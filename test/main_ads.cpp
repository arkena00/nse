#include <ndb/engine/nse/nse.hpp>
#include <ndb/engine/sql/sql.hpp>
#include "database.hpp"

#include <nse/table.hpp>

struct zeta : ndb::table
{
    using Id = ndb::field<int>;
    using Name = ndb::field<char, 6>;

    using Detail_ = ndb::table::detail<
    ndb::entity<Id, Name>
    >;
    static constexpr Detail_ detail_{"movie"};
};

int main()
{
    //ndb::engine<>::make<db::Library>();

    nse::table<zeta> table;

    table.add(3, 5);

    table.buffer_.debug();

    return 0;
}

//TODO: trouver un moyen d'inclure seulement <ndb/engine.hpp>, qui incluera le header du engine définis dans le setup