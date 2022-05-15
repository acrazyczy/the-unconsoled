cmake_minimum_required(VERSION 3.21)
project(the_unconsoled)

set(CMAKE_CXX_STANDARD 17)

add_executable(the_unconsoled main.cpp TS.cpp TS.hpp BA.cpp BA.hpp LTL.cpp LTL.hpp Tools.cpp Tools.hpp PowerSet.hpp)
