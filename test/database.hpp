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

            using entity = ndb::entity<name, lastname>;
            static constexpr ndb::detail_table detail{"author"};
        };

        struct movie : ndb::table
        {
            using id = field<int>;
            using name = field<char, 255>;
            //using author = field<tables::author>;
            using author = field<char, 100>;

            using entity = ndb::entity<id, name, author>;
            static constexpr ndb::detail_table detail{"movie"};
        };

        struct sound : ndb::table
        {
            using id = field<int>;
            //using author = tables::author;
            using author = field<char, 100>;

            using entity = ndb::entity<id, author>;
            static constexpr ndb::detail_table detail{"sound"};
        };
    } // tables

    struct library : ndb::model
    {
        static constexpr auto name_ = "library";
        using movie = tables::movie;
        using sound = tables::sound;

        using entity = ndb::entity<movie, sound>;
    };

} // db
