cmake_minimum_required(VERSION 3.26)
project(r305 C)

set(CMAKE_C_STANDARD 11)

add_executable(r305
        tp1/queue_and_stack_operations.c
        tp1/queue_and_stack_operations.h
        tp2/archiver.c
        tp2/unarchiver.c
        tp2/unarchiver.h
        tp2/archiver.h
        tp3/tp3.h
        tp3/tp3.c
)
