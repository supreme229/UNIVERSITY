#include<iostream>
#include<cmath>
using namespace std;

void function(int x_n)
{   
    double x1 = 2.0;
    double result = 2.0;
    for(double i = 2.0; i <= x_n; i=i + 1.0)
    {
        result = pow(2, i-1) * sqrt(2.0*(pow(x1/pow(2.0,i-1),2.0) / (1.0 + sqrt(1.0 - pow(x1/pow(2.0,i-1),2.0)))));
        x1 = result;
    }
    cout << result;
}


int main()
{
    function(30);
}