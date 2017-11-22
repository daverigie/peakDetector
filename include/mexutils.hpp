#include <mex.h>   
#include <stdlib.h>
#include <iostream>

class mxstreambuf : public std::streambuf {
   public:
      mxstreambuf();
      ~mxstreambuf();

   protected:
      virtual std::streamsize xsputn( const char* s, std::streamsize n  ) override;
      virtual int overflow( int c = EOF ) override;

    private:
      std::streambuf *stdoutbuf;
};

