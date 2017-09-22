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
    //Create base field here
    struct field_base {};

    template<std::size_t Size, typename... Options>
    struct common_field
    {
        struct detail
        {
            static constexpr size_t size = Size + sizeof...(Options);
        };

        using Detail_ = detail;

        static constexpr Detail_ detail_{};
    };

    // static field
    template<class T, size_t Size = sizeof(T), class = void>
    struct field : common_field<Size>, field_base
    {
        using type = T;

        using typename common_field<Size>::Detail_;
        //static constexpr size_t size = Detail_::size;
    };

    // dynamic field
    template<class T, size_t Size>
    struct field<T*, Size> : common_field<sizeof(size_t)>, field_base
    {
        using type = T*;

        using typename common_field<Size>::Detail_;
    };

    // field link
    template<class T, size_t Size>
    struct field<T, Size, typename std::enable_if_t<ndb::is_table<T>>> : common_field<sizeof(size_t)>, field_base
    {
        using type = T;

        using typename common_field<sizeof(size_t)>::Detail_;
        //static constexpr size_t size = Detail_::size;
    };

    //TODO: separate spe for field_link_id and field_link_table field<movie> field<movie, option::many>
    //TODO: field options

} // ndb

#endif // FIELD_H_NDB