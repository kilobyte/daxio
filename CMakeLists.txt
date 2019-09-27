cmake_minimum_required(VERSION 3.12)
project(daxio C)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif (NOT CMAKE_BUILD_TYPE)

set(LIBS ndctl daxctl pmem)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

add_executable(daxio daxio.c dimm_ndctl.c util.c)
target_link_libraries(daxio ${LIBS})

set(DAX1 "" CACHE STRING "test dax device 1")
set(DAX2 "" CACHE STRING "test dax device 2")

enable_testing()
add_subdirectory(tests)

install(TARGETS daxio
	RUNTIME DESTINATION bin)

find_program(PANDOC NAMES pandoc)
if(NOT PANDOC)
        message(WARNING "pandoc not found - documentation will not be generated")
endif()

if (PANDOC)
	add_subdirectory(doc)
	install(FILES ${CMAKE_CURRENT_BINARY_DIR}/doc/daxio.1
		DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)
endif()
