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
 * Motorola 68000/68010 tokens
 */

%token <y_word> SIZE
%token <y_word> DREG
%token <y_word> AREG
%token <y_word> MREG
%token <y_word> PC
%token <y_word> CREG
%token <y_word> SPEC
%token <y_word> ABCD
%token <y_word> ADDX
%token <y_word> ADD
%token <y_word> AND
%token <y_word> BITOP
%token <y_word> SHIFT
%token <y_word> SZ_EA
%token <y_word> OP_EA
%token <y_word> OP_NOOP
%token <y_word> OP_EA_D
%token <y_word> LEA
%token <y_word> DBR
%token <y_word> BR
%token <y_word> CMP
%token <y_word> MOVE
%token <y_word> MOVEP
%token <y_word> MOVEM
%token <y_word> MOVEC
%token <y_word> MOVES
%token <y_word> MOVE16
%token <y_word> PMOVE
%token <y_word> SWAP
%token <y_word> LINK
%token <y_word> UNLK
%token <y_word> TRAP
%token <y_word> STOP
%token <y_word> EXG
%token <y_word> OP_EXT
%token <y_word> RTD
%token <y_word> MODEL
%token <y_word> FPCR
%token <y_word> FPREG
%token <y_word> FMOVE
%token <y_word> FMOVECR
%token <y_word> FMOVEM
%token <y_word> FDYADIC
%token <y_word> FMONADIC
%token <y_word> FSINCOS
%token <y_word> FBCC
%token <y_word> FDBCC
%token <y_word> FNOP
%token <y_word> FSCC
%token <y_word> FTST
%token <y_word> FSAVRES
%token <y_word> FTRAPCC
%token <y_word> FSIZE
%token <y_word> CP
%token <y_word> DIVMUL DIVL
%token <y_word> CALLM RTM
%token <y_word> PFLUSH PFLUSHA PTEST PLOAD

%token <y_word> DEFCONST DEFBLOCK DEFZERO

%type <y_word> cdata
%type <y_word> bcdx op_ea regs rrange 
%type <y_word> reg sizedef sizenon creg
%type <y_word> fsize fregs fcregs frlist frrange mask
