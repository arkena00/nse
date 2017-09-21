#include <iostream>
#include <cassert>
#include <ndb/engine/nse/nse.hpp>
#include "ndb/model.hpp"
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

template<std::size_t value>
using size_t_wrapper = std::integral_constant<std::size_t, value>;

template<typename T1, typename T2>
void assert_same_type(T1, T2) { T1{} = T2{}; }

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

    ndb::for_each_entity<db::library>([](auto&& index, auto&& table) {
        std::cout << "\ntable : " << index << " : " << table.detail.name;

        ndb::for_each_entity(table, [](auto&& i, auto&& field)
        {
          std::cout << "\nindex : " << i << " : " << field.size;
        });
    });
    assert_same_type(size_t_wrapper<359>{}, ndb::trait::array_size_for<db::library::movie>::type{});
    assert_same_type(size_t_wrapper<104>{}, ndb::trait::array_size_for<db::library::sound>::type{});
    assert_same_type(size_t_wrapper<463>{}, ndb::trait::array_size_for<db::library>::type{});
    std::cout << "\n" << ndb::trait::array_size_for<db::library>::type::value;
    std::cout << "\n" << ndb::trait::array_size_for<db::library::movie>::type::value;
    std::cout << "\n" << ndb::trait::array_size_for<db::library::sound>::type::value;
    return 0;
}