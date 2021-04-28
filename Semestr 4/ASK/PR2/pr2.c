#include <stdio.h>
#include <limits.h>
#include <inttypes.h>

int64_t dodaj(int64_t a, int64_t b)
{
    int64_t res = 0;
    int8_t x, y;
    for (int i = 0; i < 8; i++)
    {
        x = (a >> (i * 8));
        y = (b >> (i * 8));
        int64_t temp3 = (x + y) << (i * 8);
        int flag = 0;

        if (x >= 0 && y >= 0)
        {
            if (INT8_MAX - x <= y)
            {
                res |= (INT8_MAX) << (i * 8);
                flag = 1;
            }
        }
        else if (x <= 0 && y <= 0)
        {
            if (INT8_MIN - x >= y)
            {
                res |= (INT8_MIN) << (i * 8);
                flag = 1;
            }
        }
        if (flag == 0)
        {
            res |= temp3;
        }
    }
    return res;
}

int main()
{
    int64_t temp1 = 103324324, temp2 = 2;
    int8_t x, y;
    x = (temp1 >> (0 * 8));

    printf("%" PRId64 "\n", dodaj(0x207F01807F7F7F7F, 0x01FFFFFFFCFDFEFF));
}