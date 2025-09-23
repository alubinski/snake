cmake_minimum_required(VERSION 3.16)
project(Snake VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(engine)
add_subdirectory(snake)

add_executable(Snake
    "main.cpp"
)

target_include_directories(Snake PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(Snake PRIVATE engine snake)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

target_link_libraries(Snake PRIVATE SDL2 SDL2_image SDL2_ttf)

if(WIN32)
    target_link_libraries(Snake PRIVATE SDL2main)
endif()


set(AssetsDir "${CMAKE_SOURCE_DIR}/assets")
add_custom_command(TARGET Snake POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${AssetsDir}/Rubik-SemiBold.ttf"
    "${AssetsDir}/apple.png"
    $<TARGET_FILE_DIR:Snake>
    VERBATIM
)

