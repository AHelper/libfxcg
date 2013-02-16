#include <fxcg/file.h>
#include <fxcg/heap.h>
#include <fxcg/serial.h>
#include <fxcg/display.h>

#include <errno.h>
#include <stdio.h>
#include <string.h>

FILE _impl_stdin = {0, 0, 0, 0, 0, 0, 0, 0, 0};
FILE _impl_stdout = {1, 0, 0, 0, 0, 0, 0, 0, 0};
FILE _impl_stderr = {2, 0, 0, 0, 0, 0, 0, 0, 0};

#define IOERR(stream, err) errno = err; stream->error = 1

static inline int isstdstream(FILE* f) {
    return f->fileno < 3 && !f->__bufferstart;
}
static inline int isbufferstream(FILE* f)
{
  return f->__bufferstart;
}

static inline int handle_tonative(int fileno)
{
  return fileno - 3;
}

int feof(FILE* stream)
{
  return stream->eof;
}

FILE* fopen(const char* path, const char* mode)
{
  // Resolve mode
  int sysmode = 0;

  if(strchr(mode, '+'))
  {
    sysmode = 3;   // READWRITE
  } 
  else if(mode[0] == 'r')
  {
    sysmode = 0;   // READ
  }
  else if(mode[0] == 'w' || mode[0] == 'a')
  {
    sysmode = 2;   // WRITE
  }
  else
  {
    errno = EINVAL;
    return NULL;
  }

  // Convert string to system native
  size_t plen = strlen(path);
  unsigned short* chars16 = sys_malloc(2 * (plen + 1));

  if(chars16 == NULL)
  {
    errno = ENOMEM;
    return NULL;
  }

  // Get a handle from the system
  Bfile_StrToName_ncpy(chars16, (unsigned char*)path, plen+1);
  int syshandle = Bfile_OpenFile_OS(chars16, sysmode);

  if(syshandle < 0)
  {
    if(sysmode == 2 || sysmode == 3)
    {
      int size = 10; // FIXME: Can I do 0 instead?
      int ret = Bfile_CreateEntry_OS(chars16, CREATEMODE_FILE, &size); 
      switch(ret)
      {
	case 0:
	  syshandle = Bfile_OpenFile_OS(chars16, sysmode);
	  break;
	case -13:
	  errno = EEXIST;
	  return NULL;
	case -3:
	  errno = ENOENT;
	  return NULL;
	default:
	  errno = EIO;
	  return NULL;
      }
    }
    else
    {
    // Failure codes here aren't documented.  Let's just fail with
    // errno = success, then.
      errno = ENOENT;
      return NULL;
    }
  }
  sys_free(chars16);  // No longer needed

  // Create a FILE and fill it in
  FILE* f = sys_malloc(sizeof(FILE));

  if(f == NULL)
  {
    errno = ENOMEM;
    return NULL;
  }

  f->__bufferstart = 0;
  f->fileno = syshandle + 3;
  // TODO reenable when dup() works
  /*if (_dtable_register(f->fileno)) {
      errno = ENFILE;
      return NULL;
  }*/
  f->error = 0;
  f->has_unput = 0;

  if(mode[0] == 'a')
  {
    // TODO Need to seek to end and do some junk.
//     errno = ENOTIMPL;
//     return NULL;
    fseek(f, 0, SEEK_END);
  }
  
  return f;
}

// TODO implement me.
// Same use-case in Python as dup(), so not necessary.  Just fail.
FILE* fdopen(int fd, const char* mode)
{
  return NULL;
}

int fclose(FILE* fp)
{
  if(isbufferstream(fp))
  {
//     sys_free(fp);  // Not handled by libc
  }
  if(!isstdstream(fp))
  {
    // TODO Not sure what this can return.  Assuming never fails.
    Bfile_CloseFile_OS(handle_tonative(fp->fileno));
    // TODO reenable when dup() does something
    //_dtable_unregister(fp->fileno);
    sys_free(fp);
  }
  else
  {
    // std streams are just serial I/O.  Do nothing.
  }

  return 0;
}

static int serial_ensureopen()
{
  if(Serial_IsOpen() != 1)    // syscall 0x1bc6
  {
    unsigned char mode[6] = {0, 5, 0, 0, 0, 0};    // 9600 bps 8n1

    if(Serial_Open(mode) != 0)      // syscall 0x1bb7
    {
      return 1;
    }
  }

  return 0;
}

