cmake_minimum_required(VERSION 3.10)

set(TARGET_NAME IOUtils_test)

# Fetching Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

# IOUtils
add_executable(${TARGET_NAME} Test.cpp)
target_link_libraries(${TARGET_NAME} PRIVATE IOUtils GTest::gtest_main GTest::gmock_main)


target_include_directories(${TARGET_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/ioutils)


add_test(NAME ${TARGET_NAME} COMMAND $<TARGET_FILE:${TARGET_NAME}>)

# MathUtils
set(BUILDING_BLOCKS_TARGET_NAME BuildingBlocks_test)
add_executable(${BUILDING_BLOCKS_TARGET_NAME} 
    BuildingBlocksTests.cpp 
    NodeSanityTest.cpp)

target_link_libraries(${BUILDING_BLOCKS_TARGET_NAME} PRIVATE BuildingBlocks GTest::gtest_main GTest::gmock_main)
target_include_directories(${BUILDING_BLOCKS_TARGET_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/layers/buildingblocks)
add_test(NAME ${BUILDING_BLOCKS_TARGET_NAME} COMMAND $<TARGET_FILE:${BUILDING_BLOCKS_TARGET_NAME}>)


# OperatorTests
set(OPERATORS_TARGET_NAME Operators_test)

add_executable(${OPERATORS_TARGET_NAME} OperatorsTest.cpp)
target_link_libraries(${OPERATORS_TARGET_NAME} PRIVATE Operators BuildingBlocks GTest::gtest_main GTest::gmock_main)
target_include_directories(${OPERATORS_TARGET_NAME} 
      PUBLIC 
      ${PROJECT_SOURCE_DIR}/layers/buildingblocks
      ${PROJECT_SOURCE_DIR}/layers/operators)

add_test(NAME ${OPERATORS_TARGET_NAME} COMMAND $<TARGET_FILE:${OPERATORS_TARGET_NAME}>)

# LossFn Tests

set(LOSS_FN_TARGET_NAME LossFns_test)

add_executable(${LOSS_FN_TARGET_NAME} LossFnsTest.cpp)
target_link_libraries(${LOSS_FN_TARGET_NAME} PRIVATE LossFns Layers GTest::gtest_main GTest::gmock_main)

target_include_directories(${LOSS_FN_TARGET_NAME} 
      PUBLIC 
      ${PROJECT_SOURCE_DIR}/layers/buildingblocks
      ${PROJECT_SOURCE_DIR}/layers/operators
      ${PROJECT_SOURCE_DIR}/layers/lossfns
      ${PROJECT_SOURCE_DIR}/layers
      )

add_test(NAME ${LOSS_FN_TARGET_NAME} COMMAND $<TARGET_FILE:${LOSS_FN_TARGET_NAME}>)


# Layers Tests

set(LAYERS_TARGET_NAME Layers_test)

add_executable(${LAYERS_TARGET_NAME} LayersTest.cpp)
target_link_libraries(${LAYERS_TARGET_NAME} PRIVATE Layers GTest::gtest_main GTest::gmock_main)
target_include_directories(${LAYERS_TARGET_NAME} 
      PUBLIC 
      ${PROJECT_SOURCE_DIR}/layers
)
add_test(NAME ${LAYERS_TARGET_NAME} COMMAND $<TARGET_FILE:${LAYERS_TARGET_NAME}>)

# Model test

set(MODEL_TARGET_NAME Model_test)

add_executable(${MODEL_TARGET_NAME} ModelTest.cpp ModelBuilderTest.cpp)
target_link_libraries(${MODEL_TARGET_NAME} PRIVATE Model GTest::gtest_main GTest::gmock_main)
target_include_directories(${MODEL_TARGET_NAME} 
      PUBLIC 
      ${PROJECT_SOURCE_DIR}/model
      ${PROJECT_SOURCE_DIR}/layers/operators
)
add_test(NAME ${MODEL_TARGET_NAME} COMMAND $<TARGET_FILE:${MODEL_TARGET_NAME}>)

# Learning Rates test

set(LR_TARGET_NAME Learning_rates_test)

add_executable(${LR_TARGET_NAME} LearningRatesTest.cpp)
target_link_libraries(${LR_TARGET_NAME} PRIVATE LearningRates GTest::gtest_main GTest::gmock_main)
target_include_directories(${LR_TARGET_NAME} 
      PUBLIC 
      ${PROJECT_SOURCE_DIR}/layers/learningrates
)
add_test(NAME ${LR_TARGET_NAME} COMMAND $<TARGET_FILE:${LR_TARGET_NAME}>)

# DataSetsTest

set(DATASETS_TARGET_NAME DataSetReaders_test)

add_executable(${DATASETS_TARGET_NAME} DataSetReadersTest.cpp)
target_link_libraries(${DATASETS_TARGET_NAME} PRIVATE DataSetReader GTest::gtest_main GTest::gmock_main)
target_include_directories(${DATASETS_TARGET_NAME} 
      PUBLIC 
      ${PROJECT_SOURCE_DIR}/datasetreader
      ${PROJECT_BINARY_DIR}/datasetreader # DataSetsPathConfig
)
add_test(NAME ${DATASETS_TARGET_NAME} COMMAND $<TARGET_FILE:${DATASETS_TARGET_NAME}>)

# BroadcastTest

set(BROADCAST_TEST_TARGET_NAME BroadcastTest)

add_executable(${BROADCAST_TEST_TARGET_NAME} BroadcastTest.cpp)
target_link_libraries(${BROADCAST_TEST_TARGET_NAME} PRIVATE Operators GTest::gtest_main GTest::gmock_main)
target_include_directories(${BROADCAST_TEST_TARGET_NAME} 
      PUBLIC 
      ${PROJECT_SOURCE_DIR}/layers/operators
)
add_test(NAME ${BROADCAST_TEST_TARGET_NAME} COMMAND $<TARGET_FILE:${BROADCAST_TEST_TARGET_NAME}>)

# Vec3DTest

set(VEC3D_TEST_TARGET_NAME Vec3DTest)

add_executable(${VEC3D_TEST_TARGET_NAME} Vec3DTest.cpp)
target_link_libraries(${VEC3D_TEST_TARGET_NAME} PRIVATE BuildingBlocks GTest::gtest_main GTest::gmock_main)
target_include_directories(${VEC3D_TEST_TARGET_NAME} 
      PUBLIC 
      ${PROJECT_SOURCE_DIR}/layers/buildingblocks
)
add_test(NAME ${VEC3D_TEST_TARGET_NAME} COMMAND $<TARGET_FILE:${VEC3D_TEST_TARGET_NAME}>)




