cmake_minimum_required (VERSION 3.13)
project (BlackBoneNode)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

include_directories(${CMAKE_JS_INC})
include_directories(${CMAKE_JS_INC} "src/3rd_party")
include_directories(${CMAKE_JS_INC} "src/BlackBone")
add_subdirectory(src/BlackBone)

file(GLOB SOURCE_FILES "src/node/blackbone.cc")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})