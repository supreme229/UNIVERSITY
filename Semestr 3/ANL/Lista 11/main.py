import matplotlib.pyplot as pyplot
import numpy as np


class Memoize:
    def __init__(self, fn):
        self.fn = fn
        self.memo = {}

    def __call__(self, *args):
        if args not in self.memo:
            self.memo[args] = self.fn(*args)
        return self.memo[args]


# ** Global variables ** #
B, X, Y, filename, = (
    [],
    [],
    [],
    "/home/suprememe/Desktop/University/Semestr 3/ANL/Lista11/punkty.csv",
)
fig, ax = pyplot.subplots(9)

# * a) *#
def f1(t):
    return (t + 3.6) * (t - 2.1) * (t - 3.7)


# * b) *#
def map_list(f, x):
    return list(map(f, x))


def calculate_b(x, f):
    n = len(x) - 1
    result = map_list(f, x)
    for i in range(1, n + 1):
        for j in range(n, i - 1, -1):
            result[j] = (result[j] - result[j - 1]) / (x[j] - x[j - i])
    return result


def function(x):
    global B, X
    p = 1
    l = 0
    for i in range(0, 50):
        l += B[i] * p
        p *= x - X[i]

    return l


# * c) *#
def h(x):
    index = X.index(x)
    return Y[index]


def dot_product(f, h):
    result = 0
    for x in X:
        result += f(x) * h(x)
    return result


@Memoize
def p_calc(k, x):
    if k == 0:
        return 1
    if k == 1:
        return x - c(k)
    else:
        return (x - c(k)) * p_calc(k - 1, x) - d(k) * p_calc(k - 2, x)


@Memoize
def p(k):
    return lambda x: p_calc(k, x)


@Memoize
def c(k):
    return dot_product(lambda x: x * p(k - 1)(x), p(k - 1)) / dot_product(
        p(k - 1), p(k - 1)
    )


@Memoize
def d(k):
    return dot_product(p(k - 1), p(k - 1)) / dot_product(p(k - 2), p(k - 2))


@Memoize
def a(k):
    return dot_product(h, p(k)) / dot_product(p(k), p(k))


@Memoize
def w(x, m):
    sum = 0
    for i in range(0, m + 1):
        sum += a(i) * p(i)(x)
    return sum


data = [[0 for x in range(2)] for y in range(50)]

# * File read, sort and append to global X and Y arrays * #
with open(filename, "r") as input:
    i = 0
    for line in input:
        curr_line = line.split(",")
        data[i][0] = float(curr_line[0])
        data[i][1] = float(curr_line[1])
        i += 1

data.sort(key=lambda x: x[0])

for i in range(0, 50):
    X.append(data[i][0])
    Y.append(data[i][1])

args = np.arange(-4.5, 5.5, 0.1)

# * set plots positions * #
line = 0
for i in range(1, 10):
    if (i - 1) % 2 == 0:
        line += 1
        pos = [0.10, 1.00 - line * 0.17, 0.3, 0.1]
    else:
        pos = [0.55, 1.00 - line * 0.17, 0.3, 0.1]
    ax[i - 1].set_position(pos)


# * plot a) * #
ax[0].plot(args, f1(args))
ax[0].set_title("Funkcja f(t)")
ax[0].scatter(X, Y, c="#ff7f0e")
ax[0].grid(True)


# * plot b) * #

arr = np.linspace(-4, 6, num=100)

values = [w(x, 49) for x in arr]
ax[1].plot(arr, values, "g")
ax[1].set_title("w* o stopniu 49")

# * plot c) * #
for i in range(2, 50):
    values = [w(x, i) for x in arr]
    if i == 49:
        ax[2].plot(arr, values, "g")
        ax[2].plot(args, f1(args), "r")
        ax[2].scatter(X, Y, c="#ff7f0e")
        ax[2].set_title("w* o stopniu 49" + str(i) + " oraz f(t)")
        ax[2].set_ylim(-25, 45)

pyplot.show()
