#ifndef IO_H_NSE
#define IO_H_NSE

#include <nse/block_base.hpp>
#include <nse/error.hpp>

namespace nse
{
    namespace io
    {
        /*
        template<class T, std::enable_if_t<std::is_fundamental<T>::value, bool> = 0>
        T read(const block_base& block, size_t offset, size_t data_size)
        {
            const T t = *(reinterpret_cast<const T*>(block.data() + offset));
            return t;
        }*/

        // write entity values into block at offset
        template<class Entity, class... Ts>
        void write(block_base& block, size_t offset, Ts... values)
        {
            ndb::for_each([&offset, &block](auto&& Index, auto&& value)
            {
                offset +=  Entity::template offset<decltype(Index){}>();
                // value is fundamental
                //if constexpr (std::is_fundamental<decltype(value)>::value)
                {
                    // check if value can be store in field
                    static_assert(sizeof(value) <= Entity::template item_size<decltype(Index){}>());
                    block.write(offset, reinterpret_cast<const char*>(&value), sizeof(value));
                }
            }, values...);
        }
    };

} // nse

#endif // IO_H_NSE
