#include <ndb/engine/nse/nse.hpp>
#include <ndb/utility.hpp>
#include "database.hpp"

struct movie : public db::library::movie::entity
{};

int main()
{
    movie test;

    ndb::engine<>::make<db::library>();

    ndb::for_each_entity<db::library>([](auto&& index, auto&& table)
    {
        std::cout << "\ntable : " << index << " : " << table.name_;

        ndb::for_each_entity(table, [](auto&& i, auto&& field)
        {
            std::cout << "\nindex : " << i << " : " << field.size();
        });
    });

    return 0;
}