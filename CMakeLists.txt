cmake_minimum_required(VERSION 4.0)
project(HTTP_Server C)

set(CMAKE_C_STANDARD 11)

add_executable(HTTP_Server main.c
        methodResolver.h
        methodResolver.c)
