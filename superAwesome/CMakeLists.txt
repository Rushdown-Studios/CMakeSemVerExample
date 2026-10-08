cmake_minimum_required(VERSION 3.20)

project(superAwesomeLibrary
    # Bump this when you make a change!
    VERSION 1.0.0
    LANGUAGES CXX
)

include(GNUInstallDirs)

set(SUPER_AWESOME_GENERATED_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated)

# Configure CMake to generate the version.h using the current version specified above.
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.h.in
    ${SUPER_AWESOME_GENERATED_DIR}/superAwesome/version.h
)

add_library(superAwesomeLibrary STATIC
    src/superAwesome.cpp
)

target_include_directories(superAwesomeLibrary
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${SUPER_AWESOME_GENERATED_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/superAwesome
        ${SUPER_AWESOME_GENERATED_DIR}/superAwesome
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
        ${SUPER_AWESOME_GENERATED_DIR}/superAwesome/version.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/superAwesome
)

# if pre-1.0.0, minor version bumps may contain breaking changes
set(SUPER_AWESOME_COMPATIBILITY SameMajorVersion)
if(PROJECT_VERSION_MAJOR EQUAL 0)
    set(SUPER_AWESOME_COMPATIBILITY SameMinorVersion)
endif()

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/superAwesomeConfigVersion.cmake
    COMPATIBILITY ${SUPER_AWESOME_COMPATIBILITY}
)

install(EXPORT superAwesomeTargets
    FILE superAwesomeConfig.cmake
    NAMESPACE superAwesome::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/superAwesome
)
