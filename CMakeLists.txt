cmake_minimum_required(VERSION 3.12)
set(PROJECT_NAME "Sillyph")
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -O3 -DNDEBUG")
add_subdirectory(sph)
add_subdirectory(external)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME}
  PRIVATE libsph
)