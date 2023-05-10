cmake_minimum_required(VERSION 3.24.2)
project(IGL)
set(CMAKE_CXX_STANDARD 20)


# Functions for library linking

function(auto_link_libraries TO_WHAT [...])
    find_package(PkgConfig)
    foreach(i RANGE 1 ${ARGC}-1)
        pkg_check_modules(LIB_${ARGV${i}} REQUIRED ${ARGV${i}})
        target_link_libraries(${TO_WHAT} ${LIB_${ARGV${i}}_LIBRARIES})
    endforeach()
endfunction()

function(link_library TO_WHAT INCLUDE_DIRECTORY LIBRARY_FILE)
    include_directories(${INCLUDE_DIRECTORY})
    set(LIB_${LIBRARY_FILE} ${LIBRARY_FILE})
    target_link_libraries(${TO_WHAT} ${LIB_${LIBRARY_FILE}})
endfunction()


include_directories(include)


#add_compile_definitions(IGL_COMPILE)
#add_compile_definitions(IGL_DEBUG)


# SOURCE FILES

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


# LIBRARY

add_library(${CMAKE_PROJECT_NAME} ${HEADERS} ${SOURCE_FILES})


# EXECUTABLE

add_executable(TEST ${HEADERS} ${SOURCE_FILES} ${TEST_FILES})


# LIBRARIES

# libs for lib
auto_link_libraries(${CMAKE_PROJECT_NAME} gl opengl glfw3 glew)
target_link_libraries(${CMAKE_PROJECT_NAME} ${CMAKE_DL_LIBS})
link_library(${CMAKE_PROJECT_NAME} /usr/include/SOIL /usr/lib/libSOIL.so)
link_library(${CMAKE_PROJECT_NAME} /usr/include/boost /usr/lib/x86_64-linux-gnu/libboost_system.so)

# libs for exe
auto_link_libraries(TEST gl opengl glfw3 glew)
target_link_libraries(TEST ${CMAKE_DL_LIBS})
link_library(TEST /usr/include/SOIL /usr/lib/libSOIL.so)
link_library(TEST /usr/include/boost /usr/lib/x86_64-linux-gnu/libboost_system.so)