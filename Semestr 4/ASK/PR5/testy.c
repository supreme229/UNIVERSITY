#include <stdio.h>
#include <limits.h>
#include <inttypes.h>

int mod17(uint32_t x)
{
    x = x & 0x5555555555555555; //restrict to odd bits.
    x = (x | (x >> 1)) & 0x3333333333333333;
    x = (x | (x >> 2)) & 0x0f0f0f0f0f0f0f0f;
    x = (x | (x >> 4)) & 0x00ff00ff00ff00ff;
    x = (x | (x >> 8)) & 0x0000ffff0000ffff;
    x = (x | (x >> 16)) & 0x00000000ffffffff;

    return x;
}

int main()
{
    printf("%d", mod17(3214));
}