#ifndef DYNAMIC_BLOCK_H_NSE
#define DYNAMIC_BLOCK_H_NSE

#include <nse/block_base.hpp>
#include <nse/error.hpp>

namespace nse
{
    template<size_t Capacity>
    class dynamic_block : public block_base
    {
    public:
        explicit dynamic_block(size_t offset = 0) :
            offset_(offset),
            write_offset_(0),
            data_(new char[Capacity]),
            data_size_(0)
        {}
        dynamic_block(const dynamic_block&) = delete;
        dynamic_block(dynamic_block&&) = delete;

        ~dynamic_block()
        {
            delete[] data_;
        }

        void write(const char* data, size_t data_size, size_t offset) override
        {
            data_size_ += data_size;
            if (data_size_ > size()) nse_error << "memory_block overflow";
            memcpy(data_ + offset, data, data_size);
            write_offset_ = offset + data_size;
        }

        char at(size_t index) const override
        {
            if (index >= size()) nse_error << "index out of range : " << index;
            return data_[index];
        }

        char* data() override
        {
            return data_;
        }

        size_t size() const override
        {
            return data_size_;
        }

        size_t capacity() const override
        {
            return Capacity;
        }

        size_t write_offset() const
        {
            return write_offset_;
        }

        size_t offset() const
        {
            return offset_;
        }

        void offset_set(const size_t absoluteoffset_)
        {
            offset_ = absoluteoffset_;
        }

    private:
        size_t offset_;
        size_t write_offset_;

        char* data_;
        size_t data_size_;
    };
} // nse

#endif // DYNAMIC_BLOCK_H_NSE
