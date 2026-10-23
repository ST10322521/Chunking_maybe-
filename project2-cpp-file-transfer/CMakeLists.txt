cmake_minimum_required(VERSION 3.20)
project(file_transfer_app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(file_transfer src/file_transfer.cpp)
target_include_directories(file_transfer PUBLIC include)
find_package(CURL REQUIRED)
target_link_libraries(file_transfer PUBLIC CURL::libcurl)

add_executable(file_transfer_app app/main.cpp)
target_link_libraries(file_transfer_app PRIVATE file_transfer)
