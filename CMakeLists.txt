cmake_minimum_required(VERSION 3.12)
project(daxio C)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif (NOT CMAKE_BUILD_TYPE)

set(LIBS ndctl daxctl pmem)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

add_executable(daxio daxio.c dimm_ndctl.c util.c)
target_link_libraries(daxio ${LIBS})

#enable_testing()
#add_subdirectory(tests)

install(TARGETS daxio
	RUNTIME DESTINATION bin)
