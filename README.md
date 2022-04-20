# Graph Algorithms

## Getting started

Download this code by running the following command in the directory of your choice:
```sh
git clone https://github.tamu.edu/csce221/assignment-graph-algorithms.git && cd assignment-graph-algorithms
```
[OPTIONAL] Then set up CMake (if your editor does not do this for you):
```sh
cmake -S . -B build
```
Open the code in your editor of choice. For instance, if you use VS Code:
```sh
code .
```
*Note:* On OSX you may need to enable the `code` command in VS Code with <kbd>Cmd</kbd>+<kbd>Shift</kbd>+<kbd>P</kbd> and typing "shell command." You can select the option to install the command, and then the above command will work.

## Assignment
The assignment provides you with a working `WeightedGraph` data structure, which you can use to complete the two tasks:
- [Implement Topological Sort](#implement-topological-sort) &ndash; Medium Difficulty
- [Implement Dijkstra's Algorithm](#implement-dijkstras-algorithm) &ndash; Hard Difficulty

### Understand Weighted Graph
#### Types
| Type | Alias | Description |
| ---- | ----- | ----------- |
| `value_type` | `T` | The values stored in the vertices. Commonly used in the functions you'll write. |
| `weight_type` | `int` | The type for edge weights. This is `int` for all graphs by default. The only requirement is that it is numeric. |
| `vertex_type` | `const value_type` | The type for vertices. It's a `const` form of `value_type`. Because of it being `const`, you can't use it for most of the functions you write. Use `value_type` instead. |
| `edge_type` | `std::pair<vertex_type, weight_type>` | A type for edges. The edges are really key value pairs within the adjacency list map, and I never used this type alias but it's here if you want it. |
| `adjacency_list` | `std::unordered_map<value_type, weight_type>` | The type of the adjacency list for a given source vertex. We use a `map` to associate destination vertices (`value_type`) to the weight (`weight_type`) of the edge connecting from the source. |
| `container_type` | `std::unordered_map<value_type, adjacency_list>` | The type of the container that manages the vertices (`value_type`) and their associated ajacency lists (`adjacency_list`). We use a `map` to handle the association. |
| `size_type` | `typename container_type::size_type` | We steal `size_type` from the `container`. It is likely `std::size_t` in most cases. |
| `iterator` | `typename container_type::iterator` | Our main iterator which allows us to check the vertices and/or adjacency lists is the iterator for the `container`. |
| `const_iterator` | `typename container_type::const_iterator` | We also get the `const_iterator` from the container. |
| `edge_iterator` | `typename adjacency_list::iterator` | We define an `edge_iterator` which allows us to iterate over all of the edges from a given source node. In other words, we iterate over every entry in the adjacency list for a given vertex. |
| `const_edge_iterator` | `typename adjacency_list::const_iterator` | We also get the `const_edge_iterator` which behaves similarly. |

These types were redefined in the [`graph-types.h`](src/graph-types.h) header. To use them from the header, write the type's name and supply a template argument. For example, `value_type<int>` or `weight_type<T>`.

----

```cpp
bool empty() const
```

**Parameters**: *None*

**Returns**:
- `true` if there are no vertices (and thus, no edges)
- `false` otherwise

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
bool empty(const vertex_type& vertex) const
```

**Parameters**:
- `vertex` a vertex in the graph to test

**Returns**:
- `true` if there are no edges sourced from that vertex
- `false` otherwise

**Throws**:
- `std::out_of_range` if `vertex` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average); *O(n)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices

----

```cpp
size_type size() const
```

**Parameters**: *None*

**Returns**: the number of vertices in the graph

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
size_type size(const vertex_type& vertex) const
```

**Parameters**:
- `vertex` a vertex in the graph to test

**Returns**: the number of edges in the graph that start at `vertex`

**Throws**:
- `std::out_of_range` if `vertex` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average); *O(n)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices

----

```cpp
const adjacency_list& at(const vertex_type& vertex) const
```

**Parameters**:
- `vertex` a vertex in the graph to access

**Returns**: a constant reference to the adjacency list for vertex `vertex`

**Throws**:
- `std::out_of_range` if `vertex` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average); *O(n)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices

