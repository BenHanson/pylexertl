cmake_minimum_required(VERSION 3.5...3.27)
project(pylexertl LANGUAGES CXX)

add_subdirectory(3rd/pybind11)
pybind11_add_module(pylexertl pylexertl.cpp)
