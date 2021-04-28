import math
from scipy.integrate import quad
import matplotlib.pyplot as plt

a = 2
b = 5


def erlang(x):
    return (x ** (b - 1)) * (math.e ** (-a * x))


def T_0k(a, b, f, arr):
    for j in range(0, 11):
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


def T_mk(T, m, k):
    T[m][k] = (((4 ** m) * T[m - 1][k + 1]) - T[m - 1][k]) / (4 ** m - 1)
    return T


def t_c():
    print("Podpunkt c)\n\n")
    T = [[0 for x in range(11)] for y in range(11)]

    T = T_0k(2, 3 * math.pi, f3, T)
    for i in range(1, 11):
        for j in range(0, 11 - i):
            T = T_mk(T, i, j)

    min = 10000000
    for i in range(0, 11):
        for j in range(0, 11 - i):
            if T[i][j] != 0:
                print(
                    f"T{i}_{j} =",
                    T[i][j],
                    end="\n",
                )
            print()
    print("Correct:", quad(f3, 2, 3 * math.pi)[0])


def erlang_integral():
    print("Podpunkt d)\n\n")
    T = [[0 for x in range(11)] for y in range(11)]

    T = T_0k(0, 12, erlang, T)
    for i in range(1, 11):
        for j in range(0, 11 - i):
            T = T_mk(T, i, j)
    T = [[((a ** b) / (math.factorial(b - 1)) * j) for j in i] for i in T]
    min = 10000000
    for i in range(0, 11):
        for j in range(0, 11 - i):
            if T[i][j] != 0:
                print(
                    f"T{i}_{j} =",
                    abs(0.999999379330130 - T[i][j]),
                    end="\n",
                )
            print()


erlang_integral()

points = [[0 for x in range(2)] for y in range(8)]

for i in range(0, 8):
    b = i + 1
    points[i][0] = i + 1
    points[i][1] = (a ** b) / (math.factorial(b - 1)) * quad(erlang, 0, 12)[0]
    print("Correct:", (a ** b) / (math.factorial(b - 1)) * quad(erlang, 0, 12)[0])

plt.plot(*zip(*points), marker="o", color="r", ls="")
# t_erlang()
