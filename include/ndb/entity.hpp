#ifndef ENTITY_H_NDB
#define ENTITY_H_NDB

//! \brief represent a database entity

#include <type_traits>
#include <tuple>
#include <utility>
#include <cstddef>
#include <ndb/utility.hpp>

namespace ndb
{
    template<class... Ts>
    class entity
    {
    public:
        template<size_t N>
        using type_at = std::tuple_element_t<N, std::tuple<Ts...>>;

        static constexpr auto count()
        {
            return sizeof...(Ts);
        }

        static constexpr auto size()
        {
            std::size_t sum = 0;
            using expand = std::size_t[];
            (void)expand{(sum += Ts::Detail_::size)...};
            return sum;
        }

        template<std::size_t N>
        static constexpr auto offset()
        {
            static_assert(N < sizeof...(Ts), "Error : Index is higher than parameter pack");
            std::size_t sum = 0;
            ndb::for_each<Ts...>([&sum](auto&& index, auto&& item)
            {
                if (index >= N) return;
                sum += item.detail_.size;
            });
            return sum;
        }
    };
} // ndb

#endif // ENTITY_H_NDB