----

```cpp
std::pair<iterator, bool> push_vertex(const vertex_type& vertex)
```

**Parameters**:
- `vertex` a vertex to add to the graph

**Returns**:
- an `iterator` to the inserted vertex, or existing vertex if the vertex already existed
- `true` if the `vertex` was just inserted for the first time
- `false` if the `vertex` already existed in the graph

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time (Average); *O(n)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices

----

```cpp
size_type pop_vertex(vertex_type& vertex)
```

**Parameters**:
- `vertex` a vertex to remove from the graph

**Returns**: the sum of the number of edges to `vertex` and the number of vertices with label `vertex` that existed in graph prior to removing `vertex`

**Throws**: *None*

**Time Complexity**: *O(n)* &ndash; Linear Time (Average Case); *O(nm)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices
- *m* is the average number of edges in each adjacency list

----

```cpp
std::pair<edge_iterator, bool> push_edge(const vertex_type& source, const vertex_type& destination, const weight_type& weight)
```

**Parameters**:
- `source` a vertex in the graph at which the edge will begin
- `destination` a vertex at which the edge will end (need not yet exist in the graph)
- `weight` the weight of the newly created edge

**Returns**:
- an `iterator` to the inserted edge within the adjacency list of source, or existing edge if the edge already existed
- `true` if the edge was just inserted for the first time
- `false` if the vertex already existed in the graph

**Throws**:
- `std::out_of_range` if `source` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average Case); *O(n+m)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices
- *m* is the average number of edges in each adjacency list

----

```cpp
size_type pop_edge(const vertex_type& source, const vertex_type& destination)
```

**Parameters**:
- `source` a vertex in the graph at which the edge will begin
- `destination` a vertex at which the edge will end (need not exist in the graph)

**Returns**:
- `0` if the edge did not exist in the graph
- `1` if the edge existed in the graph

**Throws**:
- `std::out_of_range` if `source` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average Case); *O(n+m)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices
- *m* is the average number of edges in each adjacency list

----

```cpp
iterator begin()
```

**Parameters**: *None*

**Returns**: `iterator` to the beginning vertex in the graph. This could be any given vertex within the graph, because `unordered_map` can order the vertices however it likes.

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
const_iterator begin() const
```

**Parameters**: *None*

**Returns**: `const_iterator` to the beginning vertex in the graph. This could be any given vertex within the graph, because `unordered_map` can order the vertices however it likes.

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
const_iterator cbegin() const
```

**Parameters**: *None*

**Returns**: `const_iterator` to the beginning vertex in the graph. This could be any given vertex within the graph, because `unordered_map` can order the vertices however it likes.

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
iterator end()
```

**Parameters**: *None*

**Returns**: `iterator` past the last vertex in the graph. This is the same `end` iterator we've seen for `unordered_map`.

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
const_iterator end() const
```

**Parameters**: *None*

**Returns**: `const_iterator` past the last vertex in the graph. This is the same `end` iterator we've seen for `unordered_map`.

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
const_iterator cend() const
```

**Parameters**: *None*

**Returns**: `const_iterator` past the last vertex in the graph. This is the same `cend` iterator we've seen for `unordered_map`.

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
edge_iterator begin(const vertex_type& vertex)
```

**Parameters**:
- `vertex` a vertex in the graph to examine

**Returns**: `edge_iterator` to the beginning of the adjacency list for `vertex` in the graph. This could be any given edge within the list, because `unordered_map` can order the edges however it likes.

**Throws**:
- `std::out_of_range` if `vertex` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average); *O(n)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices

----

```cpp
const_edge_iterator begin(const vertex_type& vertex) const
```

**Parameters**:
- `vertex` a vertex in the graph to examine

**Returns**: `const_edge_iterator` to the beginning of the adjacency list for `vertex` in the graph. This could be any given edge within the list, because `unordered_map` can order the edges however it likes.

**Throws**:
- `std::out_of_range` if `vertex` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average); *O(n)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices

----

```cpp
const_edge_iterator cbegin(const vertex_type& vertex) const
```

**Parameters**:
- `vertex` a vertex in the graph to examine

