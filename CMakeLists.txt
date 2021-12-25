cmake_minimum_required(VERSION 3.20)
project(imgTRanformSFML)

set(CMAKE_CXX_STANDARD 23)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "F:/lib/SFML/lib/cmake/SFML")
include_directories(headers F:/lib/SFML/include)
find_package(SFML 2.5 COMPONENTS system window graphics)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
add_executable(imgTRanformSFML main.cpp imgLib/imgTransform.cpp imgLib/imgTransform.hpp)
target_link_libraries(imgTRanformSFML sfml-system sfml-window sfml-graphics)