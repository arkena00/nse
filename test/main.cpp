#include <iostream>
#include <ndb/engine/nse/nse.hpp>
#include "database.hpp"

struct movie : public db::library::movie::entity
{};

int main()
{
    movie test;


    ndb::nse::make<db::library>();



    return 0;
}