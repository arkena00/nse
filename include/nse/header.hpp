#ifndef HEADER_H_NSE
#define HEADER_H_NSE

#include <nse/entity.hpp>
#include <nse/field.hpp>
#include <nse/static_block.hpp>
#include <nds/encoder/nse_block.hpp>

namespace nse
{
    using Header = entity<
        field<size_t>, // entity count
        field<size_t>
    >;
    struct header : public Header
    {
        using linear_type = nse::static_block<entity_size()>;

        size_t _entity_count;
        size_t _zeta;

        header() :
            _entity_count(0),
            _zeta(255)
        {}

       void encode(base_block& block)
        {
            //encoder & _entity_count & _zeta;
            store(block, 0, _entity_count, _zeta);
        }

        void entity_add() { _entity_count++; }//entity::field<0>().set(entity::field<0>().get() + 1); }
        void entity_del() { _entity_count--; } //entity::field<0>().set(entity::field<0>().get() - 1); }

        size_t entity_count() const { return _entity_count; } //entity::field_const<0>().get(); }
    };
} // nse

namespace nds
{
    template<>
    void encoder<>::decode(const nse::header::linear_type& data, nse::header& header)
    {
        header._entity_count = nse::header::field_get<0>(data);
        header._zeta = nse::header::field_get<1>(data);
    }
} // nds

#endif // HEADER_H_NSE
