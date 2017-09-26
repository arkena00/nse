#ifndef BLOCK_BASE_H_NSE
#define BLOCK_BASE_H_NSE

#include <cstddef>

namespace nse
{
    class block_base
    {
    public:
        virtual void write(const char* data, size_t data_size, size_t offset) = 0;

        virtual char* data() = 0;
        virtual char at(size_t index) const = 0;
        virtual size_t size() const = 0;
        virtual size_t capacity() const = 0;
    };
} // nse

#endif // BLOCK_BASE_H_NSE
