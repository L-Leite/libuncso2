cmake_minimum_required(VERSION 3.13.0)

project(LibPkgTests LANGUAGES CXX)

set(PKG_LIB_CATCH_DIR "${PKG_LIBS_DIR}/catch2")
set(PKG_LIB_CATCH_HEADER_DIR "${PKG_LIB_CATCH_DIR}/single_include")

message(STATUS "Building tests")

set(PKG_TESTS_CSO2_NEXON_SOURCES
    "cso2/nexon/test_encfile.cpp"
    "cso2/nexon/test_lzmatex.cpp"
    "cso2/nexon/test_pkgfile.cpp"
    "cso2/nexon/test_pkgindex.cpp"
    "cso2/nexon/settings.hpp")

set(PKG_TESTS_TFO_NEXON_SOURCES
    "tfo/nexon/test_encfile.cpp"
    "tfo/nexon/test_lzmatex.cpp"
    "tfo/nexon/test_pkgfile.cpp"
    "tfo/nexon/test_pkgindex.cpp"
    "tfo/nexon/settings.hpp")

set(PKG_TESTS_SOURCES_BASE "test_main.cpp" "utils.cpp")

set(PKG_TESTS_HEADERS_BASE "utils.hpp")

file(GLOB
     PKG_ALL_SOURCES
     ${PKG_TESTS_SOURCES_BASE}
     ${PKG_TESTS_HEADERS_BASE}
     ${PKG_TESTS_CSO2_NEXON_SOURCES}
     ${PKG_TESTS_TFO_NEXON_SOURCES})

source_group("Source Files" FILES ${PKG_TESTS_SOURCES})

#
# Add executable to build.
#
add_executable(pkg_test ${PKG_ALL_SOURCES})

target_include_directories(pkg_test
                           PRIVATE ${PKG_INCLUDE_DIR}
                                   ${PKG_LIB_CATCH_HEADER_DIR})
target_include_directories(pkg_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(${PKG_LIB_CATCH_DIR} catch)
target_link_libraries(pkg_test Catch2::Catch2)

if(PKG_USE_CLANG_FSAPI)
  target_link_libraries(pkg_test c++abi c++fs)
elseif(NOT MSVC)
  target_link_libraries(pkg_test stdc++fs)
endif()

target_link_libraries(pkg_test uncso2)

# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fcf-protection=full
# -mcet")

#
# Copy files required for the tests
#
file(GLOB PKG_TEST_REQUIRED_FILES "${CMAKE_CURRENT_SOURCE_DIR}/gamefiles/*")

foreach(file ${PKG_TEST_REQUIRED_FILES})
  configure_file(${file} "${CMAKE_CURRENT_BINARY_DIR}/" COPYONLY)
endforeach()
