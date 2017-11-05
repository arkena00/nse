#ifndef ACCESSOR_H_NSE
#define ACCESSOR_H_NSE

#include <nse/type.hpp>
#include <nse/error.hpp>
#include <nse/dynamic_block.hpp>
#include <nse/cache.hpp>
#include <fstream>
#include "debug.hpp"
#include "static_block.hpp"
#include <nse/io.hpp>

namespace nse
{
    namespace io
    {
        class drive_accessor : io::base
        {
        public:
            explicit drive_accessor(size_t cache_offset = 0, const std::string& name = "main") :
                cache_(*this, cache_offset),
                path_("./" + name)
            {
                open(static_data_, path_ + "0.nse");
                open(dynamic_data_, path_ + "1.nse");
            }

            size_t read(char* data, size_t data_size, size_t offset) override
            {
                static_data_.clear();
                static_data_.seekg(offset);
                static_data_.read(data, data_size);
                return static_cast<size_t>(static_data_.gcount());
            }

            void write(const char* data, size_t data_size, size_t offset) override
            {
                static_data_.clear();
                static_data_.seekp(offset);
                static_data_.write(data, data_size);
            }

            size_t async_read(char* data, size_t data_size, size_t offset)
            {
                return 0;
            }

            void async_write(const char* data, size_t data_size, size_t offset)
            {
                nse_debug << "cache write at " << offset - cache_.offset();
                cache_.write(data, data_size, offset - cache_.offset());
            }

            // write entity values at offset
            template<class Entity, class... Ts>
            void async_write(size_t start_offset, Ts... values)
            {
                // tmp buffer
                nse::static_block<Entity::size()> buffer;

                nse_debug << "write entity at " << start_offset << " size " << Entity::size();
                ndb::for_each([&](auto&& index, auto&& v)
                {
                    using value_type = std::decay_t<decltype(v)>;

                    // size_t offset =  start_offset + Entity::template offset<decltype(Index){}>();
                    size_t offset =  Entity::template offset<decltype(index){}>();
                    constexpr size_t item_size = Entity::template item_size<decltype(index){}>();

                    // value is fundamental
                    if constexpr (std::is_fundamental<value_type>::value)
                    {
                        // check if value can be store in field
                        static_assert(sizeof(value_type) <= item_size, "field cannot store value");
                        buffer.write(reinterpret_cast<const char*>(&v), item_size, offset);
                    }
                    else if constexpr (std::is_pointer<value_type>::value)
                    {
                        // write from pointer to pointer + item_size, rest is not zero filled
                        buffer.write(reinterpret_cast<const char*>(v), item_size, offset);
                    }
                }, values...);

                async_write(buffer.data(), Entity::size(), start_offset);
            }

            // synchronize cache
            void sync()
            {
                cache_.sync();
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

            nse::cache<28, 2> cache_;
        };
    } // io
} // nse

#endif // ACCESSOR_H_NSE

// remove cache offset add offset to pages