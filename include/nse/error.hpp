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

        template<class T, std::enable_if_t<std::is_integral<T>::value, bool> = 0>
        error& operator<<(T t)
        {
            message_ += std::to_string(t);
            return *this;
        }

        error& operator<<(const std::string& data)
        {
            message_ += data;
            return *this;
        }

    private:
        std::string message_;
    };
} // nse

#define nse_error throw nse::error()

#define nse_assert(C) if (!(C)) nse_error << "assertion failed";

#endif // ERROR_H_NSE
