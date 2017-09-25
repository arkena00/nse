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

#include <ndb/option.hpp>
#include <ndb/table.hpp>
#include <ndb/utility.hpp>

namespace ndb
{
    class field_base
    {
    public:
        template<size_t Size>
        struct size
        {
            static constexpr auto size_ = Size;
        };
    };

    namespace detail
    {
        // default field value : sizeof(T) for static_field, 0 for field_entity
        template<class T>
        constexpr size_t default_size()
        {
            if constexpr (ndb::is_table<T>) return 0;
            else return sizeof(T);
        }
    } // detail

////////////////////////////////////////////////////////////////////////////////
////////////////////////          COMMON_FIELD          ////////////////////////
////////////////////////////////////////////////////////////////////////////////
    template<class Size, class Option>
    class common_field
    {
    public:
        struct detail
        {
            static constexpr bool is_primary = option_trait::has<field_option::primary, Option>::value;
            static constexpr bool is_auto_increment = option_trait::has<field_option::autoincrement, Option>::value;
            static constexpr bool is_unique = option_trait::has<field_option::unique, Option>::value;
            static constexpr bool is_not_null = option_trait::has<field_option::not_null, Option>::value;
            static constexpr size_t size = Size::size_;
        };

        using Detail_ = detail;
        static constexpr Detail_ detail_{};
    };

////////////////////////////////////////////////////////////////////////////////
////////////////////////             FIELD              ////////////////////////
////////////////////////////////////////////////////////////////////////////////
    template<class T, class = void, class...> class field;

    // field<T>
    template<class T>
    class field<T, typename std::enable_if_t<!ndb::is_table<T>>> :
        public common_field<field_base::size<detail::default_size<T>()>, option<field_option::none>>, field_base
    {
    public:
        using type = T;
        using typename common_field<field_base::size<detail::default_size<T>()>, option<field_option::none>>::Detail_;
    };

    // field<T, Size>
    template<class T, size_t S>
    class field<T, field_base::size<S>> :
        public common_field<field_base::size<S>, option<field_option::none>>, field_base
    {
    public:
        using type = T;
        using typename common_field<field_base::size<S>, option<field_option::none>>::Detail_;
    };

    // field<T, option>
    template<class T, class... Option_code>
    class field<T, option<Option_code...>> :
        public common_field<field_base::size<detail::default_size<T>()>, option<Option_code...>>, field_base
    {
    public:
        using type = T;
        using typename common_field<field_base::size<detail::default_size<T>()>, option<Option_code...>>::Detail_;
    };

    // field<T, Size, Option>
    template<class T, size_t Size, class... Option_code>
    class field<T, field_base::size<Size>, option<Option_code...>> :
        public common_field<field_base::size<Size>, option<Option_code...>>, field_base
    {
    public:
        using type = T;
        using typename common_field<field_base::size<Size>, option<Option_code...>>::Detail_;
    };

    // field<table, size>
    template<class T, size_t Size>
    class field<T, typename std::enable_if_t<ndb::is_table<T>>, field_base::size<Size>> :
        public common_field<field_base::size<Size>, option<field_option::none>>, field_base
    {
    public:
        using type = T;
        using typename common_field<field_base::size<Size>, option<field_option::none>>::Detail_;
    };

    // field<table>
    template<class T>
    class field<T, typename std::enable_if_t<ndb::is_table<T>>> :
        public common_field<field_base::size<detail::default_size<T>()>, option<field_option::none>>, field_base
    {
    public:
        using type = T;
        using typename common_field<field_base::size<detail::default_size<T>()>, option<field_option::none>>::Detail_;
    };
} // ndb

#endif // FIELD_H_NDB