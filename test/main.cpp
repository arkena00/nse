#include <iostream>
#include <nse/table.hpp>
#include "database.hpp"

struct movie : public db::library::movie::entity
{};

int main()
{
    movie test;

    std::cout << "movie ";

    return 0;
}