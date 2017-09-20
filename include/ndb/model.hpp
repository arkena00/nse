#ifndef MODEL_H_NDB
#define MODEL_H_NDB

#include <array>

namespace ndb
{
    class model
    {

    };


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
        constexpr char get()
        {
            return std::get<N>(array_);
        }

    private:
        std::array<char, trait::array_size_for<Model>::value> array_ {};
    };

} // ndb

#endif // ENTITY_H_NDB
