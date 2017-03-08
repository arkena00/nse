#ifndef FILE_H_NSE
#define FILE_H_NSE

#include <nse/entity.hpp>
#include <nse/utility.hpp>
#include <nse/field.hpp>

namespace nse
{
    using File = entity<
        field<std::string, 16>,
        field<size_t>,
        field<char*>
    >;

    class file : public File
    {
        std::string _name;
        size_t _size;

    public:
        file(const std::string& name, size_t size);
        file(const char* data);

        const std::string& name() const;
        //size_t address() const;
        size_t size() const;
    };

} // nse

#endif // FILE_H_NSE
