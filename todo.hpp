// data blocks
class block_base;
template<unsigned int Size> static_block : block_base;
template<unsigned int Capacity> dynamic_block : block_base;

field<int, size>
taille
offset

table<id, name>
nombre de champs

model<table, table2>
nombre de table




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
