# "Table" data structure.
--------------------------------------------------------------------------------
This is a handle-based memory pool with fast lookup, addition, and removal.
Erratic additions and removals can cause the table to be underutilized.

# "TableCollection" data structure.
--------------------------------------------------------------------------------
This is a wrapper around a number of Tables. TableCollection handles have an additional piece of type data, which routes
it to the relevant underlying table.
This is intended to be used for memory pools for different types of related resources (such as component data in an entity system).
