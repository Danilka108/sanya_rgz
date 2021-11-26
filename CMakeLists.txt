cmake_minimum_required(VERSION 3.20)
project(sanya_rgz)

set(CMAKE_CXX_STANDARD 14)

add_executable(sanya_rgz main.cpp src/str_num/str_num.cpp src/str_num/str_num.hpp src/config.hpp src/io/io.cpp src/io/io.hpp src/operations/sum.cpp src/operations/sum.hpp src/operations/multiply.cpp src/operations/multiply.hpp src/operations/choose_operation.cpp src/operations/choose_operation.hpp src/operations/divide.cpp src/operations/divide.hpp)
