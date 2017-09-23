#ifndef UTILITY_H_NSE
#define UTILITY_H_NSE

//! \brief utility functions

#include <utility>
#include <iostream>

namespace ndb
{
    class table;
    class field_base;
    class field_entity;

    namespace detail
    {
        // call f for each type
        template<class... Ts, std::size_t... Ns, class F>
        void for_each_impl(std::index_sequence<Ns...>, F&& f)
        {
            using expand = int[];
            (void)expand{1, (std::forward<F>(f)(std::integral_constant<std::size_t, Ns>{}, Ts{}), 0)...};
        }

        // call f for each table or field
        template<class Entity, std::size_t... Ns, class F>
        void for_each_entity_impl(std::index_sequence<Ns...>&&, F&& f)
        {
            using expand = int[];
            (void)expand{1, ((void)std::forward<F>(f)(std::integral_constant<std::size_t, Ns>{}, typename Entity::template type_at<Ns>{}), 0)...};
        }
    } // detail

    template<class T>
    static constexpr bool is_table = std::is_base_of<ndb::table, T>::value;

    template<class T>
    static constexpr bool is_field = std::is_base_of<ndb::field_base, T>::value;

    template<class T>
    static constexpr bool is_field_entity = std::is_base_of<ndb::table, typename T::type>::value;

    template<class T>
    static constexpr bool is_field_entity_vector = is_field_entity<T> && (typename T{}.detail_.size == 0);

    template<class... Ts, class F>
    void for_each(F&& f)
    {
        detail::for_each_impl<Ts...>(std::index_sequence_for<Ts...>{}, std::forward<F>(f));
    }

    template<class DB_Entity, class F>
    void for_each_entity(DB_Entity&& e, F&& f)
    {
        using Entity = typename std::decay_t<decltype(e.detail_)>::entity;
        using Ns = std::make_index_sequence<Entity::count()>;
        detail::for_each_entity_impl<Entity>(Ns{}, std::forward<F>(f));
    }

    template<class DB_Entity, class F>
    void for_each_entity(F&& f)
    {
        for_each_entity(DB_Entity{}, std::forward<F>(f));
    }
} // ndb

/*
namespace graphic {
    inline std::ostream &operator<<(std::ostream &os, char c) {
        return os << (std::is_signed<char>::value ? static_cast<int>(c)
                                                  : static_cast<unsigned int>(c));
    }

    inline std::ostream &operator<<(std::ostream &os, signed char c) {
        return os << static_cast<int>(c);
    }

    inline std::ostream &operator<<(std::ostream &os, unsigned char c) {
        return os << static_cast<unsigned int>(c);
    }
} // graphic
*/
#endif // UTILITY_H_NSE
