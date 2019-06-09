// Copyright MakeShape. 2019, All rights reserved.

#pragma once

#define STR(x) #x
#define CHECK(x) if (!(x)) { \
    printf("Check failed: (%s), file %s, line %d.\n", STR(x), __FILE__, __LINE__); \
    abort(); \
}
