#ifndef ERROR_H_NSE
#define ERROR_H_NSE

#include <stdexcept>

namespace nse
{
    class error : public std::exception
    {
    public:
        error() = default;
        ~error() throw() override = default;

        const char* what() const throw() override
        {
            return message_.c_str();
        }

        error &operator<<(const std::string& data)
        {
            message_ += data;
            return *this;
        }

    private:
        std::string message_;
    };
} // nse

#define nse_error throw nse::error()

#endif // ERROR_H_NSE
