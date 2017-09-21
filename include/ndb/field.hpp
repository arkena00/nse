#ifndef FIELD_H_NDB
#define FIELD_H_NDB

#include <nse/type.hpp>
#include <ndb/table.hpp>
#include <ndb/utility.hpp>

namespace ndb
{
    // base field
    struct field_base {};

    // static field
    template<class T, size_t Size = sizeof(T), class = void>
    struct field : field_base
    {
        using type = T;

        static constexpr size_t size = Size;
    };

    // dynamic field
    /*
    template<class T, size_t Size, typename std::enable_if_t<!ndb::is_field<T>, T>>
    struct field<T*, Size>
    {
        using type = T*;

        static constexpr size_t size = sizeof(size_t);
    };*/

    template<class T>
    using Field_link_table = typename std::enable_if_t<ndb::is_field_link_table<T>, T>;
    // field link table

    template<class T, size_t Size>
    struct field<T, Size, typename std::enable_if_t<std::is_base_of<ndb::table, T>::value>>
{

    static constexpr size_t size = 999;
};

} // ndb

#endif // FIELD_H_NDB

/*! \class field can be static or dynamic, data will be stored in static or dynamic section of a table
 * Size is the space required for a field, it will be dynamic for dynamic fields
 *
 * Example :
 * field<int>
 * field<char, 255>
 * field<dynamic_size_object*>
 * field<dynamic_size_object_with_static_capacity*, 5000>
 */