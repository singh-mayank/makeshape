// Copyright MakeShape. 2019, All rights reserved.

#include <cstdarg>

#pragma once

namespace makeshape {
namespace common {

#define STR(x) #x
#define CHECK(x) if (!(x)) { \
    printf("Check failed: (%s), file %s, line %d.\n", STR(x), __FILE__, __LINE__); \
    abort(); \
}

int dprintf(const char* format, ...) 
{
#ifdef NDEBUG
    return 0;
#else
  va_list vl;
  va_start(vl, format);
  auto ret = vprintf(format, vl);
  va_end(vl);
  return ret;
#endif
}

} // common
} // makeshape
