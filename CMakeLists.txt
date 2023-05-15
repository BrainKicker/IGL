cmake_minimum_required(VERSION 3.24.2)
project(IGL)
set(CMAKE_CXX_STANDARD 20)

include(CMakeLogic.cmake)


#add_compile_definitions(IGL_COMPILE)
#add_compile_definitions(IGL_DEBUG)


#if(DEFINED IGL_COMPILE)
    # compile
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
#endif()

#if(DEFINED IGL_DEBUG)
    # debug
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -no-pie -fno-pie -fno-inline-functions")
#endif()


# DIRECTORIES
set_project_directories(include src test res include lib out)


# LIBRARY
set(LIBRARY_NAME ${CMAKE_PROJECT_NAME})
add_library(${CMAKE_PROJECT_NAME} ${HEADERS} ${SOURCE_FILES})
#add_library(${CMAKE_PROJECT_NAME} SHARED ${HEADERS} ${SOURCE_FILES})


# EXECUTABLE
set(EXECUTABLE_NAME TEST)
add_executable(${EXECUTABLE_NAME} ${HEADERS} ${SOURCE_FILES} ${TEST_FILES})


# LIBRARIES
find_libraries(LIBRARIES gl opengl glfw3 glew ${CMAKE_DL_LIBS} SOIL boost_system)
# libs for lib
target_link_libraries(${LIBRARY_NAME} PRIVATE ${LIBRARIES})
# libs for exe
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${LIBRARIES})