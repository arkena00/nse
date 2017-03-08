#ifndef HEADER_H_NSE
#define HEADER_H_NSE

#include <nse/entity.hpp>
#include <nse/field.hpp>
#include <nse/static_block.hpp>

namespace nse
{
    using Header = entity<
        field<size_t>, // entity count
        field<size_t>
    >;
    struct header : public Header
    {
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

        void decode(base_block& data)
        {
            _entity_count = Header::field_get<0>(data);
            _zeta = Header::field_get<1>(data);
        }

        void entity_add() { _entity_count++; }//entity::field<0>().set(entity::field<0>().get() + 1); }
        void entity_del() { _entity_count--; } //entity::field<0>().set(entity::field<0>().get() - 1); }

        size_t entity_count() const { return _entity_count; } //entity::field_const<0>().get(); }
    };
} // nse

#endif // HEADER_H_NSE
