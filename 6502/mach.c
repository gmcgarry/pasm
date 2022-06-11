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

/*
 * Mostek 6500 special routines.
 */

#include "as.h"
#include "mach.h"
#include "error.h"

extern sect_t sect[];
extern int hash(const char *);

static item_t cseg = { 0, S_UND, 0, ".cseg" };

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
	}
	newsect(&cseg, 0, NULL);
}

void
machfinish(int pass)
{
}

void
branch(int opc, expr_t exp)
{
	int dist;

	dist = exp.val - (DOTVAL + 2);
	if (PASS_RELO && dist > 0 && !(exp.typ & S_DOT))
		dist -= sect[DOTSCT].s_gain;
	if (small(fitb(dist) && (exp.typ & ~S_DOT) == DOTSCT, 3)) {
		emit1(opc);
		emit1(dist);
	} else {
		emit1(opc^0x20);
		emit1(0x03);		/* Skip over ... */
		emit1(0x4C);		/* ... far jump. */
		newrelo(exp.typ, RELO2);
		emit2(exp.val);
	}
}

#ifdef W65C02
void
bbranch(int opc, expr_t zp, expr_t label)
{
	int dist;

	if (PASS_RELO && lowb(zp.val) != zp.val)
		serror("bad zp memref");

	dist = label.val - (DOTVAL + 2);
	if (PASS_RELO && dist > 0 && !(label.typ & S_DOT)) {
		dist -= sect[DOTSCT].s_gain;
		if (!fitb(dist))
			serror("offset too large");
	}
	emit1(opc);
	emit1(zp.val);
	emit1(dist);
}
#endif

void
code(expr_t exp, int opc1, int opc2)
{
	int is_abs = (exp.typ & S_SCTMASK & ~S_VAR) == S_ABS;
	int is_local = (exp.typ & S_SCTMASK) == DOTSCT;
	if (small((is_abs || is_local) && fits_zeropage(exp.val),1)) {
		emit1(opc1);
		emit1(exp.val);
	} else {
		emit1(opc2);
		newrelo(exp.typ, RELO2);
		emit2(exp.val);
	}
}

