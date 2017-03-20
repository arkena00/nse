#ifndef DEBUG_H_NSE
#define DEBUG_H_NSE

#include <iostream>
#include <nse/base_block.hpp>

namespace nse
{
    void display(base_block& buf, size_t split = 0)
    {
        std::cout << "\n////////////////////////////////  BLOCK";
        std::cout << "\ncapacity : " << buf.size();
        std::cout << "\ndata_size : " << buf.size();
        std::cout << "\nDATA\n";
        for(size_t i = 0; i < buf.size(); ++i)
        {
            if (i % split == 0 && split != 0 && i > 0) std::cout << "\n";
            using namespace std;
            uint8_t p = buf.at(i);
            using namespace graphic;
            if (p < 10) std::cout << "0";
            if (p < 100) std::cout << "0";
            cout << p << " ";
        }
        std::cout << "\nEND\n";
    }
} // nse

#endif // DEBUG_H_NSE
