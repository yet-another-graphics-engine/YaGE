set(doxy_langs english chinese)

find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create documentation (requires Doxygen)" ${DOXYGEN_FOUND})

if(BUILD_DOCUMENTATION)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()

	file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc)

	# dev
	set(doxy_lang english)
	set(doxy_src ${PROJECT_SOURCE_DIR}/src/)
    set(doxy_file_out ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.dev)
    set(doxy_out_dir ${CMAKE_CURRENT_BINARY_DIR}/dev/)

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile-dev.in
    			   ${doxy_file_out} @ONLY)
    add_custom_target(doc-dev
		COMMAND ${DOXYGEN_EXECUTABLE} ${doxy_file_out}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating Dev documentation with Doxygen"
        VERBATIM)

	# user
	set(doxy_src ${PROJECT_SOURCE_DIR}/include/yage.h)
	foreach(doxy_lang ${doxy_langs})
		set(doxy_file_out ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.user-${doxy_lang})
		set(doxy_out_dir ${CMAKE_CURRENT_BINARY_DIR}/${doxy_lang}/)

		configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile-user.in
					   ${doxy_file_out} @ONLY)
		add_custom_target(doc-${doxy_lang}
			COMMAND ${DOXYGEN_EXECUTABLE} ${doxy_file_out}
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
			COMMENT "Generating API documentation in ${doxy_lang} with Doxygen"
			VERBATIM)
	endforeach()
endif()