void
machscr()
{
	static const char Table[] = {
		102,	/*	0	00	NUL	*/
		102,	/*	1	01	SOH	*/
		102,	/*	2	02	STX	*/
		102,	/*	3	03	ETX	*/
		102,	/*	4	04	EOT	*/
		102,	/*	5	05	ENQ	*/
		102,	/*	6	06	ACK	*/
		102,	/*	7	07	BEL	*/
		31,	/*	8	08	BS	*/
		102,	/*	9	09	HT	*/
		102,	/*	10	0A	LF	*/
		102,	/*	11	0B	VT	*/
		102,	/*	12	0C	FF	*/
		102,	/*	13	0D	CR	*/
		102,	/*	14	0E	SO	*/
		102,	/*	15	0F	SI	*/
		102,	/*	16	10	DLE	*/
		102,	/*	17	11	DC1	*/
		102,	/*	18	12	DC2	*/
		102,	/*	19	13	DC3	*/
		102,	/*	20	14	DC4	*/
		102,	/*	21	15	NAK	*/
		102,	/*	22	16	SYN	*/
		102,	/*	23	17	ETB	*/
		102,	/*	24	18	CAN	*/
		102,	/*	25	19	EM	*/
		102,	/*	26	1A	SUB	*/
		102,	/*	27	1B	ESC	*/
		102,	/*	28	1C	FS	*/
		102,	/*	29	1D	GS	*/
		102,	/*	30	1E	RS	*/
		102,	/*	31	1F	US	*/
		32,	/*	32	20	space	*/
		33,	/*	33	21	!	*/
		34,	/*	34	22	"	*/
		35,	/*	35	23	#	*/
		36,	/*	36	24	$	*/
		37,	/*	37	25	%	*/
		38,	/*	38	26	&	*/
		39,	/*	39	27	'	*/
		40,	/*	40	28	(	*/
		41,	/*	41	29	)	*/
		42,	/*	42	2A	*	*/
		43,	/*	43	2B	+	*/
		44,	/*	44	2C	,	*/
		45,	/*	45	2D	-	*/
		46,	/*	46	2E	.	*/
		47,	/*	47	2F	/	*/
		48,	/*	48	30	0	*/
		48,	/*	49	31	1	*/
		49,	/*	50	32	2	*/
		50,	/*	51	33	3	*/
		51,	/*	52	34	4	*/
		52,	/*	53	35	5	*/
		53,	/*	54	36	6	*/
		54,	/*	55	37	7	*/
		55,	/*	56	38	8	*/
		56,	/*	57	39	9	*/
		58,	/*	58	3A	:	*/
		59,	/*	59	3B	;	*/
		60,	/*	60	3C	<	*/
		61,	/*	61	3D	=	*/
		62,	/*	62	3E	>	*/
		63,	/*	63	3F	?	*/
		0,	/*	64	40	@	*/
		1,	/*	65	41	A	*/
		2,	/*	66	42	B	*/
		3,	/*	67	43	C	*/
		4,	/*	68	44	D	*/
		5,	/*	69	45	E	*/
		6,	/*	70	46	F	*/
		7,	/*	71	47	G	*/
		8,	/*	72	48	H	*/
		9,	/*	73	49	I	*/
		10,	/*	74	4A	J	*/
		11,	/*	75	4B	K	*/
		12,	/*	76	4C	L	*/
		13,	/*	77	4D	M	*/
		14,	/*	78	4E	N	*/
		15,	/*	79	4F	O	*/
		16,	/*	80	50	P	*/
		17,	/*	81	51	Q	*/
		18,	/*	82	52	R	*/
		19,	/*	83	53	S	*/
		20,	/*	84	54	T	*/
		21,	/*	85	55	U	*/
		22,	/*	86	56	V	*/
		23,	/*	87	57	W	*/
		24,	/*	88	58	X	*/
		25,	/*	89	59	Y	*/
		26,	/*	90	5A	Z	*/
		27,	/*	91	5B	[	*/
		102,	/*	92	5C	\	*/
		29,	/*	93	5D	]	*/
		102,	/*	94	5E	^	*/
		102,	/*	95	5F	_	*/
		102,	/*	96	60	`	*/
		1,	/*	97	61	a	*/
		2,	/*	98	62	b	*/
		3,	/*	99	63	c	*/
		4,	/*	100	64	d	*/
		5,	/*	101	65	e	*/
		6,	/*	102	66	f	*/
		7,	/*	103	67	g	*/
		8,	/*	104	68	h	*/
		9,	/*	105	69	i	*/
		10,	/*	106	6A	j	*/
		11,	/*	107	6B	k	*/
		12,	/*	108	6C	l	*/
		13,	/*	109	6D	m	*/
		14,	/*	110	6E	n	*/
		15,	/*	111	6F	o	*/
		16,	/*	112	70	p	*/
		17,	/*	113	71	q	*/
		18,	/*	114	72	r	*/
		19,	/*	115	73	s	*/
		20,	/*	116	74	t	*/
		21,	/*	117	75	u	*/
		22,	/*	118	76	v	*/
		23,	/*	119	77	w	*/
		24,	/*	120	78	x	*/
		25,	/*	121	79	y	*/
		26,	/*	122	7A	z	*/
		102,	/*	123	7B	{	*/
		102,	/*	124	7C	|	*/
		102,	/*	125	7D	}	*/
		102,	/*	126	7E	~	*/
		102,	/*	127	7F	DEL	*/
	};
	int i;
	char* p;

	p = stringbuf;
	i = stringlen;
	while (--i >= 0)
		emit1(Table[(*p++)&0x7f]);
	emit1(0x00);
}