// TODO restrict ptr, stream
static size_t fwrite_serial(const void* ptr, size_t size, size_t nitems,
                            FILE* stream)
{
  // tx buffer is 256 bytes, don't get stuck waiting
  if(size > 256 || serial_ensureopen())
  {
    IOERR(stream, EIO);
    return 0;
  }

  // Transmit
  size_t remain = nitems;

  while(remain > 0)
  {
    if(Serial_PollTX() > size)
    {
      Serial_Write(ptr, size);
      remain--;
    }
    else
    {
      // Wait for space in tx buffer
      // TODO sleep for an interrupt or something
    }
  }

  return nitems - remain;
}
static size_t fwrite_cout(const void* ptr, size_t size, size_t nitems, FILE* stream)
{
  unsigned char* buffer = sys_malloc(1 + nitems * size);
  unsigned char* lines;
  unsigned char* line;

  memcpy(buffer, ptr, nitems * size);
  buffer[nitems * size] = '\0';
  lines = buffer;

  do
  {
    line = (unsigned char*)strchr((const char*)lines, '\n');

    if(line)
    {
      *line = '\0';
    }

    PrintMiniMini((int*)&stream->termx, (int*)&stream->termy, lines, 0, TEXT_COLOR_BLACK, 0);

    if(line)
    {
      stream->termx = 0;
      stream->termy += 10;
      lines = line + 1;
    }
  }
  while(line);

  sys_free(buffer);
  return nitems;
}
static size_t fwrite_buffer(const void* ptr, size_t size, size_t nitems, FILE* stream)
{
  if(size*nitems == 0)
    return 0;
  /*
  unsigned char* buffer = sys_malloc(nitems * size+1);
  unsigned char* lines;
  unsigned char* line;

  memcpy(buffer, ptr, nitems * size);
  buffer[nitems * size] = '\0';
  lines = buffer;

  do
  {
    line = (unsigned char*)strchr((const char*)lines, '\n');

    if(line)
    {
      *line = '\0';
    }

    int size = strlen(lines);
    memcpy(stream->__bufferstart, lines, size+1);
    stream->__bufferleft -= size;
    stream->__bufferstart += size;
    
    if(line)
    {
      stream->termx = 0;
      stream->termy += 10;
      lines = line + 1;
    }
  }
  while(line);
  */
  memcpy(stream->__bufferstart, ptr, size*nitems);
  stream->__bufferstart[size*nitems] = 0;
  stream->__bufferleft -= size*nitems;
  stream->__bufferstart += size*nitems;
  
  return nitems;
}
// TODO make ptr, stream restrict for optimization
size_t fwrite(const void* ptr, size_t size, size_t nitems,
              FILE* stream)
{
  if(isbufferstream(stream))
  {
    int ret = nitems;
    if(size*nitems + 1 > stream->__bufferleft)
    {
      nitems = stream->__bufferleft - 1;
      size = 1;
    }
    fwrite_buffer(ptr, size, nitems, stream);
    
    return ret;
  }

  if(isstdstream(stream))
  {
    if(stream->fileno == 2)
      return fwrite_serial(ptr, size, nitems, stream);
    else if(stream->fileno == 1)
      return fwrite_cout(ptr, size, nitems, stream);
  }
  // TODO this must be able to fail, but how?
  return Bfile_WriteFile_OS(handle_tonative(stream->fileno), ptr, size * nitems);
//   return nitems; // Buffer size can chande
}

size_t fread_serial(void* buffer, size_t size, size_t count, FILE* stream)
{
  short bytes;
  size_t read = 0;

  // Don't get stuck waiting for a block to come in (buffer is 256 bytes)
  if(size > 256 || serial_ensureopen())
  {
    IOERR(stream, EIO);
    return 0;
  }

  while(count-- > 0)
  {
    while(Serial_PollRX() < size);

    Serial_Read(buffer, size, &bytes);
    buffer += size;
    read++;
  }

  return read;
}

size_t fread(void* buffer, size_t size, size_t count, FILE* stream)
{
  size_t n = size * count;

  if(isstdstream(stream))
  {
    if(stream->fileno == 2)
      return fread_serial(buffer, size, n, stream);
    else if(stream->fileno == 1)
      return -1;
  }
  if(isbufferstream(stream))
  {
    return -1;
  }
  // TODO failure modes unknown
  int ret = Bfile_ReadFile_OS(handle_tonative(stream->fileno), buffer, n, -1);
  if(ret < 0)
    stream->error = 1;
  else if(ret < n)
    stream->eof = 1;
  
  return ret;
}

int fputc(int c, FILE* stream)
{
  unsigned char uc = (unsigned char)c;

  if(fwrite(&uc, 1, 1, stream) != 1)
    return EOF;

  return uc;
}

