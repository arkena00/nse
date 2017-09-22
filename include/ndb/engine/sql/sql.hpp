#ifndef ENGINE_SQL_SQL_H_NDB
#define ENGINE_SQL_SQL_H_NDB

#include <ndb/engine.hpp>
#include <ndb/model.hpp>
#include <iostream>

namespace ndb
{
    class sql : public engine<sql>
    {
    public:
        template<class Model>
        static constexpr void make()
        {
            std::cout << "\ncreate sql database : " << Model::Detail_::size;
        }
    };
} // db

#endif // ENGINE_SQL_SQL_H_NDB

