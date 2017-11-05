#include <nse/utility.hpp>
#include <iostream>
#include <nse/page.hpp>

int main()
{
    std::cout << CacheLineSize();
    std::cout << "_" << sizeof(nse::page<4096>);

    return 0;
}