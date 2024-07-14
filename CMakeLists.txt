cmake_minimum_required(VERSION 3.25)
project(Wascan)

set(CMAKE_CXX_STANDARD 17)

add_executable(wascan

        src/main.c
        src/scan.c
        src/strf.c
        src/main.c

)
