#ifndef ACCESSOR_H_NSE
#define ACCESSOR_H_NSE

#include <nse/type.hpp>
#include <nse/error.hpp>
#include <fstream>

namespace nse
{
    namespace io
    {
        class accessor_base
        {
        public:
            virtual void write(size_t index, const char* data, size_t data_size) = 0;
        };


        class drive_accessor : accessor_base
        {
        public:
            drive_accessor() : path_("./")
            {
                open(static_data_, path_ + "0.nse");
                open(dynamic_data_, path_ + "0.nse");
            }

            void write(size_t offset, const char* data, size_t data_size) override
            {
                static_data_.clear();
                static_data_.seekp(offset);
                static_data_.write(data, data_size);
            }

        private:
            void open(std::fstream& fs, const std::string& path)
            {
                fs.open(path, std::ios::in | std::ios::out | std::ios::binary);
                if (!fs.is_open())
                {
                    fs.open(path, std::ios::out);
                    if (!fs.is_open()) nse_error << "can't access drive file " + path;
                    fs.close();
                    fs.open(path, std::ios::in | std::ios::out | std::ios::binary);
                }
            }

            std::string path_;
            std::fstream static_data_;
            std::fstream dynamic_data_;
        };
    } // io
} // nse

#endif // ACCESSOR_H_NSE