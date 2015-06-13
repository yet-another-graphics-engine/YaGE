cmake_minimum_required(VERSION 2.6)
project(YaGE)

set(VERSION_MAJOR   0   CACHE STRING "Project major version number.")
set(VERSION_MINOR   0   CACHE STRING "Project minor version number.")
set(VERSION_PATCH   1   CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

add_subdirectory(src)

set(doxy_langs english chinese)

find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create documentation (requires Doxygen)" ${DOXYGEN_FOUND})

if(BUILD_DOCUMENTATION)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()
    set(doxy_file_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
	file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc)

	# dev
	set(doxy_lang english)
	set(doxy_src ${PROJECT_SOURCE_DIR}/src/)
    set(doxy_file_out ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.dev)
    set(doxy_out_dir ${CMAKE_CURRENT_BINARY_DIR}/doc/dev/)

    configure_file(${doxy_file_in} ${doxy_file_out} @ONLY)
    add_custom_target(doc-dev
		COMMAND ${DOXYGEN_EXECUTABLE} ${doxy_file_out}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating Dev documentation with Doxygen"
        VERBATIM)

	# api
	set(doxy_src ${PROJECT_SOURCE_DIR}/include/yage.h)
	foreach(doxy_lang ${doxy_langs})
		set(doxy_file_out ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.api-${doxy_lang})
		set(doxy_out_dir ${CMAKE_CURRENT_BINARY_DIR}/doc/${doxy_lang}/)

		configure_file(${doxy_file_in} ${doxy_file_out} @ONLY)
		add_custom_target(doc-${doxy_lang}
			COMMAND ${DOXYGEN_EXECUTABLE} ${doxy_file_out}
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
			COMMENT "Generating API documentation in ${doxy_lang} with Doxygen"
			VERBATIM)
	endforeach()
endif()
