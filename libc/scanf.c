// Override libstdc++'s cin, even though I told it not to read input


int sscanf ( const char * str, const char * format, ...)
{
  return 0;
}