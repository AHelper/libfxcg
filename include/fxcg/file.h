#ifndef _FXCG_FILE_H
#define _FXCG_FILE_H

#ifdef __cplusplus
extern "C" {
#endif

enum
{
  CREATEMODE_FILE = 1,
  CREATEMODE_FOLDER = 5
};

enum
{
  READ = 0,
  READ_SHARE = 1,
  WRITE = 2,
  READWRITE = 3,
  READWRITE_SHARE = 4
};

int Bfile_CloseFile_OS( int HANDLE );
int Bfile_CreateEntry_OS( const unsigned short*filename, int mode, int*size );
int Bfile_DeleteEntry( const unsigned short *filename );
int Bfile_RenameEntry( const unsigned short *oldpath, const unsigned short *newpath );
int Bfile_FindClose( int FindHandle );
int Bfile_FindFirst( const unsigned short *pathname, int *FindHandle, const unsigned short *foundfile, void *fileinfo );
int Bfile_FindFirst_NON_SMEM( const unsigned short *pathname, int *FindHandle, const unsigned short *foundfile, void *fileinfo );
int Bfile_FindNext( int FindHandle, const unsigned short *foundfile, void *fileinfo );
int Bfile_FindNext_NON_SMEM( int FindHandle, unsigned short *foundfile, void *fileinfo );
int Bfile_GetFileSize_OS( int handle );
int Bfile_OpenFile_OS( const unsigned short*filename, int mode );
int Bfile_ReadFile_OS( int HANDLE, void *buf, int size, int readpos );
int Bfile_SeekFile_OS( int handle, int pos );
int Bfile_TellFile_OS( int handle );
int Bfile_WriteFile_OS( int HANDLE, const void *buf, int size );
void Bfile_StrToName_ncpy(unsigned short *dest, const unsigned char *source, int n);
void Bfile_NameToStr_ncpy( unsigned char*source, const unsigned short*dest, int n );
int Bfile_Name_MatchMask( unsigned short *mask, unsigned short *filename );

int MCS_CreateDirectory( unsigned char*dir );
int MCS_DeleteDirectory( unsigned char*dir );
int MCSDelVar2( unsigned char*dir, unsigned char*item );
int MCS_GetCapa( int*current_bottom );
int MCSGetData1( int offset, int len_to_copy, void*buffer );
int MCSGetDlen2( unsigned char*dir, unsigned char*item, int*data_len );
int MCS_GetMainMemoryStart( void );
int MCSGetOpenItem( unsigned char*item );
int MCSOvwDat2( unsigned char*dir, unsigned char*item, int bytes_to_write, void*buffer, int write_offset );
int MCSPutVar2( unsigned char*dir, unsigned char*item, int data_len, void*buffer );
int MCS_WriteItem( unsigned char*dir, unsigned char*item, short itemtype, int data_length, int buffer );

int SaveFileDialog( unsigned short *filenamebuffer, int mode );
int OverwriteConfirmation( char*name, int mode );
int OpenFileDialog( unsigned short keycode, unsigned short *filenamebuffer, int filenamebufferlength );
int ConfirmFileOverwriteDialog( unsigned short *filename );

#ifdef __cplusplus
}
#endif

#endif
