#include <nse/error.hpp>
#include <nse/utility.hpp>
#include <nse/field.hpp>
#include <nse/static_block.hpp>
#include <array>
#include <sstream>

namespace nse
{
    template<class T>
    drive<T>::drive(const std::string& path) :
        _path(path),
        _buffer(header::entity_size())
    {
        open(_table, path + "0.nse");
        open(_data, path + "1.nse");

        header_read();
    }

    template<class T>
    drive<T>::~drive()
    {
        _table.close();
        _data.close();
    }

    // open path with fstream, create it if not exist
    template<class T>
    void drive<T>::open(std::fstream& fs, const std::string& path)
    {
        fs.open(path, std::ios::in | std::ios::out | std::ios::binary);
        if (!fs.is_open())
        {
            fs.open(path, std::ios::out);
            if (!fs.is_open()) nse_error("can't access drive file " + path);
            fs.close();
            fs.open(path, std::ios::in | std::ios::out | std::ios::binary);
        }
    }

    // read header
    template<class T>
    void drive<T>::header_read()
    {
         std::array<char, header::entity_size()> buffer;
        _table.clear();
        _table.seekg(0);
        _table.read(buffer.data(), buffer.size());
        if (_table.tellg() < 0) return;
        static_block<header::entity_size()> data(std::move(buffer));
        _header.decode(data);
        // set buffer offset to end of osfile
        _buffer.offset_set(table_size());
    }

    template<class T>
    void drive<T>::table_write(size_t offset, const char* data, size_t data_size)
    {
        _table.clear();
        _table.seekp(offset);
        _table.write(data, data_size);
    }

    template<class T>
    size_t drive<T>::table_size() const
    {
        _table.clear();
        _table.seekg(0, std::ios::end);
        return _table.tellg();
    }

    template<class T>
    constexpr size_t drive<T>::header_size() const { return _header.entity_size(); }

    template<class T>
    size_t drive<T>::entity_offset() const { return header_size(); }
    template<class T>
    size_t drive<T>::entity_offset(size_t index) const { return entity_offset() + index * T::entity_size(); }

    template<class T>
    size_t drive<T>::entity_count() const { return _header.entity_count(); }

    template<class T>
    constexpr size_t drive<T>::entity_size() const { return T::entity_size(); }

    template<class T>
    T drive<T>::get(size_t index) const
    {
        std::array<char, T::entity_size() * 1> buffer;
        _table.clear();
        _table.seekg(entity_offset(index));
        _table.read(buffer.data(), buffer.size());
        return T(buffer.data());
    }


    template<class T>
    void drive<T>::del(size_t index)
    {
        if (index >= entity_count() || entity_count() < 1) nse_error("index out of range");
        T last_entity = get(entity_count() - 1);
        // move last entity to deleted entity
        write(entity_offset(index), last_entity);
        // remove last entity
        _header.entity_del();
        header_write();
    }

    // write raw data in buffer
    template<class T>
    void drive<T>::write(size_t offset, const char* data, size_t data_size)
    {
        /*
        if (_buffer.is_full(data_size))
        {
            sync();
            _buffer.reset(offset);
        }*/
        _buffer.write(offset, data, data_size);
    }

    // add entity at end of entity list
    template<class T>
    template<class... Ts>
    void drive<T>::add(Ts&&... args)
    {
        // if  buffer capacity
        // add entity at end of buffer
        T::store(_buffer, _buffer.size(), std::forward<Ts>(args)...);
        _header.entity_add();
    }

    // synchronize all buffers with peristant memory
    template<class T>
    void drive<T>::sync()
    {
        // write header
        static_block<T::entity_size()> h_buffer;
        _header.encode(h_buffer);
        table_write(0, h_buffer.data(), h_buffer.size());

        // write table data
        table_write(_buffer.offset(), _buffer.data(), _buffer.size());
    }

    template<class T>
    typename drive<T>::buffer_type& drive<T>::buffer()
    {
        return _buffer;
    }

    template<class T>
    void drive<T>::display() const
    {
        if (entity_count() == 0) return;

        std::array<char, T::entity_size() * 1> buffer;
        _table.clear();
        _table.seekg(entity_offset());
        size_t index = 0;
        while (!_table.eof() && index < entity_count())
        {
            _table.read(buffer.data(), buffer.size());
            T entity = T(buffer.data());
            std::cout << "\n" << index << " | " << entity.name() << " " << entity.size();
            index++;
        }
    }

    template<class T>
    std::string drive<T>::info() const
    {
        std::stringstream out;
        out << "\n////////////////////////////////  DRIVE INFO";
        out << "\nheader_size : " << _header.entity_size();
        out << "\ntable_size : " << table_size();
        out << "\nentity_count : " << entity_count();
        out << "\nentity_size : " << entity_size();
        out << "\nentity_list_size : " << entity_count() * entity_size();
        out << "\nbuffer_capacity : " << _buffer.capacity();
        out << "\nbuffer_data_size : " << _buffer.size();
        out << "\n\n";
        return out.str();
    }
} // nse
