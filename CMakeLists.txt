cmake_minimum_required(VERSION 3.3)
project(maze CXX)
include(.cs211/cmake/CMakeLists.txt)

# Defines a variable to stand for the .cxx files that implement
# the model.
set(MODEL_SRC
        src/model.cxx)

# Adds a program named `maze` built from the listed source
# files and the common model files.
add_program(maze
        src/maze.cxx
        src/controller.cxx
        src/view.cxx
        ${MODEL_SRC})
target_link_libraries(maze ge211)

# Adds a test program named `model_test` built from the listed
# source file and the common model files.
add_test_program(model_test
        test/model_test.cxx
        ${MODEL_SRC})
target_link_libraries(model_test ge211)

file(COPY Resources
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# vim: ft=cmake
