cmake_minimum_required(VERSION 3.10)
project(api_openweathermap)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(executable_file run)

message(STATUS "Author  :  DUCANHKHUONG")
message(STATUS "Configuring project  :  ${PROJECT_NAME}")

#link library from folder /lib
include_directories(${CMAKE_SOURCE_DIR}/lib/curl)
include_directories(${CMAKE_SOURCE_DIR}/lib/nlohmann)


#find library or curl
find_package(CURL REQUIRED)
message(STATUS "find package or curl : ${CURL_LIBRARIES}")


#file(GLOB LIB_SOURCES "${CMAKE_SOURCE_DIR}/lib/curl/*.h")
#foreach(SOURCE_FILE ${LIB_SOURCES})
#    message(STATUS "Lib : ${SOURCE_FILE}")
#endforeach()

#build executable file name : run
add_executable(${executable_file} ${CMAKE_SOURCE_DIR}/main/main.cpp)
target_link_libraries(${executable_file} ${CURL_LIBRARIES})
message(STATUS "build complete . . .")