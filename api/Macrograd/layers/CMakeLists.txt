set(TARGET_NAME Layers)

project(Layers VERSION 1.0)

add_subdirectory(buildingblocks)
add_subdirectory(operators)
add_subdirectory(lossfns)
add_subdirectory(learningrates)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${TARGET_NAME} LayerUtils.cpp Linear.cpp)

target_link_libraries(${TARGET_NAME} PRIVATE BuildingBlocks Operators)
target_include_directories(${TARGET_NAME} PUBLIC 
        ./buildingblocks
        ./operators)

target_link_libraries(${TARGET_NAME} 
        PRIVATE BuildingBlocks Operators)
