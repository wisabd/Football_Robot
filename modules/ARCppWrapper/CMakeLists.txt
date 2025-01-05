include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${EE212_BINARY_DIR}/lib)

set(ARCPP_SRC ARToolKitLib.cpp)

add_library(AR_cpp STATIC ${ARCPP_SRC})
#target_link_libraries(AR_cpp AR ARMulti )
#target_link_libraries(AR_cpp -lAR -lARgsub -lARMulti -lglut)
