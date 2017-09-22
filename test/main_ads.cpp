#include <ndb/engine/nse/nse.hpp>
#include <ndb/engine/sql/sql.hpp>
#include "database.hpp"


int main()
{
    ndb::engine<>::make<db::Library>();

    ndb::for_each_entity<db::Library::Movie>([](auto&& i, auto&& field)
    {
        std::cout << "\nindex : " << i << " : " << ndb::is_field<std::decay_t<decltype(field)>>;
    });

    return 0;
}

//TODO: trouver un moyen d'inclure seulement <ndb/engine.hpp>, qui incluera le header du engine définis dans le setup