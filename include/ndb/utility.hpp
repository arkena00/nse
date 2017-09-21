#ifndef UTILITY_H_NSE
#define UTILITY_H_NSE

#include <utility>
#include <tuple>
#include <iostream>

namespace ndb
{
    namespace detail
    {
        // for each entity, get field
        template<class... Ts, std::size_t... N, class F>
        void for_each_impl(std::index_sequence<N...>, F&& f)
        {
            using expand = int[];
            (void) expand{1, ((void) std::forward<F>(f)(std::integral_constant<std::size_t, N>{}, std::forward<Ts>(Ts{})), 0)...};
        }
    } // detail

    template<class... Ts, class F>
    void for_each(F&& f)
    {
        detail::for_each_impl<Ts...>(std::index_sequence_for<Ts...>{}, std::forward<F>(f));
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
