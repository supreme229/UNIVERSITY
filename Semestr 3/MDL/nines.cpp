#include <iostream>
using namespace std;

long long if_got_nine(long long start, long long end)
{
    long long result = 0, temp;
    for(long long i = start; i <= end; i++)
    {
        temp = i;
        while(temp > 0)
        {
            if(temp%10 == 9)
            {
                result++;
                break;
            }
            else
            {
                temp /= 10;
            }
        }
    }
    return result;
}

int main()
{
    cout << if_got_nine(1, 10000000000) << endl;
}