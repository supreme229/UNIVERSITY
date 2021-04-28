import math
import numpy
from scipy.integrate import quad
import matplotlib.pyplot as pyplot


def f1(x):
    return 1 / (1 + x ** 2)


def f2(t, i, n):
    res = 1
    for j in range(n + 1):
        if j != i:
            res *= t - j
    return res


def x1(a, b, n):
    arr, k = [], 0
    h = (b - a) / n
    while k <= n:
        x_k = a + k * h
        arr.append(x_k)
        k += 1

    return arr


def calc_A(a, b, x, n):
    arr, h = [-1] * (n + 1), (b - a) / n

    for k in range(n + 1):
        if arr[n - k] != -1:
            arr[k] = arr[n - k]
        else:
            mult_a = (((-1) ** (n - k)) * h) / (
                math.factorial(k) * math.factorial(n - k)
            )
            mult_b = quad(f2, 0, n, args=(k, n))
            res = mult_a * mult_b[0]
            arr[k] = res
    return arr


def Nn(n, A, x):
    sum = 0
    for k in range(n + 1):
        sum += A[k] * f1(x[k])
    return sum


def lagrange_product(n, x, args, i):
    result = 1
    for j in range(n + 1):
        if j != i:
            result *= (x - args[j]) / (args[i] - args[j])
    return result


def lagrange(x, n, vals, args):
    sum = 0
    for i in range(n + 1):
        sum += vals[i] * lagrange_product(n, x, args, i)
    return sum


iter = 0
for i in range(2, 21, 2):
    lagr = []
    X1 = numpy.linspace(-3, 3, i + 1)
    Y1 = [f1(x) for x in X1]
    X = numpy.linspace(-3, 3, 100)
    pts = [f1(x) for x in X]
    for x in X:
        lagr.append(lagrange(x, i, Y1, X1))
    pyplot.plot(X, pts)
    pyplot.plot(X, lagr)
    pyplot.title("n = " + str(i))
    iter += 1
    arr = x1(-3, 3, i)
    A = calc_A(-3, 3, arr, i)
    print(
        "Dla n =",
        i,
        "bład względny procentowy wynosi:",
        (abs((2 * math.atan(3) - Nn(i, A, arr))) / (2 * math.atan(3))) * 100,
        "%",
    )
    pyplot.show()
