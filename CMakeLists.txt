cmake_minimum_required(VERSION 3.8)
project(Serwer)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c functions.c functions.h struct.h operations.c operations.h)
add_executable(Serwer ${SOURCE_FILES} functions.c functions.h operations.c operations.h)