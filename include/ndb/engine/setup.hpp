#ifndef ENGINE_SETUP_H_NDB
#define ENGINE_SETUP_H_NDB

//! \brief setup engines properties

#include <ndb/setup.hpp>
#include <string>

namespace ndb
{
    class sql;
    class nse;

    template<>
    struct setup<>
    {
        using engine = nse;
    };

    template<class Engine = setup<>::engine> class engine;

    template<>
    struct setup<engine<>>
    {
        static constexpr auto path  = "./database/";
    };

    template<>
    struct setup<sql>
    {
        //using expression_type = std::string;
        static constexpr auto path = setup<engine<>>::path;
        static constexpr auto ext = ".sql.db";
    };
} // ndb

#endif // ENGINE_SETUP_H_NDB