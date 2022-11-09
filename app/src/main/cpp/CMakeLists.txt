cmake_minimum_required(VERSION 3.18.1)

project("cppsurfaceviewtrans")

add_library( testlib SHARED CppSurfaceView.cpp )

find_library( log-lib log )

target_link_libraries( testlib ${log-lib} android EGL GLESv2 m )
