import numpy
import math

tab = [[0.0, 2.0, 4.0,6.0,8.0,10.0], [1.0,1.6,1.4,0.6,0.2,0.8]]

def g_0(x):
    return 1
    
def g_1(x):
    return math.sin((2.0 * math.pi * tab[0][x]) / 12.0)
    
def g_2(x):
    return math.cos((2.0 * math.pi * tab[0][x]) / 12.0)
    
def y(x):
    return tab[1][x]
    
def i_s(do, f, g):
    suma = 0
    for i in range(do + 1):
        suma += f(i) * g(i)
    return suma

g0g0 = (i_s(5, g_0, g_0))
g0g1 = (i_s(5, g_0, g_1))
g0g2 = (i_s(5, g_0, g_2))
g1g0 = (i_s(5, g_1, g_0))
g1g1 = (i_s(5, g_1, g_1))
g1g2 = (i_s(5, g_1, g_2))
g2g2 = (i_s(5, g_2, g_2))
g2g1 = (i_s(5, g_2, g_1))
g2g0 = (i_s(5, g_2, g_0))
yg0  = (i_s(5, y, g_0))
yg1  = (i_s(5, y, g_1))
yg2  = (i_s(5, y, g_2))


# | 6.0         | 4.44e-16    | -1.1e-16  |  a_0  | =  5.6  
# | 4.44e-16    | 3.0         | 2.78e-16  | a_1   | =  1.73
# | -1.1e-16    | 2.78e-16    | 3.0       | a_2   | =  0.8

# wyznaczmy wyznacznik W
M1 = [[g0g0, g0g1, g0g2], [g1g0, g1g1, g1g2], [g2g0, g2g1, g2g2]]
W = (numpy.linalg.det(M1))

# wyznaczamy wyznacznik Wa_0
M2 = [[yg0, yg1, yg2], [g1g0, g1g1, g1g2], [g2g0, g2g1, g2g2]]
Wa_0 = (numpy.linalg.det(M2))

# wyznaczmy wyznacznik Wa_1
M3 = [[g0g0, g0g1, g0g2], [yg0, yg1, yg2], [g2g0, g2g1, g2g2]]
Wa_1 = (numpy.linalg.det(M3))

# wyznaczmy wyznacznik Wa_2
M4 = [[g0g0, g0g1, g0g2], [g1g0, g1g1, g1g2], [yg0, yg1, yg2]]
Wa_2 = (numpy.linalg.det(M4))

print(Wa_0 / W)
print(Wa_1 / W)
print(Wa_2 / W)



    