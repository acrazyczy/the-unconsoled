cmake_minimum_required(VERSION 3.21)
project(the_unconsoled)

set(CMAKE_CXX_STANDARD 17)
include_directories(
        ${PROJECT_SOURCE_DIR}/src/
        ${PROJECT_SOURCE_DIR}/src/Parser
        ${PROJECT_SOURCE_DIR}/src/Parser/generated
        ${PROJECT_SOURCE_DIR}/src/BA
        ${PROJECT_SOURCE_DIR}/src/LTL
        ${PROJECT_SOURCE_DIR}/src/TS
        ${PROJECT_SOURCE_DIR}/third_party/
        ${PROJECT_SOURCE_DIR}/third_party/runtime/src
)

set(LTL_model_checking
        src/Parser/generated/LTLlangLexer.cpp
        src/Parser/generated/LTLlangParser.cpp
        src/Parser/generated/LTLlangListener.cpp
        src/Parser/generated/LTLlangBaseListener.cpp
        src/LTL/LTL.cpp
        src/BA/BA.cpp
        src/TS/TS.cpp
        src/Parser/LTLEvalVisitor.cpp
)

set(Tools
        src/Tools.cpp
        src/PowerSet.hpp
)

file(GLOB antlr4-cpp-src
        ${PROJECT_SOURCE_DIR}/third_party/runtime/src/*.cpp
        ${PROJECT_SOURCE_DIR}/third_party/runtime/src/atn/*.cpp
        ${PROJECT_SOURCE_DIR}/third_party/runtime/src/dfa/*.cpp
        ${PROJECT_SOURCE_DIR}/third_party/runtime/src/misc/*.cpp
        ${PROJECT_SOURCE_DIR}/third_party/runtime/src/support/*.cpp
        ${PROJECT_SOURCE_DIR}/third_party/runtime/src/tree/*.cpp
        ${PROJECT_SOURCE_DIR}/third_party/runtime/src/tree/pattern/*.cpp
        ${PROJECT_SOURCE_DIR}/third_party/runtime/src/tree/xpath/*.cpp
)

add_library (antlr4-cpp-runtime ${antlr4-cpp-src})
add_executable(the_unconsoled ${LTL_model_checking} ${Tools} src/main.cpp)
target_link_libraries(the_unconsoled antlr4-cpp-runtime)
