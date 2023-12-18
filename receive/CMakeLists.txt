project(receive)

add_executable(${PROJECT_NAME}
    src/receive_main.cpp
    src/receive.cpp
)

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        spdlog::spdlog
        ${OPENSSL_LIBRARIES}
        # send
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    include
    ${PROJECT_BINARY_DIR}/include
    ${CMAKE_SOURCE_DIR}
    # send 프로젝트의 헤더 파일을 참조하기 위한 경로 추가
    ${CMAKE_SOURCE_DIR}/send/include  
  PRIVATE
    ${PROJECT_BINARY_DIR}/src
)
