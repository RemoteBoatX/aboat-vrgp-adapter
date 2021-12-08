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

# create the executable
add_executable(${EXEC_NAME} src/VesselClient.cpp src/easywsclient.cpp)
