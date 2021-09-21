/*
 * Microchip PIC
 */

#define	THREE_PASS	/* Distinguish short and long branches. */
#define	LISTING		/* Enable listing facilities. */
#if 0
#define ASLD
#endif

#define IGNORECASE

/* ========== Machine independent type declarations ========== */

#define PASS_1	0
#define PASS_2	1
#define PASS_3	2

#define PASS_RELO       (pass != PASS_1)
#define PASS_SYMB       (pass != PASS_1)

/* Some character constants for scanner */
#define ASC_COMMENT     ';'
#define CTRL(x)		((x) & 037)
#define ISALPHA(c)      (isalpha(c) || (c) == '_')
#define ISALNUM(c)      (isalnum(c) || (c) == '_')

#define DEFAULT_SECTION	(1)
