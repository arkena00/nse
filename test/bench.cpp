static auto nse_testing_value = 0;


#include <ndb/engine/nse/nse.hpp>
#include <ndb/engine/sql/sql.hpp>
#include <ndb/field.hpp>
#include <ndb/entity.hpp>

#include <nse/table.hpp>
#include <random>
#include <nse/debug.hpp>

#include "sqlite/sqlite3.h"

#include <benchmark/benchmark.h>

struct zeta : ndb::table
{
    using Id = ndb::field<char>;
    using Name = ndb::field<int>;

    using Detail_ = ndb::table::detail<
        ndb::entity<Id, Name>
    >;
    static constexpr Detail_ detail_{"zeta"};
};

struct zetachar : ndb::table
{
    using Id = ndb::field<char>;
    using Name = ndb::field<int>;
    using Test = ndb::field<char, ndb::field_base::size<5>>;

    using Detail_ = ndb::table::detail<
    ndb::entity<Id, Name, Test>
    >;
    static constexpr Detail_ detail_{"zeta"};
};


auto nse_base = [](benchmark::State& state, nse::table<zetachar>* table)
{
    while(state.KeepRunning())
    {
        nse_testing_value = 0;
        for (size_t i = 0; i != 1000; i++)
        {
            table->add((char) 255,  15, 65535);
        }
        table->sync();
    }
};

auto nse_test = [](benchmark::State& state, nse::table<zetachar>* table)
{
    while(state.KeepRunning())
    {
        nse_testing_value = 1;
        for (size_t i = 0; i != 5000; i++)
        {
            table->add((char) 255,  15, 65535);
        }
        table->sync();
    }
};


auto sql_test = [](benchmark::State& state, sqlite3_stmt* statement)
{
    while (state.KeepRunning())
    {
        for (size_t i = 0; i != 1000; i++)
        {
            sqlite3_bind_text(statement, 1, "zeta_test", -1, SQLITE_STATIC);
            sqlite3_bind_int(statement, 2, 25);

            sqlite3_step(statement);
        }
    }
};

int main(int argc, char** argv)
{

    sqlite3* db;
    sqlite3_stmt* statement;
    std::string query = "INSERT INTO file VALUES(?1, ?2)";

    if (sqlite3_open("test.db", &db) == SQLITE_OK)
    {
        // create table
        if(sqlite3_prepare_v2(db, "CREATE TABLE file(name VARCHAR(1), size INTEGER);", -1, &statement, 0) == SQLITE_OK)
        {
            sqlite3_step(statement);
            sqlite3_finalize(statement);
        }
    }
    else std::cout << "Failed to open db\n";
    std::string error = sqlite3_errmsg(db);
    if(error != "not an error") std::cout << error << "\n";

    sqlite3_prepare_v2(db, query.c_str(), -1, &statement, 0);


    //benchmark::RegisterBenchmark("sql_test", sql_test, statement);

    nse::table<zetachar> table("base");
    nse::table<zetachar> table2("testing");
    nse::table<zetachar> table3;
    auto b1 = benchmark::RegisterBenchmark("base", nse_base, &table)->Unit(benchmark::kMicrosecond);
    auto b2 = benchmark::RegisterBenchmark("testing", nse_test, &table2)->Unit(benchmark::kMicrosecond);


    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();

    sqlite3_finalize(statement);
    sqlite3_close(db);

    system("pause");
    return 0;
}
