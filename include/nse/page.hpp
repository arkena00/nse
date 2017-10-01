#ifndef PAGE_H_NSE
#define PAGE_H_NSE

namespace nse
{
    class page
    {
    public:
        explicit page(size_t offset = 0) : offset_(offset) {}

    private:
        size_t offset_;
    };
} // nse

#endif // PAGE_H_NSE
