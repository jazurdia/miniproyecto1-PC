cmake_minimum_required(VERSION 3.25)
project(MiniProyecto C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")

add_executable(MiniProyecto main.c ecosystem/ecosystem.h entities/entities.h configs.h
        ecosystem/ecosystem.c
        entities/entities.c)
