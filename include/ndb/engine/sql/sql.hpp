#ifndef ENGINE_NSE_NSE_H_NDB
#define ENGINE_NSE_NSE_H_NDB

#include <ndb/engine.hpp>
#include <iostream>

namespace ndb
{
    class nse : public engine<nse>
    {
    public:
        template<class Model>
        constexpr static void make()
        {
            std::cout << "\nmake : " << Model::name_;
        }
    };
} // db

#endif // ENGINE_NSE_NSE_H_NDB