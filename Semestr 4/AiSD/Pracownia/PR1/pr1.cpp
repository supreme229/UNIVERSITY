#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <inttypes.h>

using namespace std;

unsigned long long get_result(unsigned long long occurences)
{
    unsigned long long result = 0;
    for (int i = 1; i < 64; i++)
    {
        if ((occurences & 1) == 1)
        {
            result += 1;
        }
        occurences >>= 1;
    }
    return result;
}

pair<unsigned long long, unsigned long long> two_evens(unsigned long long number, unsigned long long occurences)
{
    pair<unsigned long long, unsigned long long> res;
    while (number % 2 == 0)
    {
        number >>= 1;
        occurences <<= 1;
    }
    res.first = number;
    res.second = occurences;
    return res;
}

int main()
{
    ios::sync_with_stdio(false);

    vector<pair<unsigned long long, unsigned long long>>
        number_occs;
    pair<unsigned long long, unsigned long long> p1;
    unsigned long long n, number, occurences, result = 0;
    if (scanf("%llu", &n) != 1)
    {
        {
            printf("Enter llu!");
        }
    }
    for (unsigned long long i = 0; i < n; i++)
    {
        if (scanf("%llu"
                  "%llu",
                  &number, &occurences) != 2)
        {
            printf("Enter llu!");
        }
        if ((number % 2 == 0 && occurences % 2 != 0) || (number % 2 == 0 && occurences % 2 == 0))
        {
            pair<unsigned long long, unsigned long long> p2;
            p2 = two_evens(number, occurences);
            number = p2.first;
            occurences = p2.second;
        }
        p1.first = number;
        p1.second = occurences;
        number_occs.push_back(p1);
    }

    sort(number_occs.begin(), number_occs.end());

    pair<unsigned long long, unsigned long long> temp;
    for (unsigned long long i = 1; i < number_occs.size(); i++)
    {
        if (number_occs[i].first == number_occs[i - 1].first)
        {
            number_occs[i].second += number_occs[i - 1].second;
            number_occs[i - 1].second = 0;
        }
    }

    for (unsigned long long i = 0; i < number_occs.size(); i++)
    {
        if (number_occs[i].second != 0)
        {
            result += get_result(number_occs[i].second);
        }
    }
    printf("%llu", result);
}