// Copyright MakeShape. 2019, All rights reserved.

#include "common.hh"
#include <cstdio>

namespace makeshape {
namespace common {

int dprintf(const char* format, ...) {
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
