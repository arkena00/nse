#ifndef TABLE_H_NSE
#define TABLE_H_NSE

#include <nse/io_access.hpp>

namespace nse
{
    template<class Entity, class Accessor = io_access_drive>
    class table
    {
    public:
        table() {}


        void add(const Entity& entity) {}
        //template<class... Ts>
        //void add(Ts&&... args);

        void del(size_t index) {}
        Entity get(size_t index) const {}
        // block_view fast_get(unsigned int index) const; return a view ?

    private:
        // buffer;
        // header;
        Accessor io_access_;

        void write(size_t offset, const char* data, size_t data_size)
        {
            io_access_.write(offset, data, data_size);
        }
    };
} // nse

#endif // TABLE_H_NSE
