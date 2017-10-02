#ifndef CACHE_H_NSE
#define CACHE_H_NSE

#include <nse/dynamic_block.hpp>
#include <nse/page.hpp>
#include <array>
#include <optional>
#include <ndb/utility.hpp>
#include "debug.hpp"

namespace nse
{
    namespace detail
    {
        template<size_t... Ns, class F>
        auto make_indexed(std::index_sequence<Ns...>, F&& f)
        {
            return f(Ns...);
        };
    } // detail

    template<size_t Page_size, size_t Page_count>
    class cache
    {
        using Page = nse::page<Page_size>;
    public:
        cache()
        {
        }

        auto page_list()
        {
            return page_list_;
        }

        Page* page_for(size_t offset, size_t data_size)
        {
            for (Page& page : page_list_)
            {
                nse_debug << "search " << page.index() << " " << offset << " in " << page.offset() << " - " << page.offset_last();
                // search a page who can store data
                if (page.has_offset(offset) && page.can_store(offset, data_size))
                {
                    std::cout << " FOUND " << page.index() << " can store " << data_size;
                    return &page;
                }
            }
            nse_debug << "no page found";
            return nullptr;
        }

        // write into cache
        void write(const char* data, size_t data_size, size_t offset = 0)
        {
            size_t relative_offset = 0;
            Page* page = page_for(offset, data_size);
            if (page != nullptr)
            {
                page->write(data, data_size, offset);
            }
        }

    private:
        dynamic_block<Page_size * Page_count> data_;
        std::array<Page, Page_count> page_list_ = detail::make_indexed(std::make_index_sequence<Page_count>{},
        [this](auto... ns)
        {
            return std::array<Page, Page_count>{ Page{data_, ns, ns * Page_size}... };
        });
    };
} // nse

#endif // CACHE_H_NSE
