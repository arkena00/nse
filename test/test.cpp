#include <iostream>
#include <nfs/benchmark.hpp>
#include "sqlite3.h"

#include <nfs/drive.hpp>
#include <nfs/file.hpp>

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

int main()
{
    // NFS TEST
    nfs::drive<nfs::file> fs("./test.nfs");

    BENCHMARK_BEGIN(test, 1000000)
        fs.add(nfs::file("ZETA_ZETA", 11));
    BENCHMARK_END(test)

    return 0;

    // SQL TEST
    sqlite3* db;
    std::string table = "CREATE TABLE file(name TEXT, size INTEGER);";
    std::string query = "INSERT INTO file VALUES(?1, ?2)";

    BENCHMARK_BEGIN(sql_test, 100)
    if (sqlite3_open("test.db", &db) == SQLITE_OK)
    {
        sqlite3_stmt* statement;
        // create table
        if(sqlite3_prepare_v2(db, table.c_str(), -1, &statement, 0) == SQLITE_OK)
        {
            sqlite3_step(statement);
            sqlite3_finalize(statement);
        }




        if(sqlite3_prepare_v2(db, query.c_str(), -1, &statement, 0) == SQLITE_OK)
        {
            sqlite3_bind_text(statement, 1, "zeta_test", -1, SQLITE_STATIC);
            sqlite3_bind_int(statement, 2, 25);

            sqlite3_step(statement);
            sqlite3_finalize(statement);
        }


    }
    else std::cout << "Failed to open db\n";
    std::string error = sqlite3_errmsg(db);
    if(error != "not an error") std::cout << error << "\n";
    sqlite3_close(db);

    BENCHMARK_END(sql_test)

    return 0;
}
