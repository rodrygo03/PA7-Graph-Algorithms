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
