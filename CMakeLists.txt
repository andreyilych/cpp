cmake_minimum_required(VERSION 3.11)
project("cpp")

set(CMAKE_CXX_STANDARD 20)

aux_source_directory("." SOURCES)
foreach(FILE ${SOURCES})
    set(RUN_NAME "${FILE}")
    string(REPLACE "./" "" RUN_NAME "${RUN_NAME}")
    string(REPLACE ".cpp" "" RUN_NAME "${RUN_NAME}")
    add_executable("run${RUN_NAME}" ${FILE})
endforeach()
