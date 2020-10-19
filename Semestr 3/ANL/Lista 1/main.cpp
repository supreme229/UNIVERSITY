#include <iostream>
#include <cmath>

using namespace std;

double function(double x)
{
    return 4040.0 * (sqrt(pow(x,11.0) + 1) - 1) / pow(x,11.0);
}

double function_better(double x)
{
    return 4040 * (1/(sqrt(pow(x,11.0) + 1) + 1));
}

double function2(double x)
{
    return 12120 * (x-sin(x))/pow(x,3);
}

void function3(int n)
{
    double y0 = 1;
    double y1 = -1.0/7.0;
    double yn;
    for(int i = 2; i <= n;i++)
    {
        yn = (1.0/7.0)*(69.0*y1 + 10.0*y0);
        cout << "Dla y" << i << " wynik to: " << yn << endl;
        y0 = y1;
        y1 = yn;
    }
}

void function4(int n)
{
    double I0 = log(2021.0/2020.0);
    double In = 0;
    cout << "Dla n: 0" << " wynik to: " << I0 << endl;
    for (int i = 1; i <= n; i++)
    {
        In = (1/n) - 2020 * I0;
        cout << "Dla n: " << i << " wynik to: " << In << endl;
        I0 = In;
    }
}

double function5(int n)
{
    double result = 0;
    for(int i=0 ;i<=n;i++)
    {
        result += (pow(-1.0,i))/(2.0*i+1.0);
    }
    result *= 4;
    if(abs(result - M_PI) < pow(10.0,-4))
        return n;
    else function5(n+1);
}

int main()
{
    cout << function(0.01) << endl;
    cout << function_better(0.001) << endl;
    cout << function2(pow(10,-20)) << endl;
    function3(30);
    function4(20);
    cout << function5(1) << endl;
}
