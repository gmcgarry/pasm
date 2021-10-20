/*-
 * Copyright (c) 1990 Ken Stauffer (University of Calgary)
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

extern item_t cseg;
extern item_t dseg;

struct mode {
        unsigned char mode;             /* value to index with */
        unsigned char size;             /* # of bytes used */
        unsigned char orval;            /* value OR'd to obcode */
        unsigned char byte1;            /* extra byte 1 */
        unsigned char byte2;            /* extra byte 2 */
        unsigned char byte3;            /* extra byte 3 */
};

extern struct mode	mode;

#define set_md(m,a)     ((m).mode=(a))
#define set_sz(m,a)     ((m).size=(a))
#define set_ov(m,a)     ((m).orval=(a))
#define set_b1(m,a)     ((m).byte1=(a))
#define set_b2(m,a)     ((m).byte2=(a))
#define set_b3(m,a)     ((m).byte3=(a))

#define get_md(m)       ((m).mode)
#define get_sz(m)       ((m).size)
#define get_ov(m)       ((m).orval)
#define get_b1(m)       ((m).byte1)
#define get_b2(m)       ((m).byte2)
#define get_b3(m)       ((m).byte3)

void emitop(int opc);

void movop(int add);
void anlop(int add);
void orlop(int add);
void addop(int add);
void addcop(int add);
void cjneop(int add);
void decop(int add);
void subbop(int add);
void movxop(int add);
void xrlop(int add);
void incop(int add);
void xchop(int add);
void djnzop(int add);
void clrop(int add);
void cplop(int add);
void setbop(int add);
