#ifndef ACCESSOR_H_NSE
#define ACCESSOR_H_NSE

#include <nse/type.hpp>
#include <nse/error.hpp>
#include <nse/dynamic_block.hpp>
#include <nse/cache.hpp>
#include <fstream>
#include "debug.hpp"

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
            explicit drive_accessor(const std::string& name = "main") :
                path_("./" + name)
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

            // write entity values at offset
            template<class Entity, class... Ts>
            void write(size_t start_offset, Ts... values)
            {
                nse_debug << "write entity at " << start_offset;
                ndb::for_each([&](auto&& Index, auto&& v)
                {
                  using value_type = std::decay_t<decltype(v)>;

                  size_t offset =  start_offset + Entity::template offset<decltype(Index){}>();
                  constexpr size_t item_size = Entity::template item_size<decltype(Index){}>();

                  // value is fundamental
                  if constexpr (std::is_fundamental<value_type>::value)
                {
                // check if value can be store in field
                static_assert(sizeof(value_type) <= item_size, "field cannot store value");
                cache_.write(reinterpret_cast<const char*>(&v), item_size, offset);
                }
                  else if (std::is_pointer<value_type>::value)
                {
                  // write from pointer to pointer + item_size, rest is not zero filled
                  cache_.write(reinterpret_cast<const char*>(v), item_size, offset);
                }

                }, values...);
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

            dynamic_block<32> buffer_;
            nse::cache<32, 2> cache_;
        };
    } // io
} // nse

#endif // ACCESSOR_H_NSE