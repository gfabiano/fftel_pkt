cmake_minimum_required(VERSION 3.14)

project(fftel_pkt LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

FetchContent_Declare(
    hmac-sha256
    GIT_REPOSITORY https://github.com/gfabiano/hmac_sha256.git
    GIT_TAG        CMake
)
FetchContent_MakeAvailable(hmac-sha256)

add_library(fftel_pkt STATIC
  fftel_pkt.cpp
  fftel_pkt.h
)

target_include_directories(fftel_pkt PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(fftel_pkt hmac-sha256)
target_compile_definitions(fftel_pkt PRIVATE FFTEL_PKT_LIBRARY)
