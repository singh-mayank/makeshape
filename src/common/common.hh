// Copyright MakeShape. 2019, All rights reserved.

#include <cstdarg>

#pragma once
#pragma warning( push )
#pragma warning( disable : 4018)
#pragma warning( disable : 4244)
#pragma warning( disable : 4996)
#pragma warning( pop )

namespace makeshape {
namespace common {

#define STR(x) #x
#define CHECK(x) if (!(x)) { \
    printf("Check failed: (%s), file %s, line %d.\n", STR(x), __FILE__, __LINE__); \
    abort(); \
}

int dprintf(const char* format, ...);

} // common
} // makeshape
