#ifndef TABLE_H_NSE
#define TABLE_H_NSE

#include <nse/accessor.hpp>
#include <nse/dynamic_block.hpp>
#include <nse/static_block.hpp>
#include <nse/debug.hpp>
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
            entity_count_++;
        }

        size_t entity_count() const { return entity_count_; }

        char* data() { return data_.data(); }

    private:
        nse::static_block<Header::count() * sizeof(size_t)> data_;
        size_t entity_count_;
    };

}

namespace nds
{
    template<>
    void encoder<>::encode_ref(nse::header& in)
    {
        in.data_.write(reinterpret_cast<char*>(&in.entity_count_), nse::Header::item_size<0>(), 0);
        in.data_.write(reinterpret_cast<char*>(&in.entity_count_), nse::Header::item_size<1>(), 4);
    }

    template<>
    void encoder<>::decode(nse::header& in)
    {
        in.entity_count_ = *(reinterpret_cast<nse::Header::item_at<0>::type*>(in.data_.data()));
    }
} // nds


namespace nse
{
    template<class Model_table, class Accessor = io::drive_accessor>
    class table
    {
    public:
        using Entity = typename Model_table::Detail_::entity;

        explicit table(const std::string& name = "main") :
            accessor_(entity_offset(), name)
        {
            size_t header_status  = accessor_.read(header_.data(), header_.size(), 0);
            if (header_status != 0) nds::encoder<>::decode(header_);
        }

        constexpr const header& header() const
        {
            return header_;
        }

        constexpr static size_t entity_size()
        {
            return Entity::size();
        }

        size_t entity_offset() const
        {
            return header_.size();
        }

        size_t entity_count() const
        {
            return header_.entity_count();
        }

        size_t entity_offset(size_t index) const
        {
            return entity_offset() + index * entity_size();
        }

        // get entity as block
        static_block<table::entity_size()> get(size_t index)
        {
            // index out of range
            if (index >= header_.entity_count()) nse_error << "entity index out of range, index : " << index << ", entity count : " << header_.entity_count();
            static_block<entity_size()> buffer;

            accessor_.read(buffer.data(), buffer.size(), entity_offset(index));
            return buffer;
        }

        // add new entity with specified values
        template<class... Ts>
        void add(Ts&&... values)
        {
            // check if values are set for all fields
            static_assert(sizeof...(Ts) == Entity::count(), "number of value must match number of fields");

            // write entity
            accessor_.async_write<Entity>(entity_offset() + entity_count() * entity_size(), values...);
            // update header
            header_.entity_add();
        }

        void del(size_t index) {}

        void sync()
        {
            accessor_.sync();
            // write header
            nds::encoder<>::encode_ref(header_);
            accessor_.write(header_.data(), header_.size(), 0);
        }

    public:
        nse::header header_;
        Accessor accessor_;
    };
} // nse

#endif // TABLE_H_NSE
