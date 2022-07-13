cmake_minimum_required(VERSION 3.12)
project(asteroids)

set(CMAKE_CXX_STANDARD 20)
set(PROJECT_NAME "asteroids")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")
file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "src/*.hpp")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

set(RESOURCES "font" "sound" "music" "texture")

foreach(RESOURCE IN LISTS RESOURCES)
  add_custom_command(
    TARGET asteroids POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/${RESOURCE}/"
    "${CMAKE_CURRENT_BINARY_DIR}/${RESOURCE}/")
endforeach()
