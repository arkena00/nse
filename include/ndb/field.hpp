#ifndef FIELD_H_NDB
#define FIELD_H_NDB

/*! \class field can be static or dynamic, data will be stored in static or dynamic section of a table
 * Size is the space required for a field, it will be dynamic for dynamic fields
 *
 * Example :
 * field<int>
 * field<char, 255>
 * field<dynamic_size_object*>
 * field<dynamic_size_object_with_static_capacity*, 5000>
 */

#include <ndb/table.hpp>
#include <ndb/utility.hpp>
/*
 * Options for fields
*/
namespace ndb
{
    enum class field_option : int
    {
        //value for option configuration
        unique = 1,
        autoincrement = 2,
        primary = 4,
        not_null = 8,

        //default value
        defaut = 0,
    };

    constexpr field_option operator|(field_option const& lhs, field_option const& rhs)
    {
        int olhs = static_cast<int>(lhs);
        int orhs = static_cast<int>(rhs);
        return static_cast<field_option>(olhs | orhs);
    }

    constexpr bool operator&(field_option const& lhs, field_option const& rhs)
    {
        int olhs = static_cast<int>(lhs);
        int orhs = static_cast<int>(rhs);
        return olhs & orhs;
    }

    class option_base {};

    template<field_option Option>
    class option : option_base
    {
    public:
        static constexpr auto opt = Option;
        static constexpr bool isPrimary = opt & field_option::primary;
        static constexpr bool isAutoIncrement = opt & field_option::autoincrement;
        static constexpr bool isUnique = opt & field_option::unique;
        static constexpr bool isNotNull = opt & field_option::not_null;
    };
}

/*
 * Common structures for fields
*/
namespace ndb
{
    // default field value : sizeof(T) for static_field, 0 for field_entity
    template<class T>
    constexpr auto default_size()
    {
        if constexpr(ndb::is_table<T>) return 0;
        else return sizeof(T);
    }

    // common field
    template<class Size, class Option>
    class common_field
    {
        //static_assert(is_option<Option> && is_size<Size>, "Size require type ndb::size<> and Option require type ndb::option<>");
    public:
        struct detail
        {
            static constexpr bool isPrimary = Option::isPrimary;
            static constexpr bool isAutoIncrement = Option::isAutoIncrement;
            static constexpr bool isUnique = Option::isUnique;
            static constexpr bool isNotNull = Option::isNotNull;
            static constexpr size_t size = Size::size_;
        };

        using Detail_ = detail;
        static constexpr Detail_ detail_{};
    };

    class field_base {};
}

/*
 * Size class
 */
namespace ndb
{
    class size_base {};

    template<size_t Size>
    class size : size_base
    {
    public:
        static constexpr auto size_ = Size;
    };
}

/*
 * Fields
*/
namespace ndb
{
    // field definition
    template<class T, class = void, class...>
    class field;

    //Specialization for only T
    template<class T>
    class field<
        T,
        typename std::enable_if_t<!ndb::is_table<T>>
    > : public common_field<size<default_size<T>()>, option<field_option::defaut>>, field_base
    {
    public:
        using type = T;
        using typename common_field<size<default_size<T>()>, option<field_option::defaut>>::Detail_;
    };

    //Specialization for size without option
    template<class T, size_t S>
    class field<
        T,
        size<S>
    > : public common_field<size<S>, option<field_option::defaut>>, field_base
    {
    public:
        using type = T;
        using typename common_field<size<S>, option<field_option::defaut>>::Detail_;
    };

    //Specialization for Option without size
    template<class T, field_option Option>
    class field<
        T,
        option<Option>
    > : public common_field<size<default_size<T>()>, option<Option>>, field_base
    {
    public:
        using type = T;
        using typename common_field<size<default_size<T>()>, option<Option>>::Detail_;
    };

    //Specialization for both size and option
    template<class T, size_t Size, field_option Option>
    class field<
        T,
        size<Size>,
        option<Option>
    > : public common_field<size<Size>, option<Option>>, field_base
    {
    public:
        using type = T;
        using typename common_field<size<Size>, option<Option>>::Detail_;
    };
} // ndb

/*
 * Partial specialization for entity
 */
namespace ndb
{
    //Specialization for entity with size
    template<class T, size_t Size>
    class field<
        T,
        typename std::enable_if_t<ndb::is_table<T>>,
        size<Size>
    > : public common_field<size<Size>, option<field_option::defaut>>, field_base
    {
    public:
        using type = T;
        using typename common_field<size<Size>, option<field_option::defaut>>::Detail_;
    };

    //Specialization for entity without size
    template<class T>
    class field<
        T,
        typename std::enable_if_t<ndb::is_table<T>>
    > : public common_field<size<default_size<T>()>, option<field_option::defaut>>, field_base
    {
    public:
        using type = T;
        using typename common_field<size<default_size<T>()>, option<field_option::defaut>>::Detail_;
    };
}

#endif // FIELD_H_NDB