cmake_minimum_required(VERSION 2.6)
project(YaGE)

set(VERSION_MAJOR   0   CACHE STRING "Project major version number.")
set(VERSION_MINOR   1   CACHE STRING "Project minor version number.")
set(VERSION_PATCH   0   CACHE STRING "Project patch version number.")
string(TIMESTAMP VERSION_TWEAK "%y%m%d")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

add_subdirectory(src)
add_subdirectory(doc)

