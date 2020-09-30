cmake_minimum_required(VERSION 3.5)

project(CashFlow LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CashFlow main.cpp
                        coin.cpp
                        coin.h
                        cashregister.cpp
                        cashregister.h
    )
