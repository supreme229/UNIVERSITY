import numpy

tab = [[0.0, 10.0, 20.0, 30.0, 40.0, 80.0, 90.0, 95.0],
       [68.0, 67.1, 66.4, 65.6, 64.6, 61.8, 61.0, 60.0]]


def g_0(x):
    return tab[0][x]


def g_1(x):
    return 1


def y(x):
    return tab[1][x]


def i_s(do, f, g):
    suma = 0
    for k in range(do + 1):
        suma += f(k) * g(k)
    return suma

g0g0 = (i_s(7, g_0, g_0))
g1g0 = (i_s(7, g_1, g_0))
g1g1 = (i_s(7, g_1, g_1))
yg0 = (i_s(7, y, g_0))
yg1 = (i_s(7, y, g_1))

# | 26525.0 |  365.0  | a_0 |  =  22685.0
# | 365.0   |  8      | a_1 |  =  514.5

# wyznaczamy wyznacznik Wa_0
M1 = [[yg0, yg1], [g1g0, g1g1]]
Wa_0 = (numpy.linalg.det(M1))

# wyznaczamy wyznacznik Wa_1
M2 = [[g0g0, g1g0], [yg0, yg1]]
Wa_1 = (numpy.linalg.det(M2))

M3 = [[g0g0, g1g0], [g1g0, g1g1]]
W = (numpy.linalg.det(M3))

print("Nasze a_0 to:", (Wa_0 / W))
print("Nasze a_1 to:", (Wa_1 / W))
