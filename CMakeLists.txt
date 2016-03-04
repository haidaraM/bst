cmake_minimum_required(VERSION 3.3)
project(bst)

# Compilation option
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -ggdb")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_VERBOSE_MAKEFILE on)
include_directories(src)
# Select your bst type
#add_definitions(-DAVL)
add_definitions(-DRBT)

# Test variables
set(AVL_TEST_EXECUTABLE test_avl)
set(RBTREE_EXE_TEST test_rbtree)
set(COLLECTION_TEST_EXECUTABLE test_collection)


enable_testing()

# source files for the all project
file(GLOB_RECURSE SOURCE_FILES src/*)

# executable for main
add_executable(bst_exe ${SOURCE_FILES})

# executable for avl test
add_executable(${AVL_TEST_EXECUTABLE} test/TestAvl.c src/Avl.c src/Element.c src/Utils.c src/TypePackage.c)
add_test(Test_avl ${AVL_TEST_EXECUTABLE})

# executable for rbtree test
add_executable(${RBTREE_EXE_TEST} test/TestRbtree.c src/Rbt.c src/Element.c src/Utils.c src/TypePackage.c)
add_test(Test_rbtree ${RBTREE_EXE_TEST})

# executable for collection test
add_executable(${COLLECTION_TEST_EXECUTABLE} test/TestCollection.c src/Avl.c src/Rbt.c src/Utils.c src/Collection.c src/Element.c src/TypePackage.c)
add_test(Test_collection ${COLLECTION_TEST_EXECUTABLE})