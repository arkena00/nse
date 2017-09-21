#include <iostream>
#include <cassert>
#include <ndb/engine/nse/nse.hpp>
#include "database.hpp"
/*
 * Create table structure
*/
struct table_test {
    using test = ndb::field<char, 5>;
    using firstName = ndb::field<char, 255>;
    using lastName = ndb::field<char, 255>;
    using user = ndb::entity<test, firstName, lastName>;

    static constexpr auto size() { return user::size(); }
    static constexpr auto count() { return user::count(); }
};

int main()
{
    std::cout << std::endl;
    assert(table_test::count() == 2);
    assert(table_test::size() == 510);
    assert(db::tables::author::entity::count() == 2);
    assert(db::tables::author::entity::size() == 510);
    assert(table_test::user::offset<1>() == 255);

    std::cout << "\n" << table_test::user::offset<0>();
    std::cout << "\n" << table_test::user::offset<1>();
    std::cout << "\n" << table_test::user::offset<2>();

    ndb::for_each_entity<db::library>([](auto&& index, auto&& table)
      {
        std::cout << "\ntable : " << index << " : " << table.detail.name;

        ndb::for_each_entity(table, [](auto&& i, auto&& field)
        {
          std::cout << "\nindex : " << i << " : " << field.size();
        });
      });
    return 0;
}