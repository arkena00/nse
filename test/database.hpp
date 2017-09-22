#include <ndb/model.hpp>
#include <ndb/table.hpp>
#include <ndb/field.hpp>
#include <ndb/entity.hpp>

namespace db
{
    using ndb::field;
    using ndb::table;

    namespace tables
    {
        struct author : ndb::table
        {
            using Name = field<char, 255>;
            using Lastname = field<char, 255>;

            using Detail_ = table::detail<
                ndb::entity<Name, Lastname>
            >;
            static constexpr Detail_ detail_{"author"};
        };

        struct movie : ndb::table
        {
            using Id = field<int>;
            using Name = field<char, 255>;
            using Author = field<tables::author>;
            // using author = field<tables::author, option::many>;

            using Detail_ = table::detail<
                ndb::entity<Id, Name, Author>
            >;
            static constexpr Detail_ detail_{"movie"};
        };

        struct sound : ndb::table
        {
            using Id = field<int>;
            using Name = field<char, 255>;
            using Author = field<tables::author>;

            using Detail_ = table::detail<
                ndb::entity<Id, Name, Author>
            >;
            static constexpr Detail_ detail_{"sound"};
        };
    } // tables

    struct Library : ndb::model
    {
        using Movie = tables::movie;
        using Sound = tables::sound;

        using Detail_= table::detail<
            ndb::entity<Movie, Sound>
        >;
        static constexpr Detail_ detail_{"library"};
    };
} // db
