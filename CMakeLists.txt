cmake_minimum_required(VERSION 3.17)
project(minishell)

set(CMAKE_CXX_STANDARD 14)

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
        ${LIBFT}
        ${PARSER}
        ${GENERAL}
        ${CMD}
        )
