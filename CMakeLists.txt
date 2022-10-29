cmake_minimum_required(VERSION 3.10)
project(OpenTouhou)
set(CMAKE_CPP_STANDARD 17)

# Use SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(OpenTouhou
   src/main.cpp
   src/parser/PBG3.cpp
   src/parser/BinaryReader.cpp
)

target_compile_features(OpenTouhou PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_include_directories(OpenTouhou PUBLIC src)