#ifndef DRIVE_H_NSE
#define DRIVE_H_NSE

#include <string>
#include <fstream>
#include <nse/header.hpp>
#include <nse/field.hpp>
#include <nse/memory_block.hpp>

namespace nse
{
    template<class T>
    class drive
    {
        using buffer_type = memory_block<512>;
    public:
        std::string _path;
        mutable std::fstream _data;
        mutable std::fstream _table;
        buffer_type _buffer;

        header _header;

        void open(std::fstream& fs, const std::string& path);
        void header_read();
        void header_write();
        void table_write(size_t offset, const char* data, size_t data_size);

        void write(size_t offset, const char* data, size_t data_size);

    public:
        drive(const std::string&);
        ~drive();

        size_t entity_offset() const;
        size_t entity_offset(size_t index) const;
        size_t entity_count() const;
        constexpr size_t entity_size() const;
        size_t table_size() const;
        constexpr size_t header_size() const;
        void display() const;
        buffer_type& buffer();

        void add(const T& entity);
        template<class... Ts>
        void add(Ts&&... args);

        void del(size_t index);
        T get(size_t index) const;

        void sync();

        std::string info() const;
    };
} // nse

#include "drive.tpp"

#endif // DRIVE_H_NSE
