cmake_minimum_required(VERSION 2.8.12)
project(tlog)

add_library(tlog SHARED)
target_sources(tlog PRIVATE tlog.c)

install(TARGETS tlog 
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES tlog.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
