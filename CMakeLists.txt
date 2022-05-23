cmake_minimum_required(VERSION 3.16)
project(breakout)

include_directories(include)
file(GLOB SRC src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC})

set(CMAKE_CXX_FLAGS -pthread)
target_link_libraries(${PROJECT_NAME} ncurses)
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wno-sign-compare)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)