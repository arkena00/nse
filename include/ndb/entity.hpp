#ifndef ENTITY_H_NDB
#define ENTITY_H_NDB

#include <cstddef>

namespace ndb
{
    template<class... Ts>
    class entity
    {
    public:
        static constexpr auto count() {
            return sizeof...(Ts);
        }
        static constexpr auto size() {
            std::size_t sum = 0;
            using expand = std::size_t[];
            (void)expand{(sum += Ts::size())...};
            return sum;
        }
    };
} // ndb

#endif // ENTITY_H_NDB
