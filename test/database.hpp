#include <ndb/model.hpp>
#include <ndb/table.hpp>
#include <ndb/field.hpp>
#include <ndb/entity.hpp>

/*
#define ndb_field_impl(NAME, TYPE, SIZE, OPTIONS)   using NAME = ndb::field<TYPE, SIZE>; NAME NAME##_
#define ndb_field_options(NAME, TYPE, SIZE) ndb_field_impl(NAME, TYPE, SIZE, 0)
#define ndb_field_size(NAME, TYPE) ndb_field_impl(NAME, TYPE, sizeof(TYPE), 0)
#define get_3rd_parameter(a1, a2, a3, ...) a3
#define ndb_field_chooser(...) get_3rd_parameter(__VA_ARGS__, ndb_field_size, ndb_field_options, ndb_field_impl)
#define ndb_field(...) ndb_field_chooser(__VA_ARGS__)(__VA_ARGS__)
*/

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
