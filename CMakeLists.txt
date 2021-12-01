cmake_minimum_required(VERSION 3.20)
project(minishell C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_DL_LIBS -lreadline)

FILE(GLOB SRCS "src/*.c")

include_directories(inc)

add_executable(minishell ${SRCS})

target_link_libraries(minishell ${CMAKE_DL_LIBS})