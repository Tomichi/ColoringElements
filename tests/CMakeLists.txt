PROJECT("ColoringElementsTests")

add_executable(${PROJECT_NAME} main.cpp Graph/GraphTest.cpp Graph/ColoringTest.cpp Utils/BitArrayTest.cpp)
#add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PUBLIC gtest)
