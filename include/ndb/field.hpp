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
    template<class T, size_t Size = sizeof(T), class = void>
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

    // field link
    template<class T, size_t Size>
    class field<T, Size, typename std::enable_if_t<ndb::is_table<T>>> : public common_field<sizeof(T) * Size>, field_base
    {
    public:
        using type = T;
        using typename common_field<sizeof(T) * Size>::Detail_;
    };

    template<class T>
    class field<T, 0, typename std::enable_if_t<ndb::is_table<T>>> : public common_field<sizeof(size_t)>, field_base
    {
    public:
        using type = T;
        using typename common_field<sizeof(size_t)>::Detail_;
    };

    //TODO: separate spe for field_link_id and field_link_table field<movie> field<movie, option::many>
    // TODO: field options

} // ndb

#endif // FIELD_H_NDB