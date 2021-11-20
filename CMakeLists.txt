# minimum required CMake version
cmake_minimum_required(VERSION 3.2)

# project name
project("Aboat VRGP adapter")

# set some variables
set(EXEC_NAME adapter)

# C++14 standard
set(CXX_STANDARD C++14)

# include the websocketpp git repo as well as a directory to search
# for header and source files
include_directories(websocketpp)

# create the executable
add_executable(${EXEC_NAME} src/main.cpp)

# link against the boost system libraries
target_link_libraries(${EXEC_NAME} boost_system)
