FIND_PACKAGE( Boost 1.53.0 COMPONENTS system regex timer thread chrono )
FIND_PACKAGE( OpenCV REQUIRED )

if(Boost_FOUND AND OpenCV_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    include_directories(${OpenCV_INCLUDE_DIR})
    
    include_directories(${CMAKE_SOURCE_DIR}/src)
    include_directories(${CMAKE_SOURCE_DIR}/include)

    link_directories(${EE212_BINARY_DIR}/lib)
    link_directories(${OpenCV_LIB_DIR})
    link_directories(${Boost_LIBRARY_DIR})

    set(CMAKE_CXX_FLAGS "-W -Wall ${CMAKE_CXX_FLAGS} -std=c++0x -O3 -fopenmp")

	add_executable (Test1_Dynamixel Test1_Dynamixel.cpp)
    target_link_libraries(Test1_Dynamixel -lboost_system -lboost_thread -lpthread)

	add_executable (Test2_Servo Test2_Servo.cpp)
    target_link_libraries(Test2_Servo -lboost_system -lboost_thread -lpthread)

	add_executable (Test3_Perception Test3_Perception.cpp)
    target_link_libraries(Test3_Perception -lAR_cpp -lAR -lARMulti -lboost_system -lboost_thread -lpthread -lopencv_core -lopencv_highgui -lopencv_imgproc)

	add_executable (Test4_Sound Test4_Sound.cpp)
    target_link_libraries(Test4_Sound -lboost_system -lboost_thread -lpthread)

	add_executable (Test5_BehDesign Test5_BehDesign.cpp)
    target_link_libraries(Test5_BehDesign -lboost_system -lboost_thread -lpthread)

	add_executable (Test6_BehMapping Test6_BehMapping.cpp)
    target_link_libraries(Test6_BehMapping -lAR_cpp -lAR -lARMulti -lboost_system -lboost_thread -lpthread -lopencv_core -lopencv_highgui -lopencv_imgproc)

	add_executable (Test7_IntStateDesign Test7_IntStateDesign.cpp)
    target_link_libraries(Test7_IntStateDesign -lAR_cpp -lAR -lARMulti -lboost_system -lboost_thread -lpthread -lopencv_core -lopencv_highgui -lopencv_imgproc)

add_executable (Test8_Android Test8_Android.cpp)
    target_link_libraries(Test8_Android ${Boost_LIBRARIES} -lAR_cpp -lAR -lARMulti -lpthread -lopencv_core -lopencv_highgui -lopencv_imgproc)

endif()



