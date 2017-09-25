#ifndef OPTION_H_NDB
#define OPTION_H_NDB

/*
 * Option fields
 */
namespace ndb {
    namespace field_option {
        struct none { static constexpr auto value = 0; };
        struct unique { static constexpr auto value = 1; };
        struct autoincrement { static constexpr auto value = 2; };
        struct primary { static constexpr auto value = 4; };
        struct not_null { static constexpr auto value = 8; };
    }
}

/*
 * Option traits
 */
namespace option_trait
{
    template<class Needle, class Haystack>
    class has;

    template<class Needle, template<class...> class Haystack, class T1, class... T>
    struct has<Needle, Haystack<T1, T...>> { static constexpr bool value = has<Needle, Haystack<T...>>::value; };

    template<class Needle, template<class...> class Haystack>
    struct has<Needle, Haystack<>> : std::false_type {};

    template<class Needle, template<class...> class Haystack, class... T>
    struct has<Needle, Haystack<Needle, T...>> : std::true_type {};
}

/*
 * Option structure
 */
namespace ndb
{
    template<class...>
    class option
    {
    };
} // ndb

#endif // OPTION_H_NDB