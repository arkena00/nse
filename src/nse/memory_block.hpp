#ifndef MEMORY_BLOCK_H_NSE
#define MEMORY_BLOCK_H_NSE

#include <nse/base_block.hpp>
#include <nse/error.hpp>

namespace nse
{
    template<size_t Capacity>
    class memory_block : public base_block
    {
    private:
        size_t _offset;
        size_t _write_offset;

        char* _data;
        size_t _data_size;

    public:
        memory_block(size_t offset = 0) :
            _offset(offset),
            _write_offset(0),
            _data(new char[Capacity]),
            _data_size(0)
        {}
        memory_block(const memory_block&) = delete;

        ~memory_block()
        {
            delete[] _data;
        }

        void write(size_t offset, const char* data, size_t data_size)
        {
            _data_size += data_size;
            if (_data_size > size()) nse_error("memory_block overflow");
            memcpy(_data + offset, data, data_size);
            _write_offset = offset + data_size;
        }

        char at(size_t index) const { return _data[index]; }
        size_t offset() const { return _offset; }
        void offset_set(const size_t absolute_offset) { _offset = absolute_offset; }
        size_t write_offset() const { return _write_offset; }

        const char* data() const { return _data; }
        size_t size() const { return _data_size; }
        constexpr size_t capacity() const { return Capacity; }

        void debug()
        {
            std::fstream fs("debug.txt", std::ios::out | std::ios::binary);
            std::cout << "\ndebug file created";
            //std::cout<< "\n data : " << std::hex  << _data;
            fs.write(_data, _data_size);
        }
    };
} // nse

#endif // MEMORY_BLOCK_H_NSE
