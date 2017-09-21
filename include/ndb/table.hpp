#ifndef TABLE_H_NDB
#define TABLE_H_NDB

namespace ndb
{
    namespace trait
    {
        template<class Derived>
        struct detail_base_impl
        {
            using type = typename Derived::detail_;
        };
        template<class Derived> using detail_base = typename detail_base_impl<Derived>::type;
    }

    struct table_base {};

    template<class Base>
    class table : table_base
    {
    public:
        trait::detail_base<Base> detail;
    };
} // ndb

#endif // TABLE_H_NDB
