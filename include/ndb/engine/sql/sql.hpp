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
                    output += "\n\tcreate field : " + std::to_string(field.detail_.size);
                    output += "\n\t\tOptions are : ";
                    if (field.detail_.is_primary) {
                        output += "Primary ";
                    }
                    if (field.detail_.is_unique) {
                        output += "Unique ";
                    }
                    if (field.detail_.is_auto_increment) {
                        output += "Auto increment ";
                    }
                    if (field.detail_.is_not_null) {
                        output += "Not null ";
                    }
                    if (!field.detail_.is_not_null && !field.detail_.is_auto_increment && !field.detail_.is_unique && ! field.detail_.is_primary) {
                        output += "None.";
                    }

                    if constexpr(ndb::is_field_entity<F_type>)
                    {
                        auto store_type = typename F_type::type{};

                        output += "\n\tentity type " + std::string(store_type.detail_.name);
                        output += "\n\tentity count : " + std::to_string(field.detail_.size);
                        output += "\n\ttotal size : " + std::to_string(store_type.detail_.size);

                        if constexpr(ndb::is_field_entity_vector<F_type>) output += " VECTOR";
                    }
                });
            });

            std::cout << "\noutput : " << output;
        }
    };
} // db

#endif // ENGINE_SQL_SQL_H_NDB

