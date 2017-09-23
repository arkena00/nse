#ifndef TABLE_H_NSE
#define TABLE_H_NSE

#include <nse/io_access.hpp>
#include <nse/dynamic_block.hpp>

namespace nse
{
    template<class Model_table, class Accessor = io_access_drive>
    class table
    {
    public:
        using Entity = typename Model_table::Detail_::entity;

        table() {}


        void add(const Entity& entity) {}

        template<class... Ts>
        void add(Ts&&... args)
        {
            // add entity at end of buffer

            ndb::for_each([this](auto&& Index, auto&& arg)
            {
                auto offset = buffer_.size();
                //buffer_.write(offset + Entity::offset<decltype(Index){}>(), reinterpret_cast<const char*>(&arg), sizeof(arg));
            }, args...);
        }

        void del(size_t index) {}

    public:
        dynamic_block<512> buffer_;
        // header;
        Accessor io_access_;

        void write(size_t offset, const char* data, size_t data_size)
        {
            io_access_.write(offset, data, data_size);
        }
    };
} // nse

#endif // TABLE_H_NSE
