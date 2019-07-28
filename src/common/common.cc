// Copyright MakeShape. 2019, All rights reserved.

#include "common.hh"
#include <cstdio>

namespace makeshape {
namespace common {

int dprintf(const char *format, ...) {
#ifdef NDEBUG
    return 0;
#else
   va_list arg;
   int done;

   va_start (arg, format);
   done = vfprintf (stdout, format, arg);
   va_end (arg);

   return done;
#endif
}

} // common
} // makeshape
