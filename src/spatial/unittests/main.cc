// Copyright MakeShape. 2019, All rights reserved.

// #define RUN_LEAKS_ON_MAC

#include "gtest/gtest.h" 

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
#if RUN_LEAKS_ON_MAC
    const auto val = RUN_ALL_TESTS();
    int x;
    std::cin >> x;
    return val;
#else
    return RUN_ALL_TESTS();
#endif
}
