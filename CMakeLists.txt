cmake_minimum_required(VERSION 3.5)
project(encrypt)

set(CMAKE_CXX_STANDARD 11)

set(HEADERS
        encryption.h
        types.h
        )
set(SOURCE
        main.cpp
        )

add_executable(encrypt ${SOURCE} ${HEADERS})