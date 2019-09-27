/*
 * Copyright 2014-2019, Intel Corporation
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *
 *     * Neither the name of the copyright holder nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * util.c -- very basic utilities
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <endian.h>
#include <errno.h>
#include <time.h>
#include <stdint.h>

#include "util.h"

struct suff {
	const char *suff;
	uint64_t mag;
};

/*
 * util_parse_size -- parse size from string
 */
int
util_parse_size(const char *str, size_t *sizep)
{
	const struct suff suffixes[] = {
		{ "B", 1ULL },
		{ "K", 1ULL << 10 },		/* JEDEC */
		{ "M", 1ULL << 20 },
		{ "G", 1ULL << 30 },
		{ "T", 1ULL << 40 },
		{ "P", 1ULL << 50 },
		{ "KiB", 1ULL << 10 },		/* IEC */
		{ "MiB", 1ULL << 20 },
		{ "GiB", 1ULL << 30 },
		{ "TiB", 1ULL << 40 },
		{ "PiB", 1ULL << 50 },
		{ "kB", 1000ULL },		/* SI */
		{ "MB", 1000ULL * 1000 },
		{ "GB", 1000ULL * 1000 * 1000 },
		{ "TB", 1000ULL * 1000 * 1000 * 1000 },
		{ "PB", 1000ULL * 1000 * 1000 * 1000 * 1000 }
	};

	int res = -1;
	unsigned i;
	size_t size = 0;
	char unit[9] = {0};

	int ret = sscanf(str, "%zu%8s", &size, unit);
	if (ret == 1) {
		res = 0;
	} else if (ret == 2) {
		for (i = 0; i < ARRAY_SIZE(suffixes); ++i) {
			if (strcmp(suffixes[i].suff, unit) == 0) {
				size = size * suffixes[i].mag;
				res = 0;
				break;
			}
		}
	} else {
		return -1;
	}

	if (sizep && res == 0)
		*sizep = size;
	return res;
}
