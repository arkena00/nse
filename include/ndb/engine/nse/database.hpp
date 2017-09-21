//
// Created by Clément François on 21/09/2017.
//

#ifndef NSE_DATABASE_HPP
#define NSE_DATABASE_HPP
#include <ndb/model.hpp>
#include <ndb/table.hpp>
#include <ndb/field.hpp>
#include <ndb/entity.hpp>

namespace db
{
    using ndb::field;

    namespace tables
    {
        struct author2 : ndb::table
        {
            static constexpr auto name_ = "author";
            using name = field<char, 255>;
            using lastname = field<char, 255>;

            using entity = ndb::entity<name, lastname>;
        };

        struct movie2 : ndb::table
        {
            static constexpr auto name_ = "movie";
            using id = field<int>;
            using name = field<char, 255>;
            using author = field<tables::author2>;

            using entity = ndb::entity<id, name, author>;
        };

        struct sound2 : ndb::table
        {
            static constexpr auto name_ = "sound";
            using id = field<int>;
            using author = tables::author2;

            using entity = ndb::entity<id, author>;
        };
    } // tables

    struct library2 : ndb::model
    {
        static constexpr auto name_ = "library";
        using movie = tables::movie2;
        using sound = tables::sound2;

        using entity = ndb::entity<movie, sound>;

    };

} // db

#endif //NSE_DATABASE_HPP
