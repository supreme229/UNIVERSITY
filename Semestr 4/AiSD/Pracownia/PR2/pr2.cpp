#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <inttypes.h>
using namespace std;

int calculate_tower_height_v1(int k, int r2_1, vector<int> &t)
{
    int pl1 = abs(k - r2_1);
    int H_1 = t[pl1];
    int h_1 = H_1 - pl1;

    if (h_1 < 0)
    {
        return 0;
    }
    if (H_1 + k - h_1 == r2_1)
    {
        return H_1 + k;
    }
    return max(h_1 + k, H_1);
}

int calculate_tower_height_v2(int k, int r2_1, vector<int> &t, int s)
{

    if (k + r2_1 < s)
    {
        int H_1 = t[k + r2_1];
        int h_1 = H_1 - (k + r2_1);

        if (h_1 < 0)
        {
            return 0;
        }
        if (abs(h_1 + k - H_1) == r2_1)
        {
            if (h_1 + k > H_1)
            {
                return h_1 + k;
            }
            else
            {
                return H_1;
            }
        }
        if (H_1 + k - h_1 == r2_1)
        {
            return H_1 + k;
        }
    }
    return 0;
}

int main()
{
    ios::sync_with_stdio(false);
    int d, h, sum = 0;
    vector<int> heights;
    if (scanf("%d", &d) != 1)
    {
        printf("OK");
    }
    for (int i = 0; i < d; i++)
    {
        if (scanf("%d", &h) != 1)
        {
            printf("OK");
        }
        sum += h;
        heights.push_back(h);
    }
    int minn = sum, value_min = 0;
    sort(heights.begin(), heights.end());
    int sum2 = heights[0];
    vector<vector<int>> towers(2, vector<int>(sum + 1, 0));
    towers[0][heights[0]] = heights[0];
    for (int z = 1; z < (int)heights.size(); z++)
    {
        sum2 += heights[z];
        for (int j = 0; j <= sum2; j++)
        {
            if (
                (towers[1][j] = max(calculate_tower_height_v1(heights[z], j, towers[0]), calculate_tower_height_v2(heights[z], j, towers[0], sum + 1))) == 0)
            {
                towers[1][j] = towers[0][j];
            }

            if (towers[1][j] != 0 && j <= minn && towers[1][j] - j > 0 && towers[1][j] > value_min)
            {
                if (j == 0)
                {
                    minn = j;
                    value_min = towers[1][j];
                }
                else
                {
                    minn = j;
                    value_min = j;
                }
                if (z == (int)heights.size() - 1)
                {
                    break;
                }
            }
        }
        towers[0] = towers[1];
    }
    if (minn == 0)
    {
        printf("TAK\n");
        printf("%d", value_min);
    }
    else
    {
        printf("NIE\n");
        printf("%d", value_min);
    }
}