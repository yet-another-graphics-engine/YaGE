cmake_minimum_required(VERSION 2.6)

if(MSVC AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 17)
    # from Visual Studio 2012, C++11 is supported
else()
    # check c++11 for GCC/Clang from http://www.guyrutenberg.com/2014/01/05/enabling-c11-c0x-in-cmake/
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
    CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
    if(COMPILER_SUPPORTS_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    elseif(COMPILER_SUPPORTS_CXX0X)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    else()
        message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
    endif()
endif()

if(MSVC)
    add_definitions(/W3)
elseif()
    add_definitions(-Wall)
endif()

# specify output path
# from http://stackoverflow.com/a/6595001
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(LIB_SOURCE_FILES yage.cc core/message.cc core/window.cc util/runner.cc dialog/message_dlg.cc dialog/file_chooser_dlg.cc)
add_library(yage STATIC ${LIB_SOURCE_FILES})

# CMake x GTK from https://gist.github.com/fracek/3323924
# Use the package PkgConfig to detect GTK+ headers/library files
FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

# Add other flags to the compiler
ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

project(yagetest)
add_executable(yagetest test.cc)

target_link_libraries(yagetest yage)
target_link_libraries(yagetest ${GTK3_LIBRARIES})

if(MSVC)
    target_link_libraries(yagetest "-lgtk-win32-3.0")
endif()

