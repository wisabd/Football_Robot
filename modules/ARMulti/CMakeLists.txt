include_directories(${CMAKE_SOURCE_DIR}/include)

set(ARMULTI_SRC arMultiReadConfigFile.c arMultiGetTransMat.c arMultiActivate.c)

add_library(ARMulti STATIC ${ARMULTI_SRC})
