cmake_minimum_required(VERSION 3.0.0)
project(SolanaSwapClient VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(CURL REQUIRED)

set(SOURCES
    main.cpp
    src/base58.cpp
)

add_executable(SolanaSwapClient ${SOURCES})
target_include_directories(SolanaSwapClient PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(SolanaSwapClient PRIVATE CURL::libcurl)