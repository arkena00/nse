#ifndef ENGINE_SQL_SQL_H_NDB
#define ENGINE_SQL_SQL_H_NDB

#include <ndb/engine.hpp>
#include <ndb/model.hpp>
#include <iostream>
#include "../../../../test/database.hpp"

namespace ndb
{
    class sql : public engine<sql>
    {
    public:
        template<class Model>
        static void make()
        {
            std::string output;

            ndb::for_each_entity<Model>([&output](auto&& index, auto&& table)
            {
                output += "\ncreate table " + std::string(table.detail_.name);

                ndb::for_each_entity(table, [&output](auto&& i, auto&& field)
                {
                    output += "\ncreate field : " + std::to_string(field.detail_.size);
                    if (ndb::is_field_entity<std::decay_t<decltype(field)>>)
                    {
                        using Z = typename std::decay_t<decltype(field)>::type;
                        //Z z;
                        std::cout << std::is_same<db::tables::author, Z>::value;
                        //output += " ENTITY FIELD FROM " + z.detail_.name;
                    }
                });
            });

            std::cout << "\noutput : " << output;
        }
    };
} // db

#endif // ENGINE_SQL_SQL_H_NDB

