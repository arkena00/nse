#include <cstddef>
#include <string>
#include <nse/encoder.hpp>

namespace nse
{
    template<> size_t encoder::decode<size_t>(const char* v) { return *reinterpret_cast<const size_t*>(v); }
    template<> std::string encoder::decode<std::string>(const char* v) { return std::string(v); }
} // nse
