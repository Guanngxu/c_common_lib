cmake_minimum_required(VERSION 3.10)
project(libcommon VERSION 1.0.0)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -Wextra")
set(APP_NAME common)
set(TOP_DIR ${CMAKE_CURRENT_SOURCE_DIR})
# install dir
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

include_directories(${TOP_DIR}/inc)

# Get all source files
file(GLOB_RECURSE SOURCES
    ${TOP_DIR}/src/*.c
)

add_library(${APP_NAME} SHARED ${SOURCES})

install(TARGETS ${APP_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)