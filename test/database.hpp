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
            struct detail_t {
                static constexpr auto name = "author";
            };
            detail_t detail;
            using name = field<char, 255>;
            using lastname = field<char, 255>;

            using entity = ndb::entity<name, lastname>;
        };

        struct movie : ndb::table
        {
            struct detail_t {
                static constexpr auto name = "movie";
            };
            detail_t detail;
            using id = field<int>;
            using name = field<char, 255>;
            //using author = field<tables::author>;
            using author = field<char, 100>;

            using entity = ndb::entity<id, name, author>;
        };

        struct sound : ndb::table
        {
            struct detail_t {
                static constexpr auto name = "sound";
            };
            detail_t detail;
            using id = field<int>;
            //using author = tables::author;
            using author = field<char, 100>;

            using entity = ndb::entity<id, author>;
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
