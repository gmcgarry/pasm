/*
 * Copyright (c) 1987, 1990, 1993, 2005 Vrije Universiteit, Amsterdam, The Netherlands.
 * All rights reserved.
 * 
 * Redistribution and use of the Amsterdam Compiler Kit in source and
 * binary forms, with or without modification, are permitted provided
 * that the following conditions are met:
 * 
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 * 
 *    * Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the documentation and/or other materials provided
 *      with the distribution.
 * 
 *    * Neither the name of Vrije Universiteit nor the names of the
 *      software authors or contributors may be used to endorse or
 *      promote products derived from this software without specific
 *      prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS, AUTHORS, AND
 * CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL VRIJE UNIVERSITEIT OR ANY AUTHORS OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdint.h>

#include "error.h"

#include "out.h"

#ifdef _DEBUG
#define DPRINTF(x)	DPRINTF((x))
#else
#define DPRINTF(x)	/* nothing */
#endif

#define MAX_PARTS	16

static FILE *__parts[MAX_PARTS];
static int nparts = 0;

#define MAXCHUNK	4096

static void
__wr_bytes(FILE* fd, const char *buf, long cnt)
{
	DPRINTF(("__wr_bytes(): cnt=%ld, offset=%ld \n", cnt, ftell(fd)));

	size_t written_bytes;
	while (cnt) {
		int n = cnt >= MAXCHUNK ? MAXCHUNK : cnt;
		written_bytes = fwrite(buf, 1, n, fd);
		if (written_bytes != (size_t)n)
			fatal("write error");
		buf += n;
		cnt -= n;
	}
}

void
wr_seek(int partno, long offset)
{
	DPRINTF(("wr_seek(fp=%p, part=%d, offset=%ld)\n", __parts[partno], partno, offset));
	fseek(__parts[partno], offset, SEEK_SET);
}

void
wr_write(int partno, const void *buf, long n)
{
	DPRINTF(("wr_write(part=%d, len=%ld)\n", partno, n));
	__wr_bytes(__parts[partno], buf, n);
}

void
wr_putc(int partno, int ch)
{
	DPRINTF(("wr_putc(part=%d, ch=%02x)\n", partno, ch & 0xff));
	char c = ch;
	__wr_bytes(__parts[partno], &c, 1);
}


/*
 * Open the output file according to the chosen strategy.
 */
int
wr_open(const char *filename, int n)
{
	int i;

	if (n >= MAX_PARTS)
		return -1;

	DPRINTF(("wr_open(\"%s\")\n", filename));

	fclose(fopen(filename,"wb"));
	for (i = 0; i < n; i++) {
		if ((__parts[i] = fopen(filename, "wb+")) == NULL)
			return -1;
	}

	return 0;
}

void
wr_close(void)
{
	DPRINTF(("wr_close()\n"));

	while (nparts--) {
		fclose(__parts[nparts]);
		__parts[nparts] = NULL;
	}

	DPRINTF(("wr_close() done.\n"));
}
