import math
from scipy.integrate import quad


def f3(x):
    return math.sin(7 * x - 2) / x


def T_0k(a, b, f, arr):
    for j in range(11):
        res = 0
        h_k = (b - a) / (2 ** j)
        n = 2 ** j
        for i in range(n + 1):
            if i == 0 or i == n:
                res += (1 / 2) * f(a + i * h_k)
            else:
                res += f(a + i * h_k)
        arr[0][j] = res * h_k
    return arr
