#include <iostream>
#include <nse/table.hpp>
#include <nse/io_access.hpp>

int main()
{
    class entity{};

    nse::table<entity, nse::io_access_drive> table;


    std::cout << "ok";

    return 0;
}
