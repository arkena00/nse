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
    class size_base;
    class option_base;

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

        // call f for each arg
        template<std::size_t... N, class F, class... Ts>
        void for_each_impl(std::index_sequence<N...>, F&& f, Ts&&... args)
        {
            using expand = int[];
            (void)expand{((void)std::forward<F>(f)(std::integral_constant<std::size_t, N>{}, std::forward<Ts>(args)), 0)...};
        }
    } // detail

    template<class T>
    static constexpr bool is_table = std::is_base_of<ndb::table, T>::value;

    template<class T>
    static constexpr bool is_field = std::is_base_of<ndb::field_base, T>::value;

    template<class T>
    static constexpr bool is_field_entity = std::is_base_of<ndb::table, typename T::type>::value;

    template<class T>
    static constexpr bool is_field_entity_vector = is_field_entity<T> && (T{}.detail_.size == 0);

    template<class T>
    static constexpr bool is_option = std::is_base_of<ndb::option_base, T>::value;

    template<class T>
    static constexpr bool is_size = std::is_base_of<ndb::size_base, T>::value;

    // for each on pack type
    template<class... Ts, class F>
    void for_each(F&& f)
    {
        detail::for_each_impl<Ts...>(std::index_sequence_for<Ts...>{}, std::forward<F>(f));
    }

    // for_each on model entity
    template<class DB_Entity, class F>
    void for_each_entity(DB_Entity&& e, F&& f)
    {
        using Entity = typename std::decay_t<decltype(e.detail_)>::entity;
        using Ns = std::make_index_sequence<Entity::count()>;
        detail::for_each_entity_impl<Entity>(Ns{}, std::forward<F>(f));
    }

    // for each on model entity
    template<class DB_Entity, class F>
    void for_each_entity(F&& f)
    {
        for_each_entity(DB_Entity{}, std::forward<F>(f));
    }

    // for each on arguments
    template<class F, class... Ts>
    void for_each(F&& f, Ts&&... args)
    {
        detail::for_each_impl(std::index_sequence_for<Ts...>{}, std::forward<F>(f), std::forward<Ts>(args)...);
    }
} // ndb

#endif // UTILITY_H_NSE
