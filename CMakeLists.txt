cmake_minimum_required(VERSION 3.16)
project (Babelsort)


include_directories(${CMAKE_JS_INC})

add_library(${PROJECT_NAME} SHARED src/babelsortEntry.cpp src/CSVParser.cpp ${CMAKE_JS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})