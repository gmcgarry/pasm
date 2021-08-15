#include <stdio.h>
#include <ctype.h>
#include <string.h>

extern void *malloc(size_t size);
extern void free(void *ptr);


#define B(a)		(0xF0+(a))
#define ACC(a)		(0xE0+(a))
#define PSW(a)		(0xD0+(a))
#define T2CON(a)	(0xC8+(a))
#define IP(a)		(0xB8+(a))
#define P3(a)		(0xB0+(a))
#define IE(a)		(0xA8+(a))
#define P2(a)		(0xA0+(a))
#define SCON(a)		(0x98+(a))
#define P1(a)		(0x90+(a))
#define TCON(a)		(0x88+(a))
#define P0(a)		(0x80+(a))

#define LABEL 1

struct symbol {
	const char* name;
	const char* foo;
};

static struct symbol sinit[] = {
	{ "AC",		"PSW(6)" },
	{ "ACC",	"ACC(0)" },
	{ "B",		"B(0)" },
	{ "CY",		"PSW(7)" },
	{ "DPH",	"0x83" },
	{ "DPL",	"0x82" },
	{ "EA",		"IE(7)" },
	{ "ES",		"IE(4)" },
	{ "ET0",	"IE(1)" },
	{ "ET1",	"IE(3)" },
	{ "ET2",	"IE(5)" },
	{ "EX0",	"IE(0)" },
	{ "EX1",	"IE(2)" },
	{ "EXEN2",	"T2CON(3)" },
	{ "EXF2",	"T2CON(6)" },
	{ "F0",		"PSW(5)" },
	{ "IE",		"IE(0)" },
	{ "IE0",	"TCON(1)" },
	{ "IE1",	"TCON(3)" },
	{ "INT0",	"P3(2)" },
	{ "INT1",	"P3(3)" },
	{ "IP",		"IP(0)" },
	{ "IT0",	"TCON(0)" },
	{ "IT1",	"TCON(2)" },
	{ "OV",		"PSW(2)" },
	{ "P",		"PSW(0)" },
	{ "P0",		"P0(0)" },
	{ "P1",		"P1(0)" },
	{ "P2",		"P2(0)" },
	{ "P3",		"P3(0)" },
	{ "PCON",	"0x87" },
	{ "PS",		"IP(4)" },
	{ "PSW",	"PSW(0)" },
	{ "PT0",	"IP(1)" },
	{ "PT1",	"IP(3)" },
	{ "PT2",	"IP(5)" },
	{ "PX0",	"IP(0)" },
	{ "PX1",	"IP(2)" },
	{ "RB8",	"SCON(2)" },
	{ "RCAP2H",	"0xCB" },
	{ "RCAP2L",	"0xCA" },
	{ "RCLK",	"T2CON(5)" },
	{ "REN",	"SCON(4)" },
	{ "RD",		"P3(7)" },
	{ "RI",		"SCON(0)" },
	{ "RL2",	"T2CON(0)" },
	{ "RS0",	"PSW(3)" },
	{ "RS1",	"PSW(4)" },
	{ "RXD",	"P3(0)" },
	{ "SBUF",	"0x99" },
	{ "SCON",	"SCON(0)" },
	{ "SM0",	"SCON(7)" },
	{ "SM1",	"SCON(6)" },
	{ "SM2",	"SCON(5)" },
	{ "SP",		"0x81" },
	{ "T0",		"P3(4)" },
	{ "T1",		"P3(5)" },
	{ "T2",		"P0(0)" },
	{ "T2CON",	"T2CON(0)" },
	{ "T2EX",	"P0(1)" },
	{ "TB8",	"SCON(3)" },
	{ "TCLK",	"T2CON(4)" },
	{ "TCON",	"TCON(0)" },
	{ "TF0",	"TCON(5)" },
	{ "TF1",	"TCON(7)" },
	{ "TF2",	"T2CON(7)" },
	{ "TH0",	"0x8C" },
	{ "TH1",	"0x8D" },
	{ "TH2",	"0xCD" },
	{ "TI",		"SCON(1)" },
	{ "TL0",	"0x8A" },
	{ "TL1",	"0x8B" },
	{ "TL2",	"0xCC" },
	{ "TMOD",	"0x89" },
	{ "TR0",	"TCON(4)" },
	{ "TR1",	"TCON(6)" },
	{ "TR2",	"T2CON(2)" },
	{ "TXD",	"P3(1)" },
	{ "WR",		"P3(6)" }
};

#define SINITSIZE	(sizeof(sinit)/sizeof(sinit[0]))

