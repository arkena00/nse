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
            virtual size_t read(char* data, size_t data_size, size_t offset) = 0;
            virtual void write(const char* data, size_t data_size, size_t offset) = 0;
        };


        class drive_accessor : accessor_base
        {
        public:
            explicit drive_accessor(const std::string& path = "./database") :
                path_(path)
            {
                open(static_data_, path_ + "0.nse");
                open(dynamic_data_, path_ + "1.nse");
            }

            size_t read(char* data, size_t data_size, size_t offset = 0) override
            {
                static_data_.clear();
                static_data_.seekg(offset);
                static_data_.read(data, data_size);
                return static_cast<size_t>(static_data_.gcount());
            }

            void write(const char* data, size_t data_size, size_t offset = 0) override
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
                    // can't open file, try to create
                    fs.open(path, std::ios::out);
                    // can't create file
                    if (!fs.is_open()) nse_error << "can't access drive file " << path;
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