set(TARGET_NAME Model)

add_library(${TARGET_NAME} Model.cpp ModelBuilder.cpp)

target_include_directories(${TARGET_NAME} PUBLIC 
        ${PROJECT_SOURCE_DIR}/layers/buildingblocks
        ${PROJECT_SOURCE_DIR}/layers/lossfns
        ${PROJECT_SOURCE_DIR}/layers/learningrates
        ${PROJECT_SOURCE_DIR}/layers)

target_link_libraries(${TARGET_NAME}
        PRIVATE BuildingBlocks Layers LossFns LearningRates)
