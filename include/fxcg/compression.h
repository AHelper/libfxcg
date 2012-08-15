#ifndef __FXCG_COMPRESSION_H
#define __FXCG_COMPRESSION_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
  void*source;
  int requested_sourcelength;
  int processed_sourcelength;
  void*chunkbuffer;
  int max_chunklength;
  int processed_chunklength;
  int field7;
  int field8;
  void*pMalloc_P2xP3;
  void*pFree_P2;
  int field11;
  int field12;
  int field13;
  int field14;
} deflate_t;

typedef struct {
    int field1;
    int field2;
    int field3;
    void*inflatebuffer;
    int inflatebufferlength;
    int field6;
    int field7;
    int field8;
    void*pMalloc_P2xP3;
    void*pFree_P2;
    int field11;
    int field12;
    int field13;
    int field14;
} inflate_t;

// These functions are still experimental. These appear to be using zlib.
int DeflateTofile( int filehandle, int* lengthofpackeddata, void* sourcebuffer, int *sourcebufferlength, int v6, int v8, int vB, int v5, int mixflag );
int InflateFromFile( int filehandle, int fileoffset, void* inflatebuffer, int* inflatebufferlength, int mixflag );
int OpenDeflate( deflate_t* deflate_record, int v6, int v8, int vB, int v5, int v0, unsigned char* deflate_version, int v38 );
void PerformDeflate( deflate_t* deflate_record, int v4 );
void CloseDeflate( deflate_t* deflate_record );
int OpenInflate( inflate_t* inflate_record, unsigned char* inflate_version, int v38 );
void PerformInflate( inflate_t* inflate_record, int v0 );
void CloseInflate( inflate_t* inflate_record );

#ifdef __cplusplus
}
#endif

#endif