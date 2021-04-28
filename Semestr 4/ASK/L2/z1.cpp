#include <iostream>
#include <climits>
#include <cassert>
#include <iomanip> // std::setprecision

using namespace std;

int32_t threefourths(int32_t x)
{
    return ((x & 1) & ((x >> 1) & 1)) + (x >> 1) + (x >> 2);
}

int32_t sign(int32_t x)
{
    return ((x >> 31) | ((-x >> 31) & 1));
}

int main()
{
    int32_t x = INT32_MIN, y = 1, z;
    double dx, dy, dz;
    cout
        << endl;
    dx = (double)x;
    dy = (double)y;
    dz = (double)z;
    cout << (float)x << "  " << (float)dx << endl;                        // to zawsze bedzie równe bo zauważmy, że dokonujemy
                                                                          // z lewej strony bezpośredniego rzutowania inta na float'a, a z prawej najpierw int do double, a następnie do float
                                                                          // mamy tutaj taką samą utratę precyzji przez co wyniki nigdy się nie będą różnić
    cout << setprecision(31) << x - dy << " " << (double)(x - y) << endl; // nie działa dla x = INT32_MIN i y = 1, bo lewa strona się najpierw castuje do double a następnie wylicza
                                                                          // gdy z prawej castujemy po odejmowaniu, a z prawej mamy przepełnienie, które dało nam wynik dodatni gdy z lewej wciąż się miescimy na przedziale ujemnym.
    cout << (dx + dy) + dz << " " << dx + (dy + dz) << endl;              // to nie zadziała tylko gdy będzie niedomiar, a tu mamy liczby całkowite więc on nie nastąpi więc to prawda
    cout << (dx * dy) * dz << " " << dx * (dy * dz) << endl;              // tak samo jak wyżej
    cout << dx / dx << " " << dz / dz << endl;                            // fałsz gdy jedna z liczb jest bardzo bliska zeru wtedy mamy niedomiar powodujący dzielenie przez zero i dające NaN
}