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

namespace ndb
{
    class field_base {};
    class field_entity {};

    // default field value : sizeof(T) for static_field, 0 for field_entity
    template<class T>
    constexpr auto default_size()
    {
        if constexpr(ndb::is_table<T>) return 0;
        else return sizeof(T);
    }

    // common field
    template<std::size_t Size, class... Option>
    class common_field
    {
    public:
        struct detail
        {
            static constexpr size_t size = Size + sizeof...(Option);
        };

        using Detail_ = detail;
        static constexpr Detail_ detail_{};
    };

    // static field
    template<class T, size_t Size = default_size<T>(), class = void>
    class field : public common_field<Size>, field_base
    {
    public:
        using type = T;
        using typename common_field<Size>::Detail_;
    };

    // dynamic field
    template<class T, size_t Size>
    class field<T*, Size> : public common_field<sizeof(size_t)>, field_base
    {
    public:
        using type = T*;
        using typename common_field<Size>::Detail_;
    };

    // field entity
    template<class T, size_t Entity_count>
    class field<T, Entity_count, typename std::enable_if_t<ndb::is_table<T>>> :
        public common_field<Entity_count>, field_base, field_entity
    {
    public:
        using type = T;
        using typename common_field<Entity_count>::Detail_;
    };
} // ndb

#endif // FIELD_H_NDB