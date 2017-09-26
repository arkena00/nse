#ifndef STATIC_BLOCK_H_NSE
#define STATIC_BLOCK_H_NSE

#include <nse/block_base.hpp>
#include <array>

namespace nse
{
    template<size_t Size>
    class static_block : public block_base
    {
    public:
        static_block() = default;
        explicit static_block(std::array<char, Size>&& data)
        {
            data_ = data;
        }

        void write(size_t offset, const char* data, size_t data_size) override
        {
            memcpy(data_.data() + offset, data, data_size);
        }

        char* data() override
        {
            return data_.data();
        }

        char at(size_t index) const override
        {
            return data_.at(index);
        }

        size_t size() const override
        {
            return Size;
        }

        size_t capacity() const override
        {
            return Size;
        }

    private:
        std::array<char, Size> data_;
    };
} // nse

#endif // STATIC_BLOCK_H_NSE
