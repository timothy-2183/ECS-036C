
cmake_minimum_required(Version 3.0.0)
project(MyVectorProject VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(MyVectorProject stack_vector.h)

set_property(TARGET MyVectorProject PROPERTY CXX_STANDARD 11)