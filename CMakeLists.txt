cmake_minimum_required (VERSION 2.8)

add_definitions(-std=c++11)

project(main)

aux_source_directory(. MAIN_SRCS)
aux_source_directory(src ONEURL_SRCS)


include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 指定生成目标
add_executable(main ${MAIN_SRCS} ${ONEURL_SRCS})