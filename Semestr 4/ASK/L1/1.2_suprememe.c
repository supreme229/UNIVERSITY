#include <stdio.h>
#include <stdint.h>

uint32_t test(uint32_t n)
{
    n = n & ~(n & ~(n - 1));
    return n;
}

void secret(uint8_t *to, uint8_t *from, size_t count)
{
    size_t n = (count + 7) / 8;
    static void *labels[] = {&&c0, &&c1, &&c2, &&c3, &&c4, &&c5, &&c6, &&c7};
    goto *labels[count % 8];
c0:
    *to++ = *from++;
c7:
    *to++ = *from++;
c6:
    *to++ = *from++;
c5:
    *to++ = *from++;
c4:
    *to++ = *from++;
c3:
    *to++ = *from++;
c2:
    *to++ = *from++;
c1:
    *to++ = *from++;

    if (--n > 0)
    {
        goto c0;
    }
}

int main()
{
    uint8_t from[11] = {1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12};
    uint8_t to[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (size_t count = 1; count < 12; count++)
    {
        secret(to, from, count);

        printf("count = %lu => ", count);
        for (int i = 0; i < 11; i++)
        {
            printf("%u ", to[i]);
            to[i] = 0;
        }
        printf("\n");
    }

    return 0;
}
