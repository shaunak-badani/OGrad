add_library(Operators Operator.cpp TanH.cpp Pow.cpp Broadcast.cpp)


target_link_libraries(Operators PRIVATE BuildingBlocks)
target_include_directories(Operators PUBLIC ${PROJECT_SOURCE_DIR}/buildingblocks)