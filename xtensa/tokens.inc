%token PSEUDOOP_LITPOS
%token PSEUDOOP_LITERAL

%token <y_word> REG
%token <y_word> SREG
%token <y_word> BREG
%token <y_word> FREG

%type <y_word> rel8		/* -127 .. 128 */

%type <y_word> imm4		/* 0..15 */
%type <y_word> imm4_n1		/* 0=-1, 1..15 */
%type <y_word> imm4_p1		/* 1..16 */
%type <y_word> b4const
%type <y_word> imm5
%type <y_word> imm5_p		/* 1..31 */
%type <y_word> imm7_m32		/* (0..127) - 32 */
%type <y_word> imm8
%type <y_word> imm8_x4		/* 4*(0..255) */
#if 0
%type <y_word> imm8_x8		/* 8*(-127..128) */
#endif
%type <y_word> imm8_x256	/* 256*(-127..128) */
%type <y_word> imm12
%type <y_word> imm12_x8		/* 8*(0..4096) */
%type <y_word> imm16

%type <y_word> insn24
%type <y_word> insn16

%type <y_item> sectname		/* for irom sections */

%token <y_word> FORMAT_BRI12
%token <y_word> FORMAT_BRI12_SI
%token <y_word> FORMAT_BRI8_RSI
%token <y_word> FORMAT_RI6
%token <y_word> FORMAT_RII6_TI
%token <y_word> FORMAT_RI7

%token <y_word> FORMAT_RRI4_ISTx4
%token <y_word> FORMAT_RRI4_TSRx4
%token <y_word> FORMAT_RRI4_RST
%token <y_word> FORMAT_RRI4_SIx16
%token <y_word> FORMAT_RRI4_Sx16

%token <y_word> FORMAT_RRI8
%token <y_word> FORMAT_RRI8_TI
%token <y_word> FORMAT_RRI8_RSI
%token <y_word> FORMAT_RRI8_SI
%token <y_word> FORMAT_RRI8_SIx4
%token <y_word> FORMAT_RRI8_ST
%token <y_word> FORMAT_RRI8_ST5I
%token <y_word> FORMAT_RRI8_STI
%token <y_word> FORMAT_RRI8_TSI
%token <y_word> FORMAT_RRI8_TSIx2
%token <y_word> FORMAT_RRI8_TSIx4
%token <y_word> FORMAT_RRI8_TSIx256
%token <y_word> FORMAT_RRI8_Sx4

%token <y_word> FORMAT_RRR
%token <y_word> FORMAT_RRR_A
%token <y_word> FORMAT_RRR_I4
%token <y_word> FORMAT_RRR_I4T
%token <y_word> FORMAT_RRR_L
%token <y_word> FORMAT_RRRN
%token <y_word> FORMAT_RRRN_RSI
%token <y_word> FORMAT_RRRN_RST
%token <y_word> FORMAT_RRRN_S
%token <y_word> FORMAT_RRRN_TS
%token <y_word> FORMAT_RRRN_TSIx4



%token <y_word> FORMAT_RRR_RS
%token <y_word> FORMAT_RRR_RSI
%token <y_word> FORMAT_RRR_RSI5
%token <y_word> FORMAT_RRR_RSIp7
%token <y_word> FORMAT_RRR_RSS
%token <y_word> FORMAT_RRR_RST
%token <y_word> FORMAT_RRR_RSTp7
%token <y_word> FORMAT_RRR_RT
%token <y_word> FORMAT_RRR_RTI4
%token <y_word> FORMAT_RRR_RTI5
%token <y_word> FORMAT_RRR_S
%token <y_word> FORMAT_RRR_SI
%token <y_word> FORMAT_RRR_TS
%token <y_word> FORMAT_RRR_TI4
%token <y_word> FORMAT_RRR_TSRx4
%token <y_word> FORMAT_RRR_ST
%token <y_word> FORMAT_RRR_TSI
%token <y_word> FORMAT_RRR_STmm
%token <y_word> FORMAT_RRR_Tm4
%token <y_word> FORMAT_RRR_MS
%token <y_word> FORMAT_RSR
%token <y_word> FORMAT_RUR

%token <y_word> JUMPOP CALLOP CALLX CALL CALLXOP
