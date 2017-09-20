#ifndef UTILITY_H_NSE
#define UTILITY_H_NSE

#include <utility>
#include <tuple>
#include <iostream>

namespace nse
{
    namespace trait
    {
        template<size_t N, class Field, class... Ts> struct field_offset;

        // first field offset
        template<class Field, class... Ts>
        struct field_offset<0, Field, Ts...> { static constexpr auto value = 0; };

        template<size_t N, class Field, class... Ts>
        struct field_offset
        {
            static constexpr auto value = field_offset<N - 1, Ts...>::value + Field::size();
        };

        template<size_t N, class... Ts>
        auto entity_field_offset() { return field_offset<N, Ts...>::value; }

        // field_size
        template<size_t N, class Field, class... Ts> struct field_size;

        template<class Field, class... Ts>
        struct field_size<0, Field, Ts...> { static constexpr auto value = Field::size(); };

        template<size_t N, class Field, class... Ts>
        struct field_size
        {
            static constexpr auto value = field_size<N - 1, Ts...>::value;
        };

        template<size_t N, class... Ts>
        auto entity_field_size() { return field_size<N, Ts...>::value; }
    } // trait

    // for each entity, get field
    template<std::size_t... N, class F, class... Ts>
    void for_each_impl(std::index_sequence<N...>, F&& f, Ts&&... pack)
    {
        using expand = int[];
        (void)expand{1, ((void)std::forward<F>(f)(std::integral_constant<std::size_t, N>{}, std::forward<Ts>(pack)), 0)...};
    }

    template<class F, class... Ts>
    void for_each(F&& f, Ts&&... pack)
    {
        for_each_impl(std::index_sequence_for<Ts...>{}, std::forward<F>(f), std::forward<Ts>(pack)...);
    }
} // nse

/*
namespace graphic {
    inline std::ostream &operator<<(std::ostream &os, char c) {
        return os << (std::is_signed<char>::value ? static_cast<int>(c)
                                                  : static_cast<unsigned int>(c));
    }

    inline std::ostream &operator<<(std::ostream &os, signed char c) {
        return os << static_cast<int>(c);
    }

    inline std::ostream &operator<<(std::ostream &os, unsigned char c) {
        return os << static_cast<unsigned int>(c);
    }
} // graphic
*/
#endif // UTILITY_H_NSE
