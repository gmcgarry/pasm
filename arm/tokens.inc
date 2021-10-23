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

%token <y_word> PSEUDOOP_CPU
%token <y_word> PSEUDOOP_ARCH
%token <y_word> PSEUDOOP_EABIATTR
%token <y_word> PSEUDOOP_FPU
%token <y_word> PSEUDOOP_MODE
%token <y_word> PSEUDOOP_CODE
%token <y_word> PSEUDOOP_SYNTAX
#ifdef notyet
%token <y_word> PSEUDOOP_FUNC
%token <y_word> PSEUDOOP_POOL
%token <y_word> PSEUDOOP_CANTUNWIND
#endif
%token <y_word> PSEUDOOP_THUMBFUNC

%token <y_word> COND
%token <y_word> LINK
%token <y_word> EXCHANGE
%token <y_word> BRANCH
%token <y_word> DATA1
%token <y_word> DATA2
%token <y_word> DATA3
%token <y_word> SET
%token <y_word> PEE
%token <y_word> REG
%token <y_word> SHIFT
%token <y_word> RRX
%token <y_word> SDT
%token <y_word> BYTE
%token <y_word> HALF
%token <y_word> TRANS
%token <y_word> BDT
%token <y_word> SWI
%token <y_word> ADR
%token <y_word> MUL
%token <y_word> MLA

%type <y_word> optlink optcond optexch opts optt optp optb optexc reglist rlist
%type <y_word> optsign optpsr optshift shftcnt address offset aoptshift
%type <y_expr> operand

/* thumb */
%token <y_word> STACK
%type <y_word> loreglist lorlist
