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
        static void make()
        {
            std::string output;

            ndb::for_each_entity<Model>([&output](auto&& index, auto&& table)
            {
                output += "\ncreate table " + std::string(table.detail_.name) + " size : " + std::to_string(table.detail_.size);

                ndb::for_each_entity(table, [&output](auto&& i, auto&& field)
                {
                    using F_type = std::decay_t<decltype(field)>;
                    output += "\ncreate field : " + std::to_string(field.detail_.size);

                    if constexpr(ndb::is_field_entity<F_type>)
                    {
                        auto store_type = typename F_type::type{};

                        output += " entity type " + std::string(store_type.detail_.name);
                        output += " entity count : " + std::to_string(field.detail_.size);
                        output += " total size : " + std::to_string(store_type.detail_.size);

                        if constexpr(ndb::is_field_entity_vector<F_type>) output += " VECTOR";
                    }
                });
            });

            std::cout << "\noutput : " << output;
        }
    };
} // db

#endif // ENGINE_SQL_SQL_H_NDB

