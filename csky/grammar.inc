/*-
 * Copyright (c) 2021 Gregory McGarry <g.mcgarry@ieee.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/* CSKY ISA User Guide_v1.15.17-opensource.doc */

#define MASK(x,n)       (((1<<n)-1)&(x))
#define BITS(x,n,s)     (MASK(x,n)<<(s))

#define JTYPE(op,offset)                0x0000|BITS(op,4,10)|BITS(offset,10,0)
#define ITYPE3(op,rx,rz,imm3,sop)       0x4000|BITS(op,3,11)|BITS(rx,3,8)|BITS(rz,3,5)|BITS(imm3,3,2)|BITS(sop,2,0)
#define ITYPE5_1(op,rx,rz,imm5)         0x4000|BITS(op,3,11)|BITS(rx,3,8)|BITS(rz,3,5)|BITS(imm5,5,0)
#define ITYPE5_2(op,rx,rz,imm5)         0x8000|BITS(op,3,11)|BITS(rx,3,8)|BITS(rz,3,5)|BITS(imm5,5,0)
#define ITYPE5_3(op,rx,sop,imm5)        0x0000|BITS(op,3,11)|BITS(rx,3,8)|BITS(sop,3,5)|BITS(imm5,5,0)
#define ITYPE7(op,rx,soprz,imm7)        0x0000|BITS(op,4,10)|BITS(imm7>>5,2,8)|BITS(soprz,3,5)|BITS(imm7,5,0)
#define ITYPE8_1(op,rxrz,imm8)          0x0000|BITS(op,3,11)|BITS(rxrz,3,8)|BITS(imm8,8,0)
#define ITYPE8_2(op,rz,imm8)            0x8000|BITS(op,3,11)|BITS(imm8>>5,3,8)|BITS(rz,3,5)|BITS(imm8,5,0)

#define RTYPE3(op,rx,rz,ry,sop)         0x4000|BITS(op,3,11)|BITS(rx,3,8)|BITS(rz,3,5)|BITS(ry,3,2)|BITS(sop,2,0)
#define RTYPE2(op,rzry,rx,sop)          0x4000|BITS(op,4,10)|BITS(rzry,4,6)|BITS(rx,4,2)|BITS(sop,2,0)

operation
	: IMPL					{ emit2($1); }
	;
