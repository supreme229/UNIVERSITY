#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

void printBits(size_t const size, void const *const ptr)
{
    unsigned char *b = (unsigned char *)ptr;
    unsigned char byte;
    int i, j;

    for (i = size - 1; i >= 0; i--)
    {
        for (j = 7; j >= 0; j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

uint64_t test(uint64_t x)
{
    x = (0x5555555555555555 & x) + ((x >> 1) & 0x5555555555555555);
    x = (0x3333333333333333 & x) + ((x >> 2) & 0x3333333333333333);
    x = (0x0F0F0F0F0F0F0F0F & x) + ((x >> 4) & 0x0F0F0F0F0F0F0F0F);
    x = (0x00FF00FF00FF00FF & x) + ((x >> 8) & 0x00FF00FF00FF00FF);
    x = (0x0000FFFF0000FFFF & x) + ((x >> 16) & 0x0000FFFF0000FFFF);
    x = (0xFFFFFFFF00000000 & x) + ((x >> 32) & 0xFFFFFFFF00000000);
    return x;
}

int nlz(unsigned long x)
{
    unsigned long y;
    long n, c;
    n = 64;
    c = 32;
    do
    {
        y = x >> c;
        if (y != 0)
        {
            n = n - c;
            x = y;
        }
        c = c >> 1;
    } while (c != 0);
    return n - x;
}

uint64_t zeroer(uint64_t y)
{
    uint64_t z = y;
    y = y | (y >> 1);
    y = y | (y >> 2);
    y = y | (y >> 4);
    y = y | (y >> 8);
    y = y | (y >> 16);
    y = y | (y >> 32);
    //============
    /*
    y = (y & 0x5555555555555555) + ((y >> 1) & 0x5555555555555555);
    y = (y & 0x3333333333333333) + ((y >> 2) & 0x3333333333333333);
    y = (y & 0x0F0F0F0F0F0F0F0F) + ((y >> 4) & 0x0F0F0F0F0F0F0F0F);
    y = (y & 0x00FF00FF00FF00FF) + ((y >> 8) & 0x00FF00FF00FF00FF);
    y = (y & 0x0000FFFF0000FFFF) + ((y >> 16) & 0x0000FFFF0000FFFF);
    y = (y & 0x00000000FFFFFFFF) + ((y >> 32) & 0x00000000FFFFFFFF);
    */
    return y;
}

int main()
{
    //printf("%" PRIu64, zeroer(0x001F089ADF39FE00));
    //printf("%" PRIu64, zeroer(0x10000));

    //printf("%" PRIu64, test(4));

    uint64_t i = 131071;
    //printf("%" PRIu64, zeroer(0xffffffffffffffff));
    printBits(sizeof(i), &i);
    i = 0x10000;
    printBits(sizeof(i), &i);
    //i = zeroer(0x10000);
    //printBits(sizeof(i), &i);
    return 0;
}
