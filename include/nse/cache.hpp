#ifndef CACHE_H_NSE
#define CACHE_H_NSE

#include <nse/dynamic_block.hpp>
#include <nse/page.hpp>
#include <array>
#include <ndb/utility.hpp>
#include "debug.hpp"

namespace nse
{
    template<size_t Page_size, size_t Page_count = 1>
    class cache
    {
    public:
        cache() : page_list_{page(0), page(3)}
        {

        }

        void write(const char* data, size_t data_size, size_t offset = 0)
        {
            nse_debug << "cache write at " << offset;
            int relative_offset =0;
            if (relative_offset < 0) nse_error << "offset not in range";

            // write in buffer
            if (relative_offset + data_size > data_.capacity())
            {
                std::cout << "\nbufer is full";
                // write buffer

                // reset buffer with new location
                relative_offset = 0;
            }
            data_.write(data, data_size, relative_offset);
        }

    private:
        dynamic_block<Page_size * Page_count> data_;
        std::array<nse::page, Page_count> page_list_ = ndb::make_array<nse::page, Page_count>([](size_t n)
        {
            return n * Page_size; }
        );
    };
} // nse

#endif // CACHE_H_NSE
