#ifndef TABLE_H_NDB
#define TABLE_H_NDB

namespace ndb
{
    class table_base {};

    template<typename D>
    class table : table_base
    {
        template<typename Derived>
        struct detail_t {
            constexpr detail_t() { name = Derived::name_; };
            const char *name{};
        };
    public:
        struct detail_t<D> detail{};
    };
} // ndb

#endif // TABLE_H_NDB
