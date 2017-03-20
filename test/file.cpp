#include <nfs/file.hpp>
#include <nfs/setup.hpp>

namespace nfs
{
    file::file(const std::string& name, size_t size) :
        entity(name, size, 0)
    {}

    file::file(const char* data) : entity(data) {}

    const std::string& file::name() const { return entity::field_const<NAME>().get(); }
    //size_t file::address() const { return entity::field<ADDRESS>().value(); }
    size_t file::size() const { return entity::field_const<SIZE>().get(); }
} // nfs
