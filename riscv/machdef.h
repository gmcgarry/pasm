#define LISTING
#define THREE_PASS
#if 0
#define ASLD
#endif

/* ========== Machine independent type declarations ========== */

#define PASS_1          0
#define PASS_2          1
#define PASS_3          2

#define PASS_SYMB       (pass != PASS_1)
#define PASS_RELO       (pass != PASS_1)

#define IGNORECASE

/*
#define WORDS_REVERSED
#define BYTES_REVERSED
*/

#define ADDR_T		long
#define word_t		unsigned int

#define ALIGNWORD	4
#define ALIGNSECT	4
#define VALWIDTH	8

/* Some character constants for scanner*/
#define ASC_COMMENT     '#'
#define CTRL(x)         ((x) & 037)
#define ISALPHA(c)      (isalpha(c) || (c) == '_' || (c) == '.')
#define ISALNUM(c)      (isalnum(c) || (c) == '_')
