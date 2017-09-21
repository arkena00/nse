#ifndef MODEL_H_NDB
#define MODEL_H_NDB

#include <array>
#include <type_traits>
#include <ndb/table.hpp>
#include <ndb/field.hpp>

namespace ndb
{
    class model
    {

    };

    struct generic_model_entity
    {
        using id = uint8_t;
        using type_id = uint8_t;
        using count_type = uint8_t;

        enum code : uint8_t
        {
            end = 0,
            table = 200,
            table_field_array,
            table_field_link,
            table_option,
            field
        };
    };



    template<class Entity>
    int generic_model_code()
    {
        if (std::is_base_of<ndb::table_base, Entity>::value) return generic_model_entity::table;
        else if (std::is_base_of<ndb::base_field, Entity>::value) return generic_model_entity::field;
        return 0;
    }


    namespace trait
    {
        template<class Model>
        struct array_size_for { static constexpr std::size_t value = 9; };
    } // trait

    template<class Model>
    class generic_model
    {
    public:
        constexpr generic_model()
        {
            std::get<0>(array_) = 0x61;
            std::get<1>(array_) = 0x62;
        }

        template<std::size_t N>
        constexpr char get() const
        {
            return std::get<N>(array_);
        }

    private:
        std::array<char, trait::array_size_for<Model>::value> array_ {};
    };

} // ndb

#endif // ENTITY_H_NDB
