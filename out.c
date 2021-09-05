#include <assert.h>

#include "as.h"
#include "error.h"

#include "file.h"

#include "emitter.h"


extern char *aoutpath;
extern sect_t sect[];


void
outstart()
{
#ifdef ELF
	elfstart();
#else
	int rc = emitopen(aoutpath, "bin", NULL);
	if (rc)
		fatal("cannot open output file");
#endif
}

void
outfinish()
{
#ifdef ELF
	elffinish();
#else
	emitclose();
#endif
}


void
emit1(int arg)
{
#if 0
	printf("emit1(0x%02x)\n", arg & 0xff);
#endif
#ifdef LISTING
	if (listeoln) {
		if (listflag & 1) {
			listcolm += printx(VALWIDTH, (ADDR_T)DOTVAL);
			listcolm++;
			putchar(' ');
		}
		listeoln = 0;
	}
	if (listflag & 2)
		listcolm += printx(2, (ADDR_T)arg);
#endif
	switch (pass) {
		case PASS_1:
			if (DOTSCT == S_UND)
				nosect();
			/* no break */
		case PASS_2:
			sect[DOTSCT].s_zero = 0;
			break;
		case PASS_3:
			while (sect[DOTSCT].s_zero) {
				emitbyte(0);
				sect[DOTSCT].s_zero--;
			}
			/* wr_putc(DOTSCT, arg); */
			emitbyte(arg);
			break;
	}
	DOTVAL++;
}

void
emit2(int arg)
{
#if 0
	printf("emit2(0x%04x)\n", arg & 0xffff);
#endif
#ifdef BYTES_REVERSED
	emit1((arg >> 8));
	emit1(arg);
#else
	emit1(arg);
	emit1((arg >> 8));
#endif
}

void
emit4(long arg)
{
#if 0
	printf("emit4(0x%04x)\n", arg & 0xffffffff);
#endif
#ifdef WORDS_REVERSED
	emit2((int)(arg >> 16));
	emit2((int)(arg));
#else
	emit2((int)(arg));
	emit2((int)(arg >> 16));
#endif
}

void
emitx(ADDR_T val, int n)
{
#if 0
	printf("emitx(val=%lx, n=%d)\n", val, n);
#endif

	switch (n) {
		case 1:
			emit1((int)val);
			break;
		case 2:
#ifdef BYTES_REVERSED
			emit1(((int)val >> 8));
			emit1((int)val);
#else
			emit1((int)val);
			emit1(((int)val >> 8));
#endif
			break;
		case 4:
#ifdef WORDS_REVERSED
			emit2((int)(val >> 16));
			emit2((int)(val));
#else
			emit2((int)(val));
			emit2((int)(val >> 16));
#endif
			break;
		default:
			assert(0);
	}
}

void
emit8(int64_t arg)
{
#ifdef WORDS_REVERSED
	emit2((int)(arg >> 48));
	emit2((int)(arg >> 32));
	emit2((int)(arg >> 16));
	emit2((int)(arg));
#else
	emit2((int)(arg));
	emit2((int)(arg >> 16));
	emit2((int)(arg >> 32));
	emit2((int)(arg >> 48));
#endif
}

void
emitstr(int zero)
{
	int i;
	char* p;

	p = stringbuf;
	i = stringlen;
	while (--i >= 0)
		emit1(*p++);
	if (zero)
		emit1(0);
}

#if !defined IEEEFLOAT && !defined PDPFLOAT
	#define IEEEFLOAT
#endif

#if defined WORDS_REVERSED
	#define FL_MSL_AT_LOW_ADDRESS 1
	#define FL_MSW_AT_LOW_ADDRESS 1
#else
	#define FL_MSL_AT_LOW_ADDRESS 0
	#define FL_MSW_AT_LOW_ADDRESS 0
#endif

#if defined BYTES_REVERSED
	#define FL_MSB_AT_LOW_ADDRESS 1
#else
	#define FL_MSB_AT_LOW_ADDRESS 0
#endif

#ifdef USE_FLOAT

#define gen1 emit1
#include "con_float.h"

void
emitf(int size, int negative)
{
	char buffer[40];

	if (stringlen > sizeof(buffer)-1)
		fatal("floating point constant too long");

	if (negative) {
		buffer[0] = '-';
		strcpy(buffer+1, stringbuf);
		con_float(buffer, size);
	} else {
		con_float(stringbuf, size);
	}
}

#endif
