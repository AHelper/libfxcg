#ifndef _FXCG_STDIO_H
#define _FXCG_STDIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#define EOF (-1)

typedef struct {
    /* Usual values for stdin and friends, everything else is the handle
     * from the system +3 */
    unsigned fileno;
    unsigned error : 1;
    unsigned eof : 1;
    /* Just for rewinding the stream. */
    unsigned has_unput : 1;
    unsigned char unput;
    unsigned int termx, termy;
    unsigned char* __bufferstart;
    unsigned int __bufferleft;
} FILE;

extern FILE _impl_stdin, _impl_stdout, _impl_stderr;
#define stdin (&_impl_stdin)
#define stdout (&_impl_stdout)
#define stderr (&_impl_stderr)

#define BUFSIZ 1

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define FILENAME_MAX 16
#define FOPEN_MAX (1 << (sizeof(FILE) - 1))

#ifndef fpos_t
typedef int fpos_t;
#endif

FILE *fopen(const char *path, const char *mode);
FILE *fdopen(int fd, const char *mode);
FILE *freopen(const char *path, const char *mode, FILE *stream);
int fclose(FILE *fp);

size_t fread(void *buffer, size_t size, size_t count, FILE *stream);
size_t fwrite(const void *buffer, size_t size, size_t count, FILE *stream);
int fflush(FILE *stream);
int ferror(FILE *stream);

void clearerr(FILE *stream);
int feof(FILE *stream);
int fileno(FILE *stream);

int fgetc(FILE *stream);
char *fgets(char *s, int size, FILE *stream);
int getc(FILE *stream);
int getchar(void);
char *gets(char *s);
int ungetc(int c, FILE *stream);

int fputc(int c, FILE *stream);
#define putc fputc
int putchar(int c);
int puts(const char *s);

int printf2(const char *format, ...);
int printf(const char * fmt, ...);
int sprintf(char *dest, const char *fmt, ...);
int fprintf(FILE *stream, const char *fmt, ...);
int fscanf ( FILE * stream, const char * format, ... );

int fgetpos ( FILE * stream, fpos_t * position );
int fsetpos ( FILE * stream, const fpos_t * pos );
int fputs ( const char * str, FILE * stream );
int fseek ( FILE * stream, long int offset, int origin );
long int ftell ( FILE * stream );
void perror ( const char * str );
int remove ( const char * filename );
int rename ( const char * oldname, const char * newname );
int mkdir(const char *path, unsigned int mode);
int  scanf ( const char * format, ... );
void rewind ( FILE * stream );
void setbuf ( FILE * stream, char * buffer );
int setvbuf ( FILE * stream, char * buffer, int mode, size_t size );
int sscanf ( const char * str, const char * format, ...);
FILE * tmpfile ( void );
char * tmpnam ( char * str );
// int vfprintf ( FILE * stream, const char * format, va_list arg );
// int vprintf ( const char * format, va_list arg );
// int vsprintf (char * str, const char * format, va_list arg );
int snprintf(char *str, size_t size, const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif
