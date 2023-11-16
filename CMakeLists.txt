cmake_minimum_required(VERSION 3.22)
project(r305 C)

set(CMAKE_C_STANDARD 11)

add_executable(
        r305
        src/tp1/queue_and_stack_operations.c
        src/tp1/queue_and_stack_operations.h
        src/tp2/archiver.c
        src/tp2/unarchiver.c
        src/tp2/unarchiver.h
        src/tp2/archiver.h
        src/tp3/tp3.h
        src/tp3/tp3.c
)
