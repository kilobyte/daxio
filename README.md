daxio
=====

The main purpose of daxio is to perform I/O on Device DAX devices or zero
a Device DAX device.  Since the standard I/O APIs (read/write) cannot be used
with Device DAX, data transfer is performed on a memory-mapped device.
The daxio may be used to dump Device DAX data to a file, restore data from
a backup copy, or move/copy data to another device.

There must be at least one Device DAX device involved either as the input
or output.  If input or output is not specified, it will default to stdin
or stdout respectively.

No length specified will default to input file/device length or to the
output file/device length, if input is a special char file or stdin.

For a Device DAX device, daxio will attempt to clear badblocks within range
of writes before performing the I/O.


Build dependencies
==================

 * cmake
 * libndctl-dev
 * libdaxctl-dev
 * libpmem-dev
 * pandoc [optional]
