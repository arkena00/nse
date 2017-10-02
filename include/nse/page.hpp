#ifndef PAGE_H_NSE
#define PAGE_H_NSE

#include <nse/block_base.hpp>
#include <nse/debug.hpp>

const int STATE_SYNC = 1;

namespace nse
{
    template<size_t Size>
    class page
    {
    public:
        explicit page(block_base& cache, size_t index, size_t offset) :
            cache_(cache),
            sync_(true),
            index_(index),
            offset_(offset)
        {}

        void write(const char* data, size_t data_size, size_t offset)
        {
            auto relative_offset = (index_ * Size) + offset - offset_;
            //nse_debug << "page " << index_ << " write " << data_size << " at " << relative_offset;
            cache_.write(data, data_size, relative_offset);
            sync_ = false;
        }

        const char* data() const
        {
            auto cache_offset = (index_ * Size);
            return cache_.data_at(cache_offset);
        }

        int state() const
        {
            return state_;
        }

        size_t size() const
        {
            return Size;
        }

        size_t index() const
        {
            return index_;
        }

        size_t offset() const
        {
            return offset_;
        }

        // offset after last offset
        size_t offset_last() const
        {
            return offset_ + Size - 1;
        }

        bool has_offset(size_t abs_offset) const
        {
            return abs_offset >= offset() && abs_offset <= offset_last();
        }

        bool can_store(size_t abs_offset, size_t data_size) const
        {
            return has_offset(abs_offset) && (abs_offset + data_size) <= offset_last();
        }

        bool is_sync()
        {
            return sync_;
        }

    private:
        block_base& cache_;
        int state_;
        bool sync_;

        size_t index_;
        size_t offset_;
    };
} // nse

#endif // PAGE_H_NSE