#ifndef ENTITY_H_NDB
#define ENTITY_H_NDB

#include <type_traits>
#include <utility>
#include <cstddef>
#include <nse/utility.hpp>

namespace ndb
{
    template<class... Ts>
    class entity
    {
    public:
        static constexpr auto count()
        {
            return sizeof...(Ts);
        }

        static constexpr auto size()
        {
            std::size_t sum = 0;
            using expand = std::size_t[];
            (void)expand{(sum += Ts::size())...};
            return sum;
        }

        template<std::size_t Index>
        static constexpr auto offset()
        {
            static_assert(Index < sizeof...(Ts), "Error : Index is higher than parameter pack");
            std::size_t sum = 0;
            ::nse::for_each([&sum](auto&& v, auto&& pack)
            {
                if (v >= Index) return;
                sum += std::decay_t<decltype(pack)>::size();
            }, Ts{}...);
            return sum;
        }
    };
} // ndb

#endif // ENTITY_H_NDB
