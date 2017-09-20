#ifndef IO_ACCESS_H_NSE
#define IO_ACCESS_H_NSE

#include <nse/type.hpp>
#include <fstream>

namespace nse
{
    class io_access_base
    {
    public:
        virtual void write(size_t index, char* data, size_t data_size) = 0;
    };


    class io_access_drive : io_access_base
    {
    public:
        io_access_drive() {}

        void write(size_t index, char* data, size_t data_size) override
        {

        }

    private:
        std::string path_;
        std::fstream static_data_;
        std::fstream dynamic_data_;

    };

    class io_access_memory : io_access_base
    {
        io_access_memory() {}

        void write(size_t index, char* data, size_t data_size) override
        {

        }
    };

} // nse

#endif // IO_ACCESS_H_NSE
