CC = gcc

COPTIONS = -Wall -Wunused -g -P
COPTIONS += -DYYDEBUG=1
LDOPTIONS =

#COPTIONS += --std=c89

MACH ?= i386

LIBOBJ	=

INCL	= -I. -I./$(MACH)
CFLAGS	= $(INCL) $(COPTIONS) -Dmach_$(MACH) -DMACH=$(MACH)
YFLAGS	= -d -l
LDFLAGS	= $(LDOPTIONS)

CSRC	= \
	elf.c \
	emitter.c \
	error.c \
	file.c \
	keywords.c \
	main.c \
	misc.c \
	out.c \
	pseudo.c \
	reloc.c \
	scanner.c \
	symtab.c \
	$(MACH)/mach.c
COBJ	= $(CSRC:.c=.o)

all:	pasm-$(MACH)

pasm-$(MACH):	pasm
	cp $< $@

clean:
	rm -f $(COBJ) pasm parser.[ocy] y.tab.h

pasm:	parser.o $(COBJ)
	$(CC) $(LDFLAGS) $^ $(LIBOBJ) -o $@

parser.c:	parser.y
	yacc $(YFLAGS) $< && mv y.tab.c $@

y.tab.h:	parser.c

parser.y:	grammar.y
	cpp -P -I./$(MACH) $< > $@
parser.y:	$(MACH)/tokens.inc
parser.y:	$(MACH)/grammar.inc

$(COBJ):	y.tab.h
$(COBJ) parser.y:	$(MACH)/machdef.h
$(COBJ) parser.y:	as.h
$(COBJ) parser.y:	$(MACH)/mach.h
keywords.o:	$(MACH)/keywords.inc
