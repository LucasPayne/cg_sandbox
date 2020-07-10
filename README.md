
Getting source files
================
```
git clone {this_repo}
cd {repo_name}
# Install library dependencies.
git submodule update --init --recursive
```

Building the project on Linux
================
```
# Terminal open at project root directory.
mkdir build
cd build
# Make sure CMake is installed first.
cmake ..
make
./cg_sandbox
```


