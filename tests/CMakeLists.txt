function(skip_test name)
	add_test(NAME SKIPPED_${name} COMMAND true)
endfunction()

if ("${DAX1}" STREQUAL "")
	message(WARNING "DAX1 not set -- skipping all tests")
	skip_test(basic)
	skip_test(negative)
	skip_test(units)
	skip_test(copy)
else()
	add_test(NAME basic COMMAND basic "${DAX1}")
	add_test(NAME negative COMMAND negative "${DAX1}")
	add_test(NAME units COMMAND units "${DAX1}")

	if ("${DAX2}" STREQUAL "")
		message(WARNING "DAX2 not set -- skipping copy test")
		skip_test(copy)
	else()
		add_test(NAME copy COMMAND copy "${DAX1}" "${DAX2}")
	endif()
endif()
