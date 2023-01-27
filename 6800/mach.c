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

#include "as.h"
#include "mach.h"
#include "error.h"

extern sect_t sect[];
extern int hash(const char *);

item_t bseg = { 0, S_UND, 0, ".bss" };
item_t dseg = { 0, S_UND, 0, ".data" };
item_t cseg = { 0, S_UND, 0, ".code" };

void
mflag(const char* flag)
{
}

void
machstart(int pass)
{
	if (pass == PASS_1) {
		item_insert(&cseg, H_GLOBAL+hash(cseg.i_name));
		unresolved++;
		item_insert(&dseg, H_GLOBAL+hash(cseg.i_name));
		unresolved++;
		item_insert(&bseg, H_GLOBAL+hash(cseg.i_name));
		unresolved++;
	}
	newsect(&cseg, 0, NULL);
	newsect(&dseg, 0, NULL);
	newsect(&bseg, 0, NULL);
}

void
machfinish(int pass)
{
}

void
branch(int opc, expr_t exp)
{
	int dist;
#ifdef AUTOCONVERT_LONG_BRANCHES
	int sm, saving
#endif

	dist = exp.val - (DOTVAL + 2);
	if (PASS_RELO && dist > 0 && !(exp.typ & S_DOT))
		dist -= sect[DOTSCT].s_gain;
#ifdef AUTOCONVERT_LONG_BRANCHES
	sm = fitj(dist);
//	printf("PASS %d, dist %u, sm %u\n", pass+1, dist, sm);
	if ((exp.typ & S_SCTMASK) != DOTSCT)
		sm = 0;
	if (opc == 0x8D || (opc & 0xF0) == 0x20)
		saving = 1;
	else
		saving = 3;
	if (small(sm,saving)) {
//		printf("emit short offset\n");
		emit1(opc);
		emit1(dist);
	} else {
//		printf("emit long offset\n");
		if (opc == 0x8D)		/* bsr */
			emit1(0xBD);		/* jsr */
		else {
			if (opc != 0x20) {	/* bra */
				/* reverse condition : */
				emit1(opc ^ 1);
				emit1(3);
			}
			emit1(0x7E);		/* jmp */
		}
#ifdef RELOCATION
		newrelo(exp.typ, RELO2 | RELBR);
#endif
		emit2(exp.val);
	}
#else
	/* ----- */
	/* XXXGJM: This is forcing BRA/BSR to be short, */
	/* since short forward short jumps are incorrected extended */
	/* some monitor code needs to build with known opcode sizes */
	/* ----- */
	fit(fitj(dist));
	emit1(opc);
	emit1(dist);
#endif
}
