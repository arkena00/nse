// data blocks
class block_base;
template<unsigned int Size> static_block : block_base;
template<unsigned int Capacity> dynamic_block : block_base;



// test model
table movie : id | name
table sound : id | name | duration

using Movie = table<movie,
                    field<movie.id, int>,
                    field<movie.name, string, 255>
                    >;
using Sound = entity<
                    field<int>,
                    field<string>,
                    field<std::chrono::time_point>
                    >;

using Library = model<Movie, Sound>;

// with class
class movie : Movie {};
class sound : Sound {};

model<movie, sound> m;
table<movie.id, movie.name>

struct movie : public ndb::table<>
{
    Movie::field<0>::type id;
    Movie::field<1>::type name;
};

struct library : ndb::model<>
{
    Library resource;

q << (movie.id, movie.name) << movie.id == 3;


// idea
// homogeneous table
/* add entity to each table on table.add
T1 size = 3
T2 size = 5
GLOBAL size = max of T1,T2
 */

m::table<sound>::field<NAME>::size();


ID | NAME | ID | NAME | DURATION
 -     -     1   test     45
