#ifndef _FXCG_STDLIB_H
#define _FXCG_STDLIB_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

// libstdc++ compat
typedef struct
{
  int quot,rem;
} div_t;
#define ldiv_t div_t
void abort();
void abort2(int x);
void alert(int x);
int atexit ( void ( * function ) (void) );
float  atof ( const char * str );
int atoi ( const char * str );
#define atol atoi
void * bsearch ( const void * key, const void * base, size_t num, size_t size, int ( * comparator ) ( const void *, const void * ) );
void * calloc ( size_t num, size_t size );
div_t div ( int numerator, int denominator );
char * getenv ( const char * name );
long int labs ( long int n );
// ldiv_t ldiv ( long int numerator, long int denominator );
#define ldiv div
float strtod ( const char * str, char ** endptr );
unsigned long int strtoul ( const char * str, char ** endptr, int base );
int system ( const char * command );
// END
long abs(long n);

void free(void *p);
void *malloc(size_t sz);
void *realloc(void *p, size_t sz);

int rand(void);
void srand(unsigned seed);

long strtol(const char *str, char **str_end, int base);
void qsort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *));

void exit(int status);
// This belongs here...
void itoa( int value, unsigned char*result );

#ifdef __cplusplus
}
#endif

#endif
