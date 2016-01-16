cmake_minimum_required(VERSION 3.3)
project(bst)

set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -ansi -ggdb")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

# Select your bst type
add_definitions(-DAVL)
#add_definitions(-DRBT)



set(SOURCE_FILES
        src/Utils.c
        src/Utils.h
        src/Element.c
        src/Element.h
        src/Collection.c
        src/Collection.h
    src/Ascii.c
    src/Ascii.h
    src/Avl.c
    src/Avl.h
    src/main.c src/Rbt.c src/Rbt.h)

add_executable(bst ${SOURCE_FILES})