#include <iostream>
#include <cassert>
#include <ndb/engine/nse/nse.hpp>
#include "database.hpp"
#include "ndb/model.hpp"

struct movie : public db::library::movie::entity
{};

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
    movie test;

    //constexpr std::size_t s = ndb::trait::array_size_for<db::library>::value;
    //constexpr ndb::generic_model<s> m;
    //static_assert(m.get<0>() == 0x61, "");
    //ndb::engine<>::make<db::library>();
    std::cout << std::endl;
    assert(table_test::count() == 2);
    assert(table_test::size() == 510);
    assert(db::tables::author::entity::count() == 2);
    assert(db::tables::author::entity::size() == 510);
    assert(table_test::user::offset<1>() == 255);

    std::cout << "\n" << table_test::user::offset<0>();
    std::cout << "\n" << table_test::user::offset<1>();
    std::cout << "\n" << table_test::user::offset<2>();
    return 0;
}