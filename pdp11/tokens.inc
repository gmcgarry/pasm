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
* PDP 11 machine dependent yacc declarations
*/
%token <y_word> REG
%token <y_word> FREG
%token <y_word> FRSP
%token <y_word> JMP
%token <y_word> OP_SO
%token <y_word> OP_DO
%token <y_word> OP_R_SO
%token <y_word> BR
%token <y_word> EJMP
%token <y_word> JSR
%token <y_word> RTS
%token <y_word> MARK
%token <y_word> SOB
%token <y_word> SPL
%token <y_word> TRAP
%token <y_word> OP_NO
%token <y_word> OP_SO_R
%token <y_word> MFP
%token <y_word> FOP_FSO_FR
%token <y_word> FOP_NO
%token <y_word> FOP_FSO
%token <y_word> FOP_SO
%token <y_word> MOVF
%token <y_word> FOP_SO_FR
%token <y_word> FOP_FR_SO
%token <y_word> FOP_FR_FSO
%token <y_word> CLEARCC
%token <y_word> SETCC

%type <y_word> opr1 opr2 op2 fopr2 fopr1 ari ainc adec
%type <y_word> fop2 clcc secc fregister
