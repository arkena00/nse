#include <ndb/engine/nse/nse.hpp>
#include <ndb/engine/sql/sql.hpp>
#include "database.hpp"

#include <nse/table.hpp>
#include <nse/debug.hpp>

struct zeta : ndb::table
{
    using Id = ndb::field<char>;
    using Name = ndb::field<uint16_t>;
    using Test = ndb::field<uint16_t>;
    using Test2 = ndb::field<char, ndb::field_base::size<3>>;

    using Detail_ = ndb::table::detail<
        ndb::entity<Id, Name, Test2>
    >;
    static constexpr Detail_ detail_{"zeta"};
};

int main()
{
    try
    {
        nse::table<zeta> table;
        std::cout << "count : " << table.header().entity_count();

        auto item = table.get(5);
        nse::debug::display(item);

        auto item2 = table.get(0);
        nse::debug::display(item2);

        /*
        table.add(static_cast<uint8_t>(255), (uint16_t) 0x6262, static_cast<int16_t >(256));
        table.add('A', (uint16_t) 0x6161, (char) 5);
        table.add('A', (uint16_t) 0x6161, (char) 5);
        table.add('A', (uint16_t) 0x6161, (char) 5);*/

        //table.add((char) 255, (uint16_t) 0x6161, (char) 255);
        //table.sync();

        //nse::debug::display(table.buffer_, zeta::detail_.size);
    }
    catch (const std::exception& e)
    {
        std::cout << std::endl << "FATAL ERROR : " << std::string(e.what());
    }
    return 0;
}



//TODO: trouver un moyen d'inclure seulement <ndb/engine.hpp>, qui incluera le header du engine définis dans le setup