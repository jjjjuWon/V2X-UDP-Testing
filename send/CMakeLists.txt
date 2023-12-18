project(send)

get_filename_component(SEND_PROJECT_PATH "${CMAKE_SOURCE_DIR}/send" ABSOLUTE)
set(SEND_INCLUDE_PATH "${SEND_PROJECT_PATH}/include")

# add_library(${PROJECT_NAME}
#     src/send.cpp
# )

add_executable(${PROJECT_NAME}
    src/send_main.cpp
    src/send.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        spdlog::spdlog
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${SEND_INCLUDE_PATH}  # send 프로젝트의 include 디렉토리 포함
    PRIVATE
        ${SEND_PROJECT_PATH}/src  # send 프로젝트의 src 디렉토리 포함
)
