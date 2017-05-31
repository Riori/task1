cmake_minimum_required(VERSION 3.5)
project(encrypt)

set(CMAKE_CXX_STANDARD 11)

set(HEADERS
        encryption.hpp
        types.h
        )
set(MODULES
	encryption.cpp
)

set(SOURCE
        main.cpp
        )

add_executable(encrypt ${SOURCE} ${MODULES} ${HEADERS})