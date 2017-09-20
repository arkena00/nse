#include <ndb/model.hpp>
#include <ndb/table.hpp>
#include <ndb/field.hpp>

namespace db
{
    using ndb::field;

    namespace tables
    {
        struct author : ndb::table
        {
            constexpr static auto name_ = "author";
            using name = field<char, 255>;
            using lastname = field<char, 255>;

            using entity = ndb::table<name, lastname>;
        };

        struct movie : ndb::table
        {
            constexpr static auto name_ = "movie";
            using id = field<int>;
            using name = field<char, 255>;
            using author = field<tables::author>;

            using entity = ndb::entity<id, name, author>;
        };

        struct sound : ndb::table
        {
            constexpr static auto name_ = "sound";
            using id = field<int>;
            using author = tables::author;

            using entity = ndb::entity<id, author>;
        };
    } // tables

    struct library : ndb::model
    {
        constexpr static auto name_ = "library";
        using movie = tables::movie;
        using sound = tables::sound;

        using entity = ndb::entity<movie, sound>;
    };

} // db
