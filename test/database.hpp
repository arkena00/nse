#include <ndb/model.hpp>
#include <ndb/table.hpp>
#include <ndb/field.hpp>

namespace db
{
    using ndb::field;

    namespace tables
    {
        struct author
        {
            constexpr static auto name_ = "author";
            using name = field<char, 255>;
            using lastname = field<char, 255>;

            using entity = ndb::table<name, lastname>;
        };

        struct movie
        {
            constexpr static auto name_ = "movie";
            using id = field<int>;
            using name = field<char, 255>;
            using author = field<tables::author>;

            using entity = ndb::table<id, name, author>;
        };

        struct sound
        {
            constexpr static auto name_ = "sound";
            using id = field<int>;
            using author = tables::author;

            using entity = ndb::table<id, author>;
        };
    } // tables

    struct library
    {
        constexpr static auto name_ = "library";
        using movie = tables::movie;
        using sound = tables::sound;

        using entity = ndb::model<movie, sound>;
    };

} // db
