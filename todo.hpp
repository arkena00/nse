// data blocks
class block_base;
template<unsigned int Size> static_block : block_base;
template<unsigned int Capacity> dynamic_block : block_base;


io_access

file.write()

block.write()

// test model
table movie : id | name
table sound : id | name | duration

// link custom type to engine type
template<> struct engine_type<nse, std::chrono::time_point> { using type = int; };

using Movie = entity<
                    field<int>,
                    field<string, 255>
                    >;
using Sound = entity<
                    field<int>,
                    field<string>,
                    field<std::chrono::time_point> // engine_type<Engine, Field::type>::type
                    >;

using Library = model<Movie, Sound>;

Library::entity_count();

// with class
class movie : Movie {};
class sound : Sound {};

model<movie, sound> m;


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