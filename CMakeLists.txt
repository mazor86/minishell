cmake_minimum_required(VERSION 3.17)
<<<<<<< HEAD
project(minishell)

set(CMAKE_CXX_STANDARD 14)
=======
project(minishell C)

set(CMAKE_C_STANDARD 11)
>>>>>>> master

include_directories(.)
include_directories(includes)
include_directories(libft)
include_directories(srcs)

file(GLOB
        CMD "srcs/cmd/*.c")

file(GLOB
        PARSER "srcs/parser/*.c")

file(GLOB
        GENERAL "srcs/general/*.c")

file(GLOB
        LIBFT "libft/*.c")

add_executable(minishell
<<<<<<< HEAD
        ${LIBFT}
        ${PARSER}
        ${GENERAL}
        ${CMD}
=======
        srcs/main.c
        ${LIBFT}
        ${CMD}
        ${PARSER}
        ${GENERAL}
>>>>>>> master
        )
