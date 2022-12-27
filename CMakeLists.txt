cmake_minimum_required(VERSION 3.5.1)

project(GrayscaleFilter)

set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

#generate project binary
add_executable(
        ${PROJECT_NAME}

        ${SRC_DIR}/main.c

)


target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        ${INC_DIR}
)
