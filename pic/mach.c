#include <assert.h>

#include "as.h"
#include "mach.h"

extern sect_t sect[];
extern int hash(const char *);

static item_t cseg = { 0, 0, S_UND, ".cseg" };

void
mflag(const char* flag)
{
}

void
machstart(int pass)
{
	if (pass == PASS_1) {
		item_insert(&cseg, hash(cseg.i_name));
		unresolved++;
	}
	newsect(&cseg, 0, NULL);
}

void
machfinish(int pass)
{
}
