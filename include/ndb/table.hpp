#ifndef TABLE_H_NDB
#define TABLE_H_NDB

//! \brief table for database model

namespace ndb
{
    class table
    {
    public:
        template<class Entity, class... Options>
        struct detail
        {
            using entity = Entity;

            const char* const name;
            constexpr detail(const char* n) : name{n} { }
            static constexpr std::size_t size = Entity::size() + sizeof...(Options);
        };
    };
} // ndb

#endif // TABLE_H_NDB
