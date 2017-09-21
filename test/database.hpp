#include <ndb/model.hpp>
#include <ndb/table.hpp>
#include <ndb/field.hpp>
#include <ndb/entity.hpp>

namespace db
{
    using ndb::field;

    namespace tables
    {
        struct author : ndb::table
        {
            using name = field<char, 255>;
            using lastname = field<char, 255>;

            using detail_ = ndb::detail_table<
                ndb::entity<name, lastname>
            >;
            static constexpr detail_ detail{"author"};
        };

        struct movie : ndb::table
        {
            using id = field<int>;
            using name = field<char, 255>;
            //using author = field<tables::author>;
            using author = field<char, 100>;

            using detail_ = ndb::detail_table<
                ndb::entity<id, name, author>
            >;
            static constexpr detail_ detail{"movie"};
        };

        struct sound : ndb::table
        {
            using id = field<int>;
            using author = field<char, 100>;

            using detail_ = ndb::detail_table<
                ndb::entity<id, author>
            >;
            static constexpr detail_ detail{"sound"};
        };
    } // tables

    struct library : ndb::model
    {
        using movie = tables::movie;
        using sound = tables::sound;

        using detail_= ndb::detail_table<
            ndb::entity<movie, sound>
        >;
        static constexpr detail_ detail{"library"};
    };

} // db
