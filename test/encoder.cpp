#include <cstddef>
#include <string>
#include <nfs/encoder.hpp>

namespace nfs
{
    template<> size_t encoder::decode<size_t>(const char* v) { return *reinterpret_cast<const size_t*>(v); }
    template<> std::string encoder::decode<std::string>(const char* v) { return std::string(v); }
} // nfs
