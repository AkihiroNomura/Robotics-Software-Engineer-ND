## Project: Build My World

![screenshot](./image/office_screenshot.png)

#### Procedure on Udacity Workspace

```
$ sudo apt-get update && sudo apt-get upgrade -y

$ mkdir build
$ cd build
$ cmake ../
$ make

$ export GAZEBO_PLUGIN_PATH=${GAZEBO_PLUGIN_PATH}:/home/workspace/project1/build

$ cd ..
$ gazebo world/crayon_office
```


#### Directory Structure
```
# tree .
.
├── build
│   ├── CMakeCache.txt
│   ├── CMakeFiles
│   │   ├── 3.5.1
│   │   │   ├── CMakeCCompiler.cmake
│   │   │   ├── CMakeCXXCompiler.cmake
│   │   │   ├── CMakeDetermineCompilerABI_C.bin
│   │   
│   │   :   :
│   │   
│   ├── cmake_install.cmake
│   ├── libhello.so
│   └── Makefile
├── CMakeLists.txt
├── model
│   ├── building
│   │   ├── model.config
│   │   └── model.sdf
│   └── robot
│       ├── model.config
│       └── model.sdf
├── script
│   └── hello.cpp
└── world
    └── crayon_office

13 directories, 41 files
```