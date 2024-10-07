set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(DataSetReader CSVReader.cpp DataSet.cpp)

configure_file(DataSetsPathConfig.h.in DataSetsPathConfig.h)

target_link_libraries(DataSetReader PRIVATE IOUtils BuildingBlocks)


target_include_directories(DataSetReader PUBLIC
    ${PROJECT_SOURCE_DIR}/ioutils
    ${PROJECT_SOURCE_DIR}/layers/buildingblocks)