int putchar(int c)
{
  return fputc(c, stdout);
}

int fputs(const char* s, FILE* stream)
{
  size_t len = strlen(s);

  if(fwrite(s, 1, len, stdout) != len)
    return EOF;

  return 0;
}

int puts(const char* s)
{
  int ret = fputs(s, stdout);
  putchar('\n');
  return ret;
}

char* fgets(char* s, int n, FILE* stream)
{
  unsigned char c;
  char* s_in = s;
  int count = 0;

  if(n < 1)
    return NULL;

  do
  {
    if(fread(&c, 1, 1, stream) != 1)
      return NULL;

    *s++ = c;
    count++;
  }
  while(c != '\n' && count < n && c != EOF);

  if(count < n)  // Back up unless didn't consume a terminator
    s--;

  *s = 0;
  return s_in;
}

int fgetc ( FILE * stream )
{
  if(!stream)
    return -2;
  char c;
  if(!fread(&c, 1, 1, stream))
  {
    return EOF;
  }
  return (int)c;
}

void perror(const char* s)
{
  if(s != NULL && strlen(s) > 0)
  {
    fprintf(stderr, "(%s): ", s);
  }

  fprintf(stderr, "code %i (xref errno.h)\n", -errno);
}

int ferror(FILE* stream)
{
  if(!stream)
    return 1;

  if(stream->error)
    return 2;

  return 0;
}
void clearerr(FILE* stream)
{
  if(stream)
  {
    stream->error = 0;
    stream->eof = 0;
  }
}
int fseek(FILE* stream, long int offset, int origin)
{
  // TODO: Errno
  if(!stream)
    return 1;

  if(isstdstream(stream))
    return 2;

  if(isbufferstream(stream))
  {
    return 2;
  }
  switch(origin)
  {
    case SEEK_SET:
      Bfile_SeekFile_OS(handle_tonative(stream->fileno), offset);
      break;
    case SEEK_CUR:
      Bfile_SeekFile_OS(handle_tonative(stream->fileno), offset + Bfile_TellFile_OS(handle_tonative(stream->fileno)));
      break;
    case SEEK_END:
      Bfile_SeekFile_OS(handle_tonative(stream->fileno), Bfile_GetFileSize_OS(handle_tonative(stream->fileno))); 
      break;
  }

  // Must clear error bit
  clearerr(stream);
  return 0;
}
int remove(const char *filename)
{
  int len = strlen(filename) + 1;
  unsigned short *widepath = (unsigned short*)sys_malloc(2*len);
  
  Bfile_StrToName_ncpy(widepath, (unsigned char*)filename, len);
  int ret = Bfile_DeleteEntry(widepath);
  
  if(ret >= 0)
    return 0;
  switch(ret)
  {
    case -1:
    case -3:
    case -5:
      errno = ENOENT;
      return 1;
    default:
      errno = EIO;
      return 1;
  }
}
int rename ( const char * oldname, const char * newname )
{
  int len_o = strlen(oldname) + 1;
  int len_n = strlen(newname) + 1;
  unsigned short *widepath_o = (unsigned short*)sys_malloc(2*len_o);
  unsigned short *widepath_n = (unsigned short*)sys_malloc(2*len_n);
  
  Bfile_StrToName_ncpy(widepath_o, (unsigned char*)oldname, len_o);
  Bfile_StrToName_ncpy(widepath_n, (unsigned char*)newname, len_n);
  int ret = Bfile_RenameEntry(widepath_o, widepath_n);
  
  if(ret >= 0)
    return 0;
  switch(ret)
  {
    default:
      errno = ret;
  }
  return 1;
}
int mkdir(const char *path, unsigned int mode)
{
  int len = strlen(path) + 1;
  unsigned short *widepath = (unsigned short*)sys_malloc(2*len);
  
  Bfile_StrToName_ncpy(widepath, (unsigned char*)path, len);
  int ret = Bfile_CreateEntry_OS(widepath, CREATEMODE_FOLDER, 0);
  
  if(ret >= 0)
    return 0;
  switch(ret)
  {
    case -3:
      errno = EEXIST;
    default:
      errno = ret;
  }
  return -1;
}
long int ftell(FILE* stream)
{
  if(!stream)
    return -1;

  if(isstdstream(stream) || isbufferstream(stream))
    return -2;

  return Bfile_TellFile_OS(handle_tonative(stream->fileno));
}
int fflush(FILE* stream)
{
  if(!stream)
    return EOF;

  if(isstdstream(stream))
  {
    Bdisp_PutDisp_DD();
  }

  // Unbuffered
  return 0;
}
  

