#ifndef TABLE_H_NSE
#define TABLE_H_NSE

#include <nse/accessor.hpp>
#include <nse/dynamic_block.hpp>
#include <nse/static_block.hpp>
#include <nse/io.hpp>
#include <nds/encoder.hpp>

namespace nse
{
    using Header =  ndb::entity<ndb::field<size_t>, ndb::field<size_t>>;
    struct header : Header
    {
        template<class> friend class nds::encoder;
    public:
        header() : entity_count_(0)
        {}

        void entity_add()
        {
            //entity_count_++;
        }

        size_t entity_count() const { return entity_count_; }

        char* data() { return data_.data(); }

    private:
        nse::static_block<Header::count()> data_;
        size_t entity_count_;
    };

}

namespace nds
{
    template<>
    void encoder<>::encode(nse::header& in)
    {
        in.data_.write(0, reinterpret_cast<const char*>(in.entity_count_), nse::Header::item_size<0>());
    }

    template<>
    void encoder<>::decode(nse::header& in)
    {
        //in.entity_count_ = reinterpret_cast<nse::Header::item_at<0>::type>(in.data_.data());
    }
} // nds


namespace nse
{
    template<class Model_table, class Accessor = io::drive_accessor>
    class table
    {
    public:
        using Entity = typename Model_table::Detail_::entity;

        table() : buffer_(header_.size())
        {
            accessor_.read(header_.data(), header_.size());
        }

        // get entity as block
        static_block<Entity::size()> get(size_t index)
        {
            // index out of range
            if (index >= header_.entity_count()) nse_error << "entity index out of range, index : " << index << ", entity count : " << header_.entity_count();
            static_block<Entity::size()> buffer;
            accessor_.read(buffer.data(), buffer.size(), entity_offset(index));
            return buffer;
        }

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
            header_.entity_add();
        }

        constexpr const header& header() const { return header_; }
        size_t entity_offset() const { return header_.size(); }
        size_t entity_offset(size_t index) const { return entity_offset() + index * Entity::size(); }

        void del(size_t index) {}

        void sync()
        {
            std::cout << header_.entity_count();
            // update header
            accessor_.write(header_.data(), header_.size());
            // write buffer
            accessor_.write(buffer_.data(), buffer_.size(), buffer_.offset());
        }

    public:
        dynamic_block<512> buffer_;
        nse::header header_;
        Accessor accessor_;
    };
} // nse

#endif // TABLE_H_NSE
