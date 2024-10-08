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
