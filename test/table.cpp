#include <ndb/engine/nse/nse.hpp>
#include <ndb/engine/sql/sql.hpp>
#include "database.hpp"

#include <nse/table.hpp>
#include <nse/debug.hpp>

struct zeta : ndb::table
{
    using Id = ndb::field<uint16_t>;
    using Name = ndb::field<uint16_t>;
    using Test = ndb::field<uint16_t>;
    using Test2 = ndb::field<char, ndb::field_base::size<3>>;

    using Detail_ = ndb::table::detail<
        ndb::entity<Id, Name, Test2>
    >;
    static constexpr Detail_ detail_{"zeta"};
};

void populate(int z, nse::table<zeta>& table)
{
    for (size_t i = 0; i != z; i++)
    {
        table.add((uint16_t) i, (uint16_t) 0xAAAA, "YYY");
    }
    table.sync();
    std::cout << "\n\nsynchronized : " << table.header().entity_count();
    std::cout << "\nentity size : " << table.entity_size();
    std::cout << "\ntotal size : " << table.header().entity_count() * table.entity_size();
}

int main()
{
    try
    {
        nse::table<zeta> table;
        populate(11, table); return 0;

        std::cout << "count : " << table.header().entity_count();

        /*
        std::cout << std::endl;
        for (size_t i = 0; i != table.header().entity_count(); i++)
        {
            auto item3 = table.get(i);
            nse::debug::display(item3);
        }*/

        //nse::debug::display(table.buffer_, zeta::Detail_::size);

    }
    catch (const std::exception& e)
    {
        std::cout << std::endl << "FATAL ERROR : " << std::string(e.what());
    }
    return 0;
}