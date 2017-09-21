#ifndef TABLE_H_NDB
#define TABLE_H_NDB

#include <tuple>

namespace ndb
{
    template<typename Entity, typename... Options>
    struct detail_table
    {
        using entity = Entity; //YYAAAAAAAAY
        const char * const name;
        constexpr detail_table(const char * n) : name{n} { }
    };

    class table
    {
    };
} // ndb

#endif // TABLE_H_NDB
