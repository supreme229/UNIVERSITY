import matplotlib.pyplot as pyplot
from math import log, exp
import numpy as np

# * https://www.python-course.eu/python3_memoization.php
class Memoize:
    def __init__(self, fn):
        self.fn = fn
        self.memo = {}

    def __call__(self, *args):
        if args not in self.memo:
            self.memo[args] = self.fn(*args)
        return self.memo[args]


def execute_plot(filename):
    B, X, Y, D, Y2 = ([], [], [], [], [])
    fig, ax = pyplot.subplots()

    def h(x):
        index = X.index(x)
        return Y[index]

    def dot_product(f, h):
        result = 0
        for x in X:
            result += f(x) * h(x)
        return result

    @Memoize
    def c(k):
        return dot_product(lambda x: x * p(k - 1)(x), p(k - 1)) / dot_product(
            p(k - 1), p(k - 1)
        )

    @Memoize
    def d(k):
        return dot_product(p(k - 1), p(k - 1)) / dot_product(p(k - 2), p(k - 2))

    @Memoize
    def p(k):
        return lambda x: p_calc(x, k)

    @Memoize
    def a(k):
        return dot_product(lambda x: Y[x], p(k)) / dot_product(p(k), p(k))

    @Memoize
    def p_calc(x, k):
        if k == 0:
            return 1
        if k == 1:
            return x - c(k)
        else:
            return (x - c(k)) * p_calc(x, k - 1) - d(k) * p_calc(x, k - 2)

    @Memoize
    def w(x, m):
        sum = 0
        for i in range(0, m + 1):
            sum += a(i) * p(i)(x)
        return exp(sum)

    # * File read, sort and append to global X and Y arrays * #
    with open(filename, "r") as input:
        for line in input:
            if int(line) != 0:
                Y.append(log(int(line)))
                Y2.append(int(line))

    X = range(len(Y))

    # * plot * #
    values = [w(x, 20) for x in np.linspace(-4, 6, num=1000)]
    ax.plot(X, values, "r")
    ax.scatter(X, Y2, c="#ff7f0e")

    pyplot.show()


execute_plot("/home/suprememe/Desktop/University/Semestr 3/ANL/Lista11/z5/covid.csv")

execute_plot("/home/suprememe/Desktop/University/Semestr 3/ANL/Lista11/z5/deaths.csv")

execute_plot("/home/suprememe/Desktop/University/Semestr 3/ANL/Lista11/z5/recovery.csv")

execute_plot(
    "/home/suprememe/Desktop/University/Semestr 3/ANL/Lista11/z5/cases_confirmed.csv"
)