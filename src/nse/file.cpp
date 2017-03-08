#include <nse/file.hpp>
#include <nse/setup.hpp>

namespace nse
{
    file::file(const std::string& name, size_t size) :
        _name(name),
        _size(size)
    {}

    file::file(const char* data) : entity(data) {}

    const std::string& file::name() const { return _name;}//entity::field_const<NAME>().get(); }
    //size_t file::address() const { return entity::field<ADDRESS>().value(); }
    size_t file::size() const { return _size;}//entity::field_const<SIZE>().get(); }
} // nse
