import math
from scipy.integrate import quad
import matplotlib.pyplot as plt

# lambda i k (domyślnie wybrałem takie wartości)
lamb = 4
k = 2

# Funkcja całkowana
def erlang(x):
    return (x ** (k - 1)) * (math.e ** (-lamb * x))


# Wyznaczenie pierwszej kolumny z optymalizacją podaną w dokumentacji
def T_0k(a, b, f, arr, w):
    for j in range(0, w):
        res = 0
        if j == 0:
            n = 1
            h_k = b - a
            res += (1 / 2) * f(a) + (1 / 2) * f(b)
            arr[0][j] = res
        else:
            n = 2 ** (j - 1)
            h_k = (b - a) / n
            for i in range(1, n + 1):
                res += f(a + (1 / 2) * (2 * i - 1) * h_k)
            res = (res * h_k) + arr[0][j - 1]
            arr[0][j] = res / 2
    return arr


# Wyznaczenie pojedynczego elementu tablicy Romberga (nie 1 kolumny)
def T_mk(T, m, k):
    T[m][k] = (((4 ** m) * T[m - 1][k + 1]) - T[m - 1][k]) / (4 ** m - 1)
    return T


# Wyliczenie całki z rozkładu Erlanga (w - ilość węzłów, l - wartość lambda, k1 - wartość k, a - dolna granica całkowania, b - górna granica)
def erlang_integral(w, l, k1, a, b):
    # Ustawienie lambdy i k na wybrane wartości, (lamb i k to zmienne globalne)
    lamb = l
    k = k1

    T = [[0 for x in range(w + 1)] for y in range(w + 1)]

    # Wyliczenie pierwszej kolumny tablicy Romberga
    T = T_0k(a, b, erlang, T, w + 1)

    # Wyliczenie dalszej zawartości tablicy Romberga
    for i in range(1, w + 1):
        for j in range(0, w + 1 - i):
            T = T_mk(T, i, j)

    # Wykorzystanie wyznaczonej wartości przed całką (znajduję się to w dokumentacji)
    T = [[((lamb ** k) / (math.factorial(k - 1)) * j) for j in i] for i in T]

    # Ostateczny wynik Romberga
    print("Metoda Romberga daje wynik:", T[w][0])
    # Ostateczny wynik złożonych trapezów
    print("Metoda złożonych trapezów daje wynik:", T[0][w])
    # wykorzystałem funkcję wbudowaną biblioteki math w pythonie. Daje ona dość dobre wyniki, porównując rzeczywiste wartości całek.
    print(
        "Błąd bezwzględny metody Romberga: ",
        abs((lamb ** k) / (math.factorial(k - 1)) * quad(erlang, a, b)[0] - T[w][0]),
    )
    print(
        "Błąd bezwzględny metody trapezów: ",
        abs((lamb ** k) / (math.factorial(k - 1)) * quad(erlang, a, b)[0] - T[0][w]),
    )


# przykładowe wyniki
print("Dla 2^6 węzłów:")
erlang_integral(6, 4, 2, 0, 16)
print()
print("Dla 2^8 węzłów:")
erlang_integral(8, 4, 2, 0, 16)
print()
print("Dla 2^10 węzłów:")
erlang_integral(10, 4, 2, 0, 16)
print()
print("Dla 2^12 węzłów:")
erlang_integral(12, 4, 2, 0, 16)
print()


# Dodatek:
# wykresy, które zamieściłem w dokumentacji :)

points = [[0 for x in range(2)] for y in range(32)]

lamb = 1.5

for i in range(0, 32):
    k = i + 1
    points[i][0] = i + 1
    points[i][1] = (lamb ** k) / (math.factorial(k - 1)) * quad(erlang, 0, 12)[0]

f1 = plt.figure()
f2 = plt.figure()
ax1 = f1.add_subplot(111)
ax1.set(xlabel="Wartość k", ylabel="Wartość całki")
ax1.grid()
ax1.plot(*zip(*points), marker="o", color="r", ls="")

lamb = 0.5
k = 60

for i in range(0, 32):
    lamb += 0.5
    points[i][0] = lamb
    points[i][1] = (lamb ** k) / (math.factorial(k - 1)) * quad(erlang, 0, 12)[0]

ax2 = f2.add_subplot(111)
ax2.set(xlabel="Wartość lambdy", ylabel="Wartość całki")
ax2.grid()
ax2.plot(*zip(*points), marker="o", color="r", ls="")
plt.show()