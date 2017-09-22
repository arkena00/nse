#ifndef FIELD_H_NDB
#define FIELD_H_NDB

#include <nse/type.hpp>
#include <ndb/table.hpp>
#include <ndb/utility.hpp>

namespace ndb
{
    //TODO : Ajouter le detail_table::size dans le field_table (les champs où on stock des tables)

    //detail_field
    template<std::size_t Size, typename... Options>
    struct detail_field
    {
        static constexpr size_t size = Size + sizeof...(Options);
    };

    // static field
    template<class T, size_t Size = sizeof(T), class = void>
    struct field : field_base
    {
        using type = T;

        static constexpr size_t size = Size;
        using detail_ = detail_field<Size>;
    };

    // dynamic field
    template<class T, size_t Size>
    struct field<T*, Size>
    {
        using type = T*;

        static constexpr size_t size = sizeof(size_t);
        using detail_ = detail_field<size>;
    };

    // field link
    template<class T, size_t Size>
    struct field<T, Size, typename std::enable_if_t<ndb::is_table<T>>>
    {
        static constexpr size_t size = sizeof(size_t);
        using detail_ = detail_field<size>;
    };

} // ndb


/*
 * Macro syntaxic sugar to define field
 */
#define ndb_field_impl(NAME, TYPE, SIZE, OPTIONS)   using NAME = ndb::field<TYPE, SIZE>; NAME NAME##_
#define ndb_field_options(NAME, TYPE, SIZE) ndb_field_impl(NAME, TYPE, SIZE, 0)
#define ndb_field_size(NAME, TYPE) ndb_field_impl(NAME, TYPE, sizeof(TYPE), 0)
#define get_3rd_parameter(a1, a2, a3, ...) a3
#define ndb_field_chooser(...) get_3rd_parameter(__VA_ARGS__, ndb_field_size, ndb_field_options, ndb_field_impl)
#define ndb_field(...) ndb_field_chooser(__VA_ARGS__)(__VA_ARGS__)

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