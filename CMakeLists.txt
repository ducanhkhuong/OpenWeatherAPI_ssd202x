#cmake_minimum_required(VERSION 3.10)
#project(api_openweathermap)

#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(executable_file run)

#message(STATUS "Author  :  DUCANHKHUONG")
#message(STATUS "Configuring project  :  ${PROJECT_NAME}")

#link library from folder /lib
#include_directories(${CMAKE_SOURCE_DIR}/lib/curl)
#include_directories(${CMAKE_SOURCE_DIR}/lib/nlohmann)


#find library or curl
#find_package(CURL REQUIRED)
#message(STATUS "find package or curl : ${CURL_LIBRARIES}")


#file(GLOB LIB_SOURCES "${CMAKE_SOURCE_DIR}/lib/curl/*.h")
#foreach(SOURCE_FILE ${LIB_SOURCES})
#    message(STATUS "Lib : ${SOURCE_FILE}")
#endforeach()

#build executable file name : run
#add_executable(${executable_file} ${CMAKE_SOURCE_DIR}/main/main.cpp)
#target_link_libraries(${executable_file} ${CURL_LIBRARIES})
#message(STATUS "build complete . . .")


cmake_minimum_required(VERSION 3.0)
project(OpenWeather)

set(CMAKE_CXX_STANDARD 11)

set(STAGING_DIR /home/ducanhkhuong/MT7688_OW19/openwrt/staging_dir)

set(TOOLS_PATH ${STAGING_DIR}/toolchain-mipsel_24kc_gcc-8.3.0_musl)
set(TARGET ${STAGING_DIR}/target-mipsel_24kc_musl)

message(STATUS "STAGING_DIR:=${STAGING_DIR}")
message(STATUS "TOOLS_PATH:=${TOOLS_PATH}")
message(STATUS "TARGET:=${TARGET}")

set(CMAKE_C_COMPILER   ${TOOLS_PATH}/bin/mipsel-openwrt-linux-gcc)
set(CMAKE_CXX_COMPILER ${TOOLS_PATH}/bin/mipsel-openwrt-linux-g++)

set(CMAKE_C_FLAGS   "-I${TARGET}/usr/include -I${TARGET}/usr/include/glib-2.0 -I${TARGET}/usr/lib/glib-2.0/include/ -Wno-deprecated -Wno-psabi ")
set(CMAKE_CXX_FLAGS "-I${TARGET}/usr/include -I${TARGET}/usr/include/glib-2.0 -I${TARGET}/usr/lib/glib-2.0/include/ -Wno-deprecated -Wno-psabi ")

include_directories(${TARGET}/root-ramips/usr/include)

set(CMAKE_SYSROOT ${TARGET})
set(CMAKE_SKIP_BUILD_RPATH TRUE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "${TARGET}/root-ramips/lib/;${TARGET}/usr/lib/")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_SHARED_LIBRARY_RPATH_LINK_C_FLAG "-Wl,-rpath-link,-Wall")

link_directories(${TARGET}/usr/lib)
link_directories(${TARGET}/root-ramips/usr/lib)


find_package(CURL REQUIRED)
link_libraries(CURL::libcurl uci avahi-client avahi-common)
add_executable(OpenWeather ../main/main.cpp)
install(TARGETS OpenWeather RUNTIME DESTINATION bin)
