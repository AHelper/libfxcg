int ItoA_10digit( int, void* );
void ByteToHex( unsigned char value, unsigned char*result );
void HexToByte( unsigned char*value, unsigned char*result );
void HexToNibble( unsigned char value, unsigned char*result );
void HexToWord( unsigned char*value, unsigned short*result );
void itoa( int value, unsigned char*result );
void LongToAscHex( int, unsigned char*, int );
void NibbleToHex( unsigned char value, unsigned char*result );
void WordToHex( unsigned short value, unsigned char*result );
unsigned char *GetAppName( unsigned char*name );
void APP_FINANCE( int, int );
void APP_Program( int, int );
void APP_SYSTEM_BATTERY( int opt );
void APP_SYSTEM_DISPLAY( int );
void APP_SYSTEM_LANGUAGE( int );
void APP_SYSTEM_POWER( int opt );
void APP_SYSTEM_RESET( void );
void APP_SYSTEM_VERSION( void );
void APP_SYSTEM( void );
void ResetAllDialog( void );
void Test1E44( void );
int EnableColor( int );
int GetMainBatteryVoltage( int one );
int SMEM_FindFirst( const unsigned short*pattern, unsigned short*foundfile );
int Timer_Deinstall( int InternalTimerID );
int Timer_Install( int InternalTimerID, void*handler, int elapse );
int Timer_Start( int InternalTimerID );
int Timer_Stop( int InternalTimerID );
unsigned char GetSetupSetting( unsigned int SystemParameterNo );
void CMT_Delay_100micros( int );
void CMT_Delay_micros( int );
void DisplayMainMenu( void );
void *GetStackPtr( void );
void HourGlass( void );
void OS_InnerWait_ms( int );
void SetSetupSetting( unsigned int SystemParameterNo, unsigned char SystemParameterValue );
void SMEM_maint( int );
void TestMode( int );
int sys_memcmp3(void *mem1, void *mem2, unsigned int n);
int sys_memcmp(const void *s1, const void *s2, unsigned int n);
int sys_strcmp_ignore_case( unsigned char*, unsigned char* );
int sys_strlen( const char* );
void *sys_memcpy(void *dest, const void *source, unsigned int n);
void *sys_memset(void *dest, int c, unsigned int n);
void sys_free( void*p );
void *sys_malloc( int );
void *sys_realloc( void*p, int );
int Bfile_CloseFile_OS( int HANDLE );
int Bfile_CreateEntry_OS( const unsigned short*filename, int mode, int*size );
int Bfile_DeleteEntry( const unsigned short *filename );
int Bfile_FindClose( int FindHandle );
int Bfile_FindFirst( const char *pathname, int *FindHandle, char *foundfile, void *fileinfo );
int Bfile_FindFirst_NON_SMEM( const char *pathname, int *FindHandle, char *foundfile, void *fileinfo );
int Bfile_FindNext( int FindHandle, char *foundfile, char *fileinfo );
int Bfile_FindNext_NON_SMEM( int FindHandle, char *foundfile, char *fileinfo );
int Bfile_GetFileSize_OS( int handle, int pos );
int Bfile_OpenFile_OS( const unsigned short*filename, int mode );
int Bfile_ReadFile_OS( int HANDLE, void *buf, int size, int readpos );
int Bfile_SeekFile_OS( int handle, int pos );
int Bfile_TellFile_OS( int handle ); 
int Bfile_WriteFile_OS( int HANDLE, const void *buf, int size );
void Bfile_NameToStr_ncpy( unsigned char*source, const unsigned short*dest, int n );
void Bfile_StrToName_ncpy( unsigned short*dest, const unsigned char*source, int n );
int CharacterSelectDialog( void );
int DefineStatusAreaFlags( int, int, void*, void* );
int EditMBStringChar( unsigned char*, int xposmax, int xpos, int );
int SetCursorFlashToggle( int );
int Test17BC( int );
unsigned char Syscall02A7( void );
unsigned char Syscall1816( int, int );
unsigned short Bdisp_GetPoint_DD( int x, int y );
unsigned short Bdisp_GetPoint_DD_Workbench( int x, int y );
unsigned short Bdisp_GetPoint_VRAM( int x, int y );
void APP_EACT_StatusIcon( int );
void AUX_DisplayErrorMessage( int msgno );
void BatteryIcon( unsigned int );
void Bdisp_AllClr_VRAM( void );
void Bdisp_AreaClr_DD_x3( void*p1 );
void Bdisp_AreaClr( void*p1, unsigned char P2, unsigned short color );
void Bdisp_Fill_VRAM( int color, int mode );
void Bdisp_HeaderFill2( unsigned int, unsigned int, unsigned char, unsigned char );
void Bdisp_HeaderFill( unsigned char, unsigned char );
void Bdisp_HeaderText2( void );
void Bdisp_HeaderText( void );
void Bdisp_PutDisp_DD_stripe( int y1, int y2 );
void Bdisp_PutDisp_DD( void );
void Bdisp_SetPoint_DD( int x, int y, int color );
void Bdisp_SetPoint_VRAM( int x, int y, int color );
void Bdisp_SetPointWB_VRAM( int x, int y, int color );
void Bdisp_ShapeBase3XVRAM( void*shape );
void Bdisp_ShapeBase( unsigned char*work, void*shape, int color, int line_width, int zero1, int zero2 );
void Bdisp_ShapeToVRAM16C( void*, int color );
//void Bdisp_WriteGraphVRAM( TDispGraph* );
//void Bdisp_WriteGraphVRAM_WB( TDispGraph* );
void Box2( int, int );
void BoxInnerClear( int );
void Box( int, int, int, int, int );
void BoxYLimits( int lines, int*top, int*bottom );
void Cursor_SetFlashOff( void );
void Cursor_SetFlashOn( unsigned char cursor_type );
void d_c_Icon( unsigned int );
void DefineStatusGlyph( int, void* );
void DefineStatusMessage( char*msg, short P2, char P3, char P4 );
void DirectDrawRectangle( int x1, int y1, int x2, int y2, unsigned short color );
void DispInt( int, int );
void DisplayMBString2( int, unsigned char*, int, int xpos, int zero, int x, int y, int, int, int );
void DisplayMBString( unsigned char*, int, int xpos, int x, int y );
void DisplayMessageBox( unsigned char*message );
void DisplayStatusArea( void );
void DrawFrame( int color );
void DrawFrameWorkbench( int, int, int, int, int );
void DrawHeaderLine( void );
void EditMBStringCtrl2( unsigned char*, int xposmax, void*, void*, void*, int, int, int, int );
void EditMBStringCtrl3( unsigned char*, int xposmax, void*, void*, void*, int, int, int, int, int );
void EditMBStringCtrl4( unsigned char*, int xposmax, void*, void*, void*, int, int, int, int, int, int );
void EditMBStringCtrl( unsigned char*, int xposmax, void*, void*, void*, int, int );
void EnableDisplayHeader( int, int );
void EnableStatusArea( int );
void FKey_Display( int, void* );
void GetFKeyPtr( int, void* );
void *GetMiniGlyphPtr( unsigned short mb_glyph_no, unsigned short*glyph_info );
void Keyboard_CursorFlash( void );
void KeyboardIcon( unsigned int );
void LineIcon( unsigned int );
void LoadVRAM_1( void );
void locate_OS( int X, int y );
void MsgBoxPop( void );
void MsgBoxPush( int lines );
void NormIcon( unsigned int );
void PrintCXY( int, int, unsigned char*, int, int, int, int, int, int );
void PrintGlyph( int, int, unsigned char*glyph, int, int color, int back_color, int );
void PrintLine2( int, int, unsigned char*, int, int, int, int, int );
void PrintLine( unsigned char*msg, int imax );
void PrintMiniGlyph(int x, int y, void*glyph, int mode_flags, int glyph_width, int, int, int, int, int color, int back_color, int );
void PrintMini( int*, int*, unsigned char*, int, int, int, int, int, int, int, unsigned int );
void Print_OS( unsigned char*msg, int invers, int zero2 );
void PrintXY_2( int mode, int x, int y, int msgno, int color );
void PrintXY( int x, int y, char*string, int mode, int color );
void ProgressBar0(int, int, int, int, int );
void ProgressBar(int, int );
void RadIcon( unsigned int );
void RealIcon( unsigned int );
void SaveVRAM_1( void );
void Scrollbar( void* );
void SetBackGround( int );
void SetupMode_StatusIcon( void );
void StandardScrollbar( void* );
void Syscall02A4( int, int );
void Syscall02A9( int );
void Test01A8(int,int,int);
void Test1B0E(void);
void WriteBackground( void*target, int width, int height, void*source, int, int, int );
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
int RTC_Elapsed_ms( int start_value, int duration_in_ms );
int RTC_GetTicks(void);
int RTC_Reset( int );
void RTC_GetTime( unsigned int*hour, unsigned int*minute, unsigned int*second, unsigned int*millisecond );
void RTC_SetDateTime( unsigned char*timestr );
int GetKey(int*key);
int GetKeyWait_OS(int*column, int*row, int type_of_waiting, int timeout_period, int menu, unsigned short*keycode );
int Test127E( int, int );
void PRGM_GetKey_OS( unsigned char*p );
void Set_FKeys1( unsigned int p1, unsigned int*P2 );
void Set_FKeys2( unsigned int p1 );
int Serial_Close( int mode );
int Serial_DirectTransmitOneByte( unsigned char byte_to_transmit );
int Serial_Open( unsigned char *mode );
