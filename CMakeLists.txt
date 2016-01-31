cmake_minimum_required(VERSION 3.3)
project(bst)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -ansi -ggdb")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

include_directories(src)

# Select your bst type
#add_definitions(-DAVL)
add_definitions(-DRBT)

enable_testing()

# source files for the all project
file(GLOB_RECURSE SOURCE_FILES src/*)

# executable for main
add_executable(bst_exe ${SOURCE_FILES})

# executable for avl test
add_executable(test_avl test/TestAvl.c src/Avl.c src/Element.c src/Utils.c)
add_test(Test_avl ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_avl)

# executable for rbtree test
add_executable(test_rbtree test/TestRbtree.c src/Rbt.c src/Element.c src/Utils.c)
add_test(Test_rbtree ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_rbtree)

# executable for collection test
add_executable(test_collection test/TestCollection.c src/Avl.c src/Rbt.c src/Utils.c src/Collection.c src/Element.c)
add_test(Test_collection ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_collection)