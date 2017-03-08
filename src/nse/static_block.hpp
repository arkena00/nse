#ifndef STATIC_BLOCK_H_NSE
#define STATIC_BLOCK_H_NSE

#include <nse/base_block.hpp>

namespace nse
{
    template<size_t Size>
    class static_block : public base_block
    {
    private:
        std::array<char, Size> _data;

    public:
        static_block() {}
        static_block(std::array<char, Size>&& data) { _data = data; }

        void write(size_t offset, const char* data, size_t data_size)
        {
            memcpy(_data.data() + offset, data, data_size);
        }

        const char* data() const { return _data.data(); }
        char at(size_t index) const { return _data.at(index); }
        size_t size() const { return Size; }
        size_t capacity() const { return Size; }

    };
} // nse

#endif // STATIC_BLOCK_H_NSE
