# DVA338 Lab 1

Welcome to the course! This is the lab skeleton you will use for the initial labs.

## Setup

Here follows installation guides

### Windows

We have prepared a separate document for how to setup Visual Studio with this project.

If you are not using another IDE, the setup process should be quite similar.

If you are not using any IDE, we do recommend you use an IDE.

## CMake

You need to ensure that OpenGL, GLEW and GLUT are installed on your system. Check your favourite package manager for details.

Alternatively you can use the script found in Lab1_setup to download and build freeglut and GLEW from source.

Note: In the following, we assume that the working directory is DVA338_Lab1 which contains the folders ```models```, ```test``` and the code files
```
cmake -S . -B cmakebuild
```

That should generate a folder called cmakebuild, containing the build files. We do **not** do in-source builds using cmake, hence the separate build directory!

Assuming that the Make build system is used the following command should build and run the lab skeleton: ```cd cmakebuild && make && ./DVA338_Lab1```. Should you prefer another build system, `cmake --help` will list the generators available on your setup.

Should something go wrong please run ```cmake -S . -B cmakebuild --trace-source=CMakeLists.txt --trace-expand > DVA338_CMAKE_TRACE``` and then send the generated file DVA338_CMAKE_TRACE to the assistants, along with an explanation of what has gone wrong.

### Rebuilding Tests

Currently, test case code is given as prebuilt libraries. Should there be a reason to rebuild them, you need to set the option `-DDEV_BUILD=ON` to cmake.
