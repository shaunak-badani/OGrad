cmake_minimum_required(VERSION 3.10)

project(Macrograd VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(DATASETS_PATH ${PROJECT_SOURCE_DIR}/datasets)

add_subdirectory(datasets)

add_subdirectory(datasetreader)

add_executable(${PROJECT_NAME} macrograd.cpp model_mediator.cpp output_handler.cpp output_metrics.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC DataSetReader Model LossFns)

target_include_directories(${PROJECT_NAME} PUBLIC 
            "${PROJECT_SOURCE_DIR}/datasetreader"
            ${PROJECT_SOURCE_DIR}/model
            ${PROJECT_SOURCE_DIR}/layers/lossfn
            ${PROJECT_SOURCE_DIR}/layers/operators
            "${PROJECT_BINARY_DIR}/datasetreader" # for datasets path config header file
)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

include(CTest) # We include CTest which is part of CMake
enable_testing()

# add_test(Test_0, "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}")

# Adding test folders:
add_subdirectory(ioutils)
add_subdirectory(tests)
add_subdirectory(layers)
add_subdirectory(model)