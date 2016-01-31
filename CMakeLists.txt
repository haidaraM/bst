cmake_minimum_required(VERSION 3.3)
project(bst)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -ansi -ggdb")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

# Select your bst type
#add_definitions(-DAVL)
add_definitions(-DRBT)

enable_testing()

file(GLOB_RECURSE SOURCE_FILES src/*)

add_executable(bst ${SOURCE_FILES})