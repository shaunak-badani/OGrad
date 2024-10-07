set(TARGET_NAME LossFns)

add_library(${TARGET_NAME} MeanSquaredError.cpp RootMeanSquaredError.cpp SoftmaxCrossEntropyLoss.cpp)
target_link_libraries(${TARGET_NAME} PUBLIC 
        Operators
        BuildingBlocks
    )

target_include_directories(${TARGET_NAME} PUBLIC
        ${PROJECT_SOURCE_DIR}/buildingblocks 
        ${PROJECT_SOURCE_DIR}/operators)