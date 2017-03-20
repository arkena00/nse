#ifndef ENTITY_H_NSE
#define ENTITY_H_NSE

#include <string>
#include <nse/utility.hpp>
#include <nse/encoder.hpp>
#include <nse/field.hpp>
#include <nse/base_block.hpp>
#include <nse/io.hpp>
#include <sstream>
#include <iostream>

namespace nse
{
    template<class... Ts>
    class entity
    {
    public:
        template<size_t N>
        using field_type = std::tuple_element_t<N, std::tuple<Ts...>>;

        constexpr static std::size_t size()
        {
          std::size_t sum = 0;
          using expand = std::size_t[];
          (void)expand{(sum += Ts::size())...};
          return sum;
        }
        constexpr static std::size_t entity_size() { return size(); }

        entity()
        {
            _data.fill(0);
        }

        template<class... Us>
        entity(Us&&... args) : entity()
        {
            static_assert(sizeof...(Us) <= sizeof...(Ts)); // too many values for entity
        }

        constexpr static size_t field_count() { return sizeof...(Ts); }
        template<size_t N>
        constexpr static size_t field_offset() { return trait::entity_field_offset<N, Ts...>(); }
        template<size_t N>
        constexpr static size_t field_size() { return trait::entity_field_size<N, Ts...>(); }

        template<size_t N>
        static auto field_get(const base_block& block) { return io::read<size_t>(block, field_offset<N>(), field_size<N>()); }

        std::array<char, size()> _data;
        std::array<char, field_count()> _field_offset;

        // hydrate block
        template<size_t N, class Field, class T, std::enable_if_t<!std::is_pointer<typename Field::type>::value, bool> = 0>
        static void hydrate(base_block& block, size_t offset, Field&&, T&& t)
        {
            io::write(block, offset + field_offset<N>(), t, field_size<N>());
        }

        template<size_t N, class Field, class T, std::enable_if_t<std::is_pointer<typename Field::type>::value, bool> = 0>
        static void hydrate(base_block& block, size_t offset, Field&&, T&& t)
        {
            io::write(block, offset + field_offset<N>(), 8421504, field_size<N>());
        }

        // store entity at buffer offset
        template<class... Us>
        static void store(base_block& block, size_t offset, Us&&... args)
        {
            static_assert(sizeof...(Us) <= sizeof...(Ts)); // too many values for entity

            nse::for_each([&](auto N, auto&& v)
            {
                entity::hydrate<decltype(N){}>(block, offset, field_type<N>{}, std::forward<decltype(v)>(v));
            }, args...);
        }
    };
} // nse

#endif // ENTITY_H_NSE
