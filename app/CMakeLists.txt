cmake_minimum_required(VERSION 3.4.1)

include_directories(${CMAKE_SOURCE_DIR}/src/main/cpp/include) #头文件

add_library(libimg SHARED src/main/cpp/native-lib.cpp)

add_library(yuv SHARED IMPORTED)
set_target_properties(yuv PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libyuv.so)

find_library(log-lib log)

target_link_libraries(libimg yuv jnigraphics ${log-lib})