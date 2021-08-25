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
 * INTEL 80386 tokens
 */

%token PSEUDOOP_CPU
%token PSEUDOOP_USE16
%token PSEUDOOP_USE32
%token PSEUDOOP_USE64
%token <y_word> R64
%token <y_word> R32X
%token <y_word> R32
%token <y_word> R16
%token <y_word> R8
%token RIP
%token <y_word> RSEG
%token <y_word> RSYSCR
%token <y_word> RSYSDR
%token <y_word> RSYSTR
%token <y_word> PREFIX
%token <y_word> ADDOP
%token <y_word> ARPLOP
%token <y_word> BITTEST
%token <y_word> CALFOP
%token <y_word> CALLOP
%token <y_word> ENTER
%token <y_word> EXTEND
%token <y_word> EXTOP
%token <y_word> EXTOP1
%token <y_word> IMUL
%token <y_word> IMULB
%token <y_word> INCOP
%token <y_word> INT
%token <y_word> IOOP
%token <y_word> JOP
%token <y_word> JOP2
%token <y_word> LEAOP
%token <y_word> LEAOP2
%token <y_word> LSHFT
%token <y_word> MOV
%token <y_word> NOOP_1
%token <y_word> NOOP_2
%token <y_word> NOTOP
%token <y_word> PUSHOP
%token <y_word> RET
%token <y_word> ROLOP
%token <y_word> SETCC
%token <y_word> TEST
%token <y_word> XCHG

/* Intel 80[23]87 coprocessor tokens */
%token <y_word> FNOOP
%token <y_word> FMEM
%token <y_word> FMEM_AX
%token <y_word> FST_I
%token <y_word> FST_ST
%token <y_word> FST_ST2
%token <y_word> ST

/* Intel 80486 tokens */
%token <y_word> EXTOPBW
%token <y_word> BSWAP
%type <y_valu> st_i

%type <y_valu> reg
%type <y_valu> const
%type <y_word> XREG
%type <y_word> ACC
