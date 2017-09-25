#ifndef TABLE_H_NSE
#define TABLE_H_NSE

#include <nse/accessor.hpp>
#include <nse/dynamic_block.hpp>
#include <nse/io.hpp>

namespace nse
{
    template<class Model_table, class Accessor = io::drive_accessor>
    class table
    {
    public:
        using Entity = typename Model_table::Detail_::entity;

        table() {}

        // add new entity with specified values
        template<class... Ts>
        void add(Ts&&... values)
        {
            // check if values are set for all fields
            static_assert(sizeof...(Ts) == Entity::count(), "number of value must match number of fields");
            // check if buffer can add new entity
            if (buffer_.size() + Entity::size() > buffer_.capacity()) nse_error << "buffer is full";
            // add entity at end of buffer
            auto offset = buffer_.size();
            // write new entity
            io::write<Entity>(buffer_, offset, values...);
        }

        void del(size_t index) {}

        void sync()
        {
            accessor_.write(buffer_.offset(), buffer_.data(), buffer_.size());
        }

    public:
        dynamic_block<512> buffer_;
        // header;
        Accessor accessor_;
    };
} // nse

#endif // TABLE_H_NSE
