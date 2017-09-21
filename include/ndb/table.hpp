#ifndef TABLE_H_NDB
#define TABLE_H_NDB

#include <tuple>

namespace ndb
{
    struct detail_table
    {
        const char * const name;
        constexpr detail_table(const char * n) : name{n} { }
    };

    class table
    {
    };
} // ndb

#endif // TABLE_H_NDB
