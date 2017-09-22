#ifndef MODEL_H_NDB
#define MODEL_H_NDB

//! see later

namespace ndb
{
    struct model
    {

    };
}

/*

#include <array>
#include <type_traits>
#include <ndb/table.hpp>
#include <ndb/field.hpp>

namespace ndb
{
    template<class Entity>
    int generic_model_code()
    {
        if (std::is_base_of<ndb::table, Entity>::value) return generic_model_entity::table;
        else if (std::is_base_of<ndb::field_base, Entity>::value) return generic_model_entity::field;
        return 0;
    }


    namespace trait
    {
        template<class DB_Entity>
        struct array_size_for_impl
        {
            using type = std::integral_constant<std::size_t, DB_Entity::size()>;
        };

        template<class Model>
        struct array_size_for
        {
            using type = typename array_size_for_impl<typename Model::Detail_::entity>::type;
        };
    } // trait

    template<std::size_t ModelSize>
    class generic_model
    {
    public:
        constexpr generic_model()
        {
            std::get<0>(array_) = 0x61;
            std::get<1>(array_) = 0x62;
        }

        template<unsigned N>
        constexpr char get() const
        {
            return std::get<N>(array_);
        }

    private:
        std::array<char, ModelSize> array_ {};
    };

} // ndb

 */

#endif // ENTITY_H_NDB