static unsigned char add[]=	{ 0x28, 0x25, 0x26, 0x24 };
static unsigned char addc[]=	{ 0x38, 0x35, 0x36, 0x34 };
static unsigned char anl[]=	{ 0x58, 0x55, 0x56, 0x54, 0x52, 0x53, 0x82, 0xb0 };
static unsigned char cjne[]=	{ 0xb5, 0xb4, 0xb8, 0xb6 };
static unsigned char clr[]=	{ 0xe4, 0xc3, 0xc2 };
static unsigned char cpl[]=	{ 0xf4, 0xb3, 0xb2 };
static unsigned char dec[]=	{ 0x14, 0x18, 0x15, 0x16 };
static unsigned char djnz[]=	{ 0xd8, 0xd5 };
static unsigned char inc[]=	{ 0x04, 0x08, 0x05, 0x06, 0xa3 };
static unsigned char mov[]=	{ 0xe8, 0xe5, 0xe6, 0x74, 0xf5, 0x75, 0xf8, 0xa8, 0x78, 0x88, 0x85, 0x86, 0xf6, 0xa6, 0x76, 0x90, 0xa2, 0x92 };
static unsigned char movc[]=	{ 0x93, 0x83 };
static unsigned char movx[]=	{ 0xe2, 0xe3, 0xe0, 0xf2, 0xf3, 0xf0 };
static unsigned char orl[]=	{ 0x48, 0x45, 0x46, 0x44, 0x42, 0x43, 0x72, 0xa0 };
static unsigned char setb[]=	{ 0xd3, 0xd2 };
static unsigned char subb[]=	{ 0x98, 0x95, 0x96, 0x94 };
static unsigned char xch[]=	{ 0xc8, 0xc5, 0xc6 };
static unsigned char xrl[]=	{ 0x68, 0x65, 0x66, 0x64, 0x62, 0x63 };

struct opcode {
	const char *mnemonic;
	const char *token;
	const unsigned char* opcodes;
};

static struct opcode optable[] = {
{"a","A",NULL	},
{"ab","AB",NULL	},
{"acall","ACALL",acall	},
{"add","ADD",add	},
{"addc","ADDC",addc	},
{"ajmp","AJMP",ajmp	},
{"anl","ANL",anl	},
{"byte","D_BYTE",NULL	},
{"c","C",NULL	},
{"cjne","CJNE",cjne	},
{"clr","CLR",clr	},
{"cpl","CPL",cpl	},
{"da","DA",da	},
{"db","D_BYTE",NULL	},
{"dec","DEC",dec	},
{"div","DIV",div	},
{"djnz","DJNZ",djnz	},
{"dptr","DPTR",NULL	},
{"dw","D_WORD",NULL	},
{"end","D_END",NULL	},
{"equ","D_EQU",NULL	},
{"flag","D_FLAG",NULL	},
{"inc","INC",inc	},
{"jb","JB",jb	},
{"jbc","JBC",jbc	},
{"jc","JC",jc	},
{"jmp","JMP",jmp	},
{"jnb","JNB",jnb	},
{"jnc","JNC",jnc	},
{"jnz","JNZ",jnz	},
{"jz","JZ",jz	},
{"lcall","LCALL",lcall	},
{"ljmp","LJMP",ljmp	},
{"mov","MOV",mov	},
{"movc","MOVC",movc	},
{"movx","MOVX",movx	},
{"mul","MUL",mul	},
{"nop","NOP",nop	},
{"org","D_ORG",NULL	},
{"orl","ORL",orl	},
{"pc","PC",NULL	},
{"pop","POP",pop	},
{"push","PUSH",push	},
{"r0","R0",NULL	},
{"r1","R1",NULL	},
{"r2","R2",NULL	},
{"r3","R3",NULL	},
{"r4","R4",NULL	},
{"r5","R5",NULL	},
{"r6","R6",NULL	},
{"r7","R7",NULL	},
{"ret","RET",ret	},
{"reti","RETI",reti	},
{"rl","RL",rl	},
{"rlc","RLC",rlc	},
{"rr","RR",rr	},
{"rrc","RRC",rrc	},
{"setb","SETB",setb	},
{"sjmp","SJMP",sjmp	},
{"skip","D_SKIP",NULL	},
{"subb","SUBB",subb	},
{"swap","SWAP",swap	},
{"word","D_WORD",NULL	},
{"xch","XCH",xch	},
{"xchd","XCHD",xchd	},
{"xrl",		"XRL",	xrl		}
};

#define OPTABSIZE	(sizeof(optable)/sizeof(struct opcode))

int
main()
{
	printf("\n\t/* register names */\n");
	for (int i = 0; i < SINITSIZE; i++)
		printf("\t{ 0,\tSREG,\t\t\t%s,\t\t\"%s\"\t},\n", sinit[i].foo, sinit[i].name);

	printf("\n\t/* opcodes */\n");
	for (int i = 0; i < OPTABSIZE; i++) {
		int arg = optable[i].opcodes == NULL ? 0 : optable[i].opcodes[0];
		printf("\t{ 0,\t%s,\t\t\t0x%x,\t\t\"%s\"\t},\n", optable[i].token, arg, optable[i].mnemonic);
	}

	return 0;
}
