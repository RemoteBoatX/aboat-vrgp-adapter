# minimum required CMake version
cmake_minimum_required(VERSION 3.2)

# project name
project("Aboat VRGP adapter")

# set executable name
set(EXEC_NAME adapter)

# C++14 standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# add the pthread lib
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# include the websocketpp git repo as a directory to search
# for header and source files
include_directories(websocketpp)

# add specific macros to the program
add_definitions(-D_WEBSOCKETPP_CPP11_STL_)

# create the executable
add_executable(${EXEC_NAME} src/main.cpp)

# link against the boost system libraries
target_link_libraries(${EXEC_NAME} boost_system)
