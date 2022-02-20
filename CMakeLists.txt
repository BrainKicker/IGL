cmake_minimum_required(VERSION 3.21)

project(IGL)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

#add_compile_definitions(IGL_COMPILE)
#add_compile_definitions(IGL_DEBUG)

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "include/IGL/*.h" "include/IGL/*.hpp")
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "src/IGL/*.cpp")
file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS "test/IGL/*.h" "test/IGL/*.hpp" "test/IGL/*.cpp")

#if(DEFINED IGL_COMPILE)
    # compile
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
#endif()

#if(DEFINED IGL_DEBUG)
    # debug
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -no-pie -fno-pie -fno-inline-functions")
#endif()

# libs
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lglfw -lGLEW -lGL -lSOIL -lboost_system -ldl")

add_library(IGL ${HEADERS} ${SOURCE_FILES})

add_executable(TEST ${HEADERS} ${SOURCE_FILES} ${TEST_FILES})