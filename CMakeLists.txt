cmake_minimum_required(VERSION 3.5)

project(MP_Lab4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(FILES files.hpp)
set(GENS gens.hpp)

add_executable(MP_Lab4 main.cpp ${FILES} ${GENS})
