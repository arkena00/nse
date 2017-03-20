#include <iostream>
#include <nse/drive.hpp>
#include <nse/file.hpp>
#include <nse/benchmark.hpp>
#include <nse/debug.hpp>
#include <vector>

#include <experimental/filesystem>

int main()
{
    using namespace nse;
    using Zeta = nse::entity<
        field<char*>,
        field<int>,
        field<std::string, 10>
    >;
    std::string s { "zeta" };
    Zeta test('b', 255, "zeta");

    nse::drive<nse::file> fs("./database");

    // fs.del(5);
    // fs.get(8)

    for (int i = 0; i != 1; i++)
    {
        fs.add("0ÿÿÿÿÿÿÿÿÿÿÿÿÿÿ", 1, 0);
        fs.add("1ÿÿÿÿÿÿÿÿÿÿÿÿÿÿ", 2, 0);
    }
    //fs.del(1);
    //fs.add(nse::file("ZETA_ZETA", 255));

    //std::cout << fs.info();
    fs.sync();


    std::cout << fs.info();
    //nse::display(fs.buffer(), nse::file::entity_size());

    return 0;
}
