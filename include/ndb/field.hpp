#ifndef FIELD_H_NDB
#define FIELD_H_NDB

#include <nse/type.hpp>

namespace ndb
{
    // static field
    template<class T, size_t Size = sizeof(T)>
    struct field
    {
        using type = T;

        constexpr static size_t size() { return Size; }
    };

    // dynamic field
    template<class T, size_t Size>
    struct field<T*, Size>
    {
        using type = T*;

        constexpr static size_t size() { return sizeof(size_t); }
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