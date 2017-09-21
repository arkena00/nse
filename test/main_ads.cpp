#include <ndb/engine/nse/nse.hpp>
#include <ndb/utility.hpp>
#include "database.hpp"

struct movie : public db::library::movie::entity
{};

int main()
{
    movie test;

    ndb::engine<>::make<db::library>();

    ndb::for_each_entity<db::library::movie>([](auto&& index, auto&& item)
    {
        std::cout << "\nindex : " << index << " : " << item.size();
    });

    ndb::for_each_entity<db::library>([](auto&& index, auto&& item)
    {
        std::cout << "\nindex : " << index << " : " << item.name_;
    });

    return 0;
}