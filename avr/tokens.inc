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

%token PSEUDOOP_DEVICE
%token PSEUDOOP_DEFINE

%token <y_word> SHIFTFUNC

%token <y_word> PSEUDOOP_SEGMENT
%token <y_word> MACHID
%token <y_word> REG8
%token <y_word> REG16

%token <y_word> BASICOP
%token <y_word> BRANCHOP
%token <y_word> BRANCHOP_SREG
%token <y_word> ONEOP
%token <y_word> ONEOPI
%token <y_word> TWOOP
%token <y_word> TWOOP_1
%token <y_word> SKIPBITOP

%token <y_word> BITLOAD
%token <y_word> BITSET
%token <y_word> IOBITSET

%token <y_word> MNEMONIC_LPM
%token <y_word> MNEMONIC_ELPM
%token <y_word> MNEMONIC_BSET
%token <y_word> MNEMONIC_BCLR
%token <y_word> MNEMONIC_SER

%token <y_word> MNEMONIC_TST
%token <y_word> MNEMONIC_CLR
%token <y_word> MNEMONIC_LSL
%token <y_word> MNEMONIC_ROL

%token <y_word> MNEMONIC_RJMP
%token <y_word> MNEMONIC_JMP

%token <y_word> MNEMONIC_MOVW
%token <y_word> MNEMONIC_MULS
%token <y_word> MNEMONIC_FMUL
%token <y_word> MNEMONIC_OPIW

%token <y_word> MNEMONIC_BRBS
%token <y_word> MNEMONIC_BRBC
%token <y_word> MNEMONIC_ADD
%token <y_word> MNEMONIC_ADC
%token <y_word> MNEMONIC_SUB
%token <y_word> MNEMONIC_SBC
%token <y_word> MNEMONIC_AND
%token <y_word> MNEMONIC_OR
%token <y_word> MNEMONIC_EOR
%token <y_word> MNEMONIC_CP
%token <y_word> MNEMONIC_CPC
%token <y_word> MNEMONIC_CPSE
%token <y_word> MNEMONIC_MOV
%token <y_word> MNEMONIC_MUL
%token <y_word> MNEMONIC_SUBI
%token <y_word> MNEMONIC_SBCI
%token <y_word> MNEMONIC_ANDI
%token <y_word> MNEMONIC_ORI
%token <y_word> MNEMONIC_SBR
%token <y_word> MNEMONIC_CPI
%token <y_word> MNEMONIC_CBR
%token <y_word> MNEMONIC_SBRC
%token <y_word> MNEMONIC_SBRS
%token <y_word> MNEMONIC_BST
%token <y_word> MNEMONIC_BLD
%token <y_word> MNEMONIC_IN
%token <y_word> MNEMONIC_OUT
%token <y_word> MNEMONIC_SBIC
%token <y_word> MNEMONIC_SBIS
%token <y_word> MNEMONIC_SBI
%token <y_word> MNEMONIC_CBI
%token <y_word> MNEMONIC_LDS
%token <y_word> MNEMONIC_STS
%token <y_word> MNEMONIC_LD
%token <y_word> MNEMONIC_ST
%token <y_word> MNEMONIC_LDD
%token <y_word> MNEMONIC_STD

%type <y_word> reg8
%type <y_valu> regw
%type <y_valu> regU
%type <y_valu> regV
%type <y_valu> port

%type <y_valu> imm3
%type <y_valu> imm6
%type <y_valu> imm8
%type <y_valu> imm16
