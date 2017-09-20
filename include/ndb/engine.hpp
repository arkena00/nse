#ifndef ENGINE_ENGINE_H_NDB
#define ENGINE_ENGINE_H_NDB

#include <ndb/engine/setup.hpp>
#include <ndb/model.hpp>

namespace ndb
{
    template<class Engine>
    struct engine
    {
        template<class Model>
        static constexpr void make()
        {
            Engine::template make<Model>();
        }
    };
} // ndb

#endif // ENGINE_ENGINE_H_NDB