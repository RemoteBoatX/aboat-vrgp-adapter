# minimum required CMake version
cmake_minimum_required(VERSION 3.2)

# build type: debug/release (default debug)
# can switch on the command line with -DCMAKE_BUILD_TYPE={Debug,Release}
IF(DEFINED CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the type of
    build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug
    Release.")
ELSE()
    SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build,
    options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release.")
ENDIF()

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

# set debug flags to pass onto the program when the build type is
# set to debug
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DBUILD_DEBUG")

# include the websocketpp git repo as a directory to search
# for header and source files
include_directories(websocketpp nlohmann)

# add specific macros to the program
add_definitions(-D_WEBSOCKETPP_CPP11_STL_)

# create the executable
add_executable(${EXEC_NAME} src/main.cpp src/adapter_manager.cpp src/websocket_client.cpp src/opendlv_handler.cpp)

# link against the boost system libraries
target_link_libraries(${EXEC_NAME} boost_system)
