#include <stdio.h>
#include <stdint.h>

// Obstawiam, że da się lepiej narazie niech będzie tak //

uint32_t zero(uint32_t x, uint32_t k)
{
    uint32_t b1 = 0x1;
    uint32_t mask = ~(b1 << k);
    uint32_t res = x & mask;

    return res;
}

uint32_t copy_bit(uint32_t x, uint32_t i, uint32_t k)
{
    uint32_t i_numb = (x >> i) & 1;
    i_numb = i_numb << k;
    x = zero(x, k);
    return x | i_numb;
}

int main()
{
    printf("%u\n", copy_bit(52, 1, 2));
    printf("%u\n", copy_bit(52, 2, 3));
    return 0;
}