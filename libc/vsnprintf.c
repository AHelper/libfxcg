/* Copyright (C) 2004       Manuel Novoa III    <mjn3@codepoet.org>
 *
 * GNU Library General Public License (LGPL) version 2 or later.
 *
 * Dedicated to Toni.  See uClibc/DEDICATION.mjn3 for details.
 */

#include <stdio.h>
#include <stdarg.h>

int vsnprintf(char *__restrict buf, size_t size,
			  const char * __restrict format, va_list arg)
{
	FILE f = {0, 0, 0, 0, 0, 0, 0, buf, size};
	int rv;
	
	rv = _vfprintf_internal(&f, format, arg);
	
	return rv;
}
