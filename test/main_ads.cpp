#include <ndb/engine/nse/nse.hpp>
#include <ndb/engine/sql/sql.hpp>
#include "database.hpp"

#include <nse/table.hpp>
#include <nse/debug.hpp>

struct zeta : ndb::table
{
    using Id = ndb::field<char, ndb::field_base::size<20>, ndb::option<ndb::field_option::unique, ndb::field_option::autoincrement>>;
    using Name = ndb::field<char, ndb::option<ndb::field_option::primary, ndb::field_option::not_null>>;
    using Test = ndb::field<uint16_t, ndb::field_base::size<340>>;
    using Test2 = ndb::field<char, ndb::field_base::size<3>>;

    using Detail_ = ndb::table::detail<
    ndb::entity<Id, Name, Test, Test2>
    >;
    static constexpr Detail_ detail_{"zeta"};
};

struct zeta_model : ndb::model
{
    using Detail_= ndb::table::detail<
        ndb::entity<zeta>
    >;
    static constexpr Detail_ detail_{"ZetaModel"};
};

int main()
{
    //ndb::engine<>::make<db::Library>();

    nse::table<zeta> table;
    ndb::engine<>::make<zeta_model>();

    // table.add(4, 'b'); fail
    table.add(static_cast<char>(68), 'O', (uint16_t)0x6262, static_cast<int16_t >(256));
    table.add('A', 'B', (uint16_t)0x6161, (char)5);

    table.sync();

    nse::debug::display(table.buffer_);

    return 0;
}

//TODO: trouver un moyen d'inclure seulement <ndb/engine.hpp>, qui incluera le header du engine définis dans le setup