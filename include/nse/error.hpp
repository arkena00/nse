#ifndef ERROR_H_NSE
#define ERROR_H_NSE

#include <stdexcept>
#define nse_error(message) throw std::logic_error(message);

#endif // ERROR_H_NSE
