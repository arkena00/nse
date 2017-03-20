#ifndef FIELD_H_NSE
#define FIELD_H_NSE

#include <nse/encoder.hpp>

namespace nse
{
    // static field
    template<class T, size_t Size = sizeof(T)>
    struct field
    {
        using type = T;


        constexpr static size_t size() { return Size; }
    };

    // dynamic field
    template<class T, size_t Size>
    struct field<T*, Size>
    {
        using type = T*;

        constexpr static size_t size() { return sizeof(size_t); }
    };
} // nse

#endif // FIELD_H_NSE
