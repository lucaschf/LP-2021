cmake_minimum_required(VERSION 3.17)
project(test)

set(CMAKE_CXX_STANDARD 14)

add_executable(test Product.cpp
        Product.h
        ProductList.cpp
        ProductList.h
        Program.cpp
        Program.h
        Source.cpp
        Stock.cpp
        Stock.h)