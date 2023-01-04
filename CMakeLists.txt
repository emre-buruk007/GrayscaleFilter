cmake_minimum_required(VERSION 3.5.1)

project(GrayscaleFilter)

set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

#generate project binary
add_executable(
        ${PROJECT_NAME}

        ${SRC_DIR}/main.c

        ${LIB_DIR}/lodepng.c

        ${INC_DIR}/lodepng.h

)


target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        ${INC_DIR}
)
