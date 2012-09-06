CC=sh3eb-elf-gcc
AS=sh3eb-elf-as
AR=sh3eb-elf-ar
CFLAGS=-c -ffunction-sections -fdata-sections -m4a-nofpu -mb -Os -nostdlib -mhitachi \
	   -Wall -L../lib -I../include -Wsystem-headers
LDFLAGS=-Wl,-static -lfxcg
ARFLAGS=rsv
OBJECTS=printf.o stdio.o stdlib.o ctype.o string.o unistd.o scanf.o printf2.o vfprintf.o _vfprintf_internal.o _load_inttype.o _ppfs_init.o _ppfs_parsespec.o _ppfs_prepargs.o _ppfs_setargs.o _store_inttype.o fprintf.o _uintmaxtostr.o snprintf.o vsnprintf.o sprintf.o vsprintf.o _fpmaxtostr.o
LIBRARY=../lib/libc.a

all: $(LIBRARY)
	
$(LIBRARY): $(OBJECTS) ../lib/libfxcg.a
	cp ../lib/libfxcg.a ../lib/libc.a
	$(AR) $(ARFLAGS) $@ $(OBJECTS) 

clean:
	rm -f $(OBJECTS) $(LIBRARY)
