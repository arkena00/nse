#ifndef IO_H_NSE
#define IO_H_NSE

#include <nse/base_block.hpp>
#include <nse/error.hpp>

namespace nse
{
    class io
    {
    public:
        template<class T, std::enable_if_t<std::is_fundamental<T>::value, bool> = 0>
        static T read(const base_block& block, size_t offset, size_t data_size)
        {
            const T t = *(reinterpret_cast<const T*>(block.data() + offset));
            return t;
        }

        // WRITE
        template<class T, std::enable_if_t<std::is_fundamental<T>::value, bool> = 0>
        static void write(base_block& block, size_t offset, const T& data, size_t data_size)
        {
            if (sizeof(data) > data_size) nse_error("type size > data_size");
            write(block, offset, reinterpret_cast<const char*>(&data), data_size);
        }
        static void write(base_block& block, size_t offset, const std::string& data, size_t data_size)
        {
            if (data.size() > data_size) nse_error("string length > field data_size");
            write(block, offset, data.c_str(), data.size());
        }
        static void write(base_block& block, size_t offset, const char* data, size_t data_size)
        {
            block.write(offset, data, data_size);
        }
    };

} // nse

#endif // IO_H_NSE
