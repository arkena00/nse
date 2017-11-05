#ifndef CACHE_H_NSE
#define CACHE_H_NSE

#include <nse/dynamic_block.hpp>
#include <nse/page.hpp>
#include <array>
#include <optional>
#include <ndb/utility.hpp>
#include "debug.hpp"
#include <nse/io.hpp>
#include <vector>

namespace nse
{
    template<size_t Page_size, size_t Page_count>
    class cache
    {
        using Page = nse::page<Page_size>;
    public:
        cache(io::base& accessor, size_t offset = 0) :
            accessor_(accessor),
            offset_(offset),
            last_page_(0)
        {
            page_list_.reserve(Page_count);
            for (size_t i = 0; i != Page_count; i++)
            {
                page_list_.emplace_back(Page{data_, i, i * Page_size});
            }
        }

        auto page_list()
        {
            return page_list_;
        }

        size_t offset() const
        {
            return offset_;
        }

        void sync()
        {
            for (auto& page : page_list_)
            {
                if (!page.is_sync())
                {
                    nse_debug << "write page " << page.index() << " at file offset " << offset_ + page.offset();
                    accessor_.write(page.data(), page.size(), offset_ + page.offset());
                    page.sync(true);
                }
            }
        }

        // write into cache
        void write(const char* data, size_t data_size, size_t offset = 0)
        {
            // search page to store data
            for (auto& page : page_list_)
            {
                nse_debug << "search " << page.index() << " " << offset << " in " << page.offset() << " - " << page.offset_last();
                // search a page who can store data
                if (page.can_store(offset, data_size))
                {
                    nse_debug << "FOUND";
                    page.write(data, data_size, offset);
                    break;
                }
                // page store begin of data
                else if (page.has_offset(offset))
                {
                    nse_debug << "CUT ";
                }
                else
                {
                    nse_debug << "need new page";
                }

            }
        }

    private:
        dynamic_block<Page_size * Page_count> data_;

        io::base& accessor_;
        size_t offset_;
        size_t last_page_;

        std::vector<Page> page_list_;
    };
} // nse

#endif // CACHE_H_NSE
