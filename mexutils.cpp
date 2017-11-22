#include <mex.h>   
#include <stdlib.h>
#include <iostream>
#include "mexutils.hpp"


mxstreambuf::mxstreambuf() {
      stdoutbuf = std::cout.rdbuf( this );
}
mxstreambuf::~mxstreambuf() {
      std::cout.rdbuf( stdoutbuf );
}

std::streamsize mxstreambuf::xsputn( const char* s, std::streamsize n )  {
      mexPrintf( "%.*s", n, s );
      return n;
}

int mxstreambuf::overflow( int c ) {
      if( c != EOF ) {
            mexPrintf( "%.1s", & c );
      }
      return 1;
}