**Returns**: `const_edge_iterator` to the beginning of the adjacency list for `vertex` in the graph. This could be any given edge within the list, because `unordered_map` can order the edges however it likes.

**Throws**:
- `std::out_of_range` if `vertex` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average); *O(n)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices

----

```cpp
edge_iterator end(const vertex_type& vertex)
```

**Parameters**:
- `vertex` a vertex in the graph to examine

**Returns**: `edge_iterator` past the last edge in the adjacency list of `vertex` in the graph. This is the same `end` iterator we've seen for `unordered_map`.

**Throws**:
- `std::out_of_range` if `vertex` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average); *O(n)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices

----

```cpp
const_edge_iterator end(const vertex_type& vertex) const
```

**Parameters**:
- `vertex` a vertex in the graph to examine

**Returns**: `const_edge_iterator` past the last edge in the adjacency list of `vertex` in the graph. This is the same `end` iterator we've seen for `unordered_map`.

**Throws**:
- `std::out_of_range` if `vertex` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average); *O(n)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices

----

```cpp
const_edge_iterator cend(const vertex_type& vertex) const
```

**Parameters**:
- `vertex` a vertex in the graph to examine

**Returns**: `const_edge_iterator` past the last edge in the adjacency list of `vertex` in the graph. This is the same `cend` iterator we've seen for `unordered_map`.

**Throws**:
- `std::out_of_range` if `vertex` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average); *O(n)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices

----

```cpp
void clear()
```

**Description**: Clears every vertex and its corresponding adjacency list from the graph. Resets the graph to an empty state.

**Parameters**: *None*

**Returns**: *None*

**Throws**: *None*

**Time Complexity**: *O(nm)* &ndash; Linear Time
- *n* is the number of vertices
- *m* is the average number of edges in each adjacency list

----

```cpp
void clear(const vertex_type& vertex)
```

**Description**: Clears every edge from the adjacency list of `vertex`. Resets the adjacency list of `vertex` to an empty state.

**Parameters**:
- `vertex` a vertex in the graph to test

**Returns**: *None*

**Throws**:
- `std::out_of_range` if `vertex` is not in the graph

**Time Complexity**: *O(n+m)* &ndash; Linear Time
- *n* is the number of vertices
- *m* is the average number of edges in each adjacency list


### Implement Topological Sort


### Implement Dijkstra's Algorithm

#### Further Reading
- []()


### Application of Graphs & Graph Algorithms



## Run Tests

**First consult this guide: [`tests/README.md`](./tests/README.md)**

To run the tests, you need to rename [`main.cpp`](./src/main.cpp) or you need to rename the `int main` function within that file.

Execute the following commands from the `assignment-unordered-map` folder to accomplish what you need:

**Build all of the tests**
```sh
make -C tests -j12 build-all
```

**Run the test called `<test-name>`.** Replace `<test-name>` with the name of any `.cpp` file in the [`./tests/tests`](./tests/tests) folder.
```sh
make -C tests -j12 run/<test-name>
```

**Run every test** in the [`./tests/tests`](./tests/tests) folder.
```sh
make -C tests -j12 run-all -k
```

**Debugging tests** &ndash; For a detailed view, see [./tests/README.md](./tests/README.md).
```sh
make -C tests -j12 build-all -k
cd tests/build
gdb <test-name>
cd ../..
```
> Alex recommends you use `cgdb` which has the same commands as `gdb` but a better user interface. You can install it with `sudo apt install cgdb` on `WSL` or `brew install cgdb` on `MacOS` (provided you have [brew](https://brew.sh))

The first command builds the tests, the next enters the folder where the tests were build. The third invokes `gdb` (**use `lldb` if on Mac OSX**) which is used to debug the program by examining Segmentation Faults and running code line-by-line. Finally, the last command takes you back to the top-level directory.


## Incremental Testing:



## Turn In

Submit the following file **and no other files** to Gradescope:
- [ ] [`UnorderedMap.h`](src/UnorderedMap.h)
- [ ] [`primes.h`](src/primes.h)
- [ ] [`primes.cpp`](src/primes.cpp)
