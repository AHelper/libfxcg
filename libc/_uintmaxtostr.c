/* Copyright (C) 2004       Manuel Novoa III    <mjn3@codepoet.org>
 *
 * GNU Library General Public License (LGPL) version 2 or later.
 *
 * Dedicated to Toni.  See uClibc/DEDICATION.mjn3 for details.
 */

#define _ISOC99_SOURCE			/* for ULLONG primarily... */
#include <stdio.h>
#include <limits.h>
#include <locale.h>
#include <assert.h>
#include "uClibc_uintmaxtostr.h"
#include "uClibc_locale.h"

#ifndef likely
# define likely(x)	__builtin_expect((!!(x)),1)
#endif
#ifndef unlikely
# define unlikely(x)	__builtin_expect((!!(x)),0)
#endif
# define LLONG_MAX __LONG_LONG_MAX__
/* Avoid using long long / and % operations to cut down dependencies on
 * libgcc.a.  Definitely helps on i386 at least. */
// #if (INTMAX_MAX > INT_MAX) && (((INTMAX_MAX/INT_MAX)/2) - 2 <= INT_MAX)
// #warning !!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
// #define INTERNAL_DIV_MOD
// #endif

char  *_uintmaxtostr(char * bufend, unsigned long long uval,
					int base, __UIM_CASE alphacase)
{
	int negative;
	unsigned int digit;
#ifdef INTERNAL_DIV_MOD
	unsigned int H, L, high, low, rh;
#endif
#ifndef __LOCALE_C_ONLY
	int grouping, outdigit;
	const char *g;		   /* This does not need to be initialized. */
#endif /* __LOCALE_C_ONLY */

	negative = 0;
	if (base < 0) {				/* signed value */
		base = -base;
		if (uval > 0x8000000000000000) { // shut your face
			uval = -uval;
			negative = 1;
		}
	}

	/* this is an internal routine -- we shouldn't need to check this */
	assert(!((base < 2) || (base > 36)));

#ifndef __LOCALE_C_ONLY
	grouping = -1;
	outdigit = 0x80 & alphacase;
	alphacase ^= outdigit;
	if (alphacase == __UIM_GROUP) {
		assert(base == 10);
		if (*(g = __UCLIBC_CURLOCALE->grouping)) {
			grouping = *g;
		}
	}
#endif /* __LOCALE_C_ONLY */

	*bufend = '\0';

#ifndef INTERNAL_DIV_MOD
	do {
#ifndef __LOCALE_C_ONLY
		if (!grouping) {		/* Finished a group. */
			bufend -= __UCLIBC_CURLOCALE->thousands_sep_len;
			memcpy(bufend, __UCLIBC_CURLOCALE->thousands_sep,
				   __UCLIBC_CURLOCALE->thousands_sep_len);
			if (g[1] != 0) { 	/* g[1] == 0 means repeat last grouping. */
				/* Note: g[1] == -1 means no further grouping.  But since
				 * we'll never wrap around, we can set grouping to -1 without
				 * fear of */
				++g;
			}
			grouping = *g;
		}
		--grouping;
#endif /* __LOCALE_C_ONLY */
		digit = uval % base;
		uval /= base;
// 		alert(digit);
#ifndef __LOCALE_C_ONLY
		if (unlikely(outdigit)) {
			bufend -= __UCLIBC_CURLOCALE->outdigit_length[digit];
			memcpy(bufend,
				   (&__UCLIBC_CURLOCALE->outdigit0_mb)[digit],
				   __UCLIBC_CURLOCALE->outdigit_length[digit]);
		} else
#endif
		{
			*--bufend = ( (digit < 10) ? digit + '0' : digit + alphacase );
		}
	} while (uval);

#else  /* ************************************************** */

	H = (UINT_MAX / base);
	L = UINT_MAX % base + 1;
	if (L == base) {
		++H;
		L = 0;
	}
	low = (unsigned int) uval;
	high = (unsigned int) (uval >> (sizeof(unsigned int) * CHAR_BIT));

	do {
#ifndef __LOCALE_C_ONLY
		if (!grouping) {		/* Finished a group. */
			bufend -= __UCLIBC_CURLOCALE->thousands_sep_len;
			memcpy(bufend, __UCLIBC_CURLOCALE->thousands_sep,
				   __UCLIBC_CURLOCALE->thousands_sep_len);
			if (g[1] != 0) { 	/* g[1] == 0 means repeat last grouping. */
				/* Note: g[1] == -1 means no further grouping.  But since
				 * we'll never wrap around, we can set grouping to -1 without
				 * fear of */
				++g;
			}
			grouping = *g;
		}
		--grouping;
#endif /* __LOCALE_C_ONLY */

		if (unlikely(high)) {
			rh = high % base;
			high /= base;
			digit = (low % base) + (L * rh);
			low = (low / base) + (H * rh) + (digit / base);
			digit %= base;
		} else {
			digit = low % base;
			low /= base;
		}

#ifndef __LOCALE_C_ONLY
		if (unlikely(outdigit)) {
			bufend -= __UCLIBC_CURLOCALE->outdigit_length[digit];
			memcpy(bufend,
				   (&__UCLIBC_CURLOCALE->outdigit0_mb)[digit],
				   __UCLIBC_CURLOCALE->outdigit_length[digit]);
		} else
#endif
		{
			*--bufend = ( (digit < 10) ? digit + '0' : digit + alphacase );
		}
	} while (low | high);

#endif /******************************************************/

	if (negative) {
		*--bufend = '-';
	}

	return bufend;
}
