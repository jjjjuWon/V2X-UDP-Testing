cmake_minimum_required(VERSION 3.10)

project(test_erhalten)

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

add_executable(${PROJECT_NAME}
    src/test.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        spdlog::spdlog
        receive
        send
        ${OPENSSL_LIBRARIES}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_BINARY_DIR}/src
        ${CMAKE_SOURCE_DIR}/send/include
        ${CMAKE_SOURCE_DIR}/receive/include
)
