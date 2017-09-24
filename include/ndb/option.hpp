#ifndef OPTION_H_NDB
#define OPTION_H_NDB

namespace ndb
{
    enum class option_code
    {
        none = 0, unique = 1, autoincrement = 2, primary = 4, not_null = 8
    };

    constexpr option_code operator|(option_code const& lhs, option_code const& rhs)
    {
        auto olhs = static_cast<int>(lhs);
        auto orhs = static_cast<int>(rhs);
        return static_cast<option_code>(olhs | orhs);
    }

    constexpr bool operator&(option_code const& lhs, option_code const& rhs)
    {
        auto olhs = static_cast<int>(lhs);
        auto orhs = static_cast<int>(rhs);
        return static_cast<bool>(olhs & orhs);
    }


    //option<unique<A, B>, fk<A, B>>
    //option<field_option::unique, field_option::primary_key>

    template<option_code Code>
    struct option
    {
        static constexpr auto value = Code;
    };


} // ndb

#endif // OPTION_H_NDB