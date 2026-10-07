cmake_minimum_required(VERSION 3.20)

project(superAwesomeLibrary
    LANGUAGES CXX
)

include(GNUInstallDirs)

add_library(superAwesomeLibrary STATIC
    src/superAwesome.cpp
)

target_include_directories(superAwesomeLibrary
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/superAwesome
)

target_compile_features(superAwesomeLibrary PUBLIC cxx_std_20)

add_library(superAwesome::superAwesomeLibrary ALIAS superAwesomeLibrary)

install(TARGETS superAwesomeLibrary
    EXPORT superAwesomeTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(
    FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/superAwesome/superAwesome.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/superAwesome
)

install(EXPORT superAwesomeTargets
    FILE superAwesomeConfig.cmake
    NAMESPACE superAwesome::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/superAwesome
)
