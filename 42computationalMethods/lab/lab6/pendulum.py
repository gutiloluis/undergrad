import numpy as np
import matplotlib.pyplot as plt
import sys

h=0.01
min_x = 0.0
max_x = 12.0
n_points = int((max_x-min_x)/h)
x = np.zeros(n_points)
y_1 = np.zeros(n_points)
y_2 = np.zeros(n_points)


def func_prime_1(x, y_1, y_2):
    return y_2

def func_prime_2(x, y_1, y_2):
    return -4*np.sin(y_1)

def RungeKuttaFourthOrderStep(x_old, y1_old, y2_old):
    
    k_1_prime1 = func_prime_1(x_old,y1_old, y2_old)
    k_1_prime2 = func_prime_2(x_old,y1_old, y2_old)
    
    #first step
    x1 = x_old+ (h/2.0)
    y1_1 = y1_old + (h/2.0) * k_1_prime1
    y2_1 = y2_old + (h/2.0) * k_1_prime2
    k_2_prime1 = func_prime_1(x1, y1_1, y2_1)
    k_2_prime2 = func_prime_2(x1, y1_1, y2_1)
    
    #second step
    x2 = x_old + (h/2.0)
    y1_2 = y1_old + (h/2.0) * k_2_prime1
    y2_2 = y2_old + (h/2.0) * k_2_prime2
    k_3_prime1 = func_prime_1(x2, y1_2, y2_2)
    k_3_prime2 = func_prime_2(x2, y1_2, y2_2)
    
    
    #third
    x3 = x_old + h
    y1_3 = y1_old + h * k_3_prime1
    y2_3 = y2_old + h * k_3_prime2
    k_4_prime1 = func_prime_1(x3, y1_3, y2_3)
    k_4_prime2 = func_prime_2(x3, y1_3, y2_3)
    
    #fourth step
    average_k_1 = (1.0/6.0)*(k_1_prime1 + 2.0*k_2_prime1 + 2.0*k_3_prime1 + k_4_prime1)
    average_k_2 = (1.0/6.0)*(k_1_prime2 + 2.0*k_2_prime2 + 2.0*k_3_prime2 + k_4_prime2)
    
    x_new = x_old + h
    y_1_new = y1_old + h * average_k_1
    y_2_new= y2_old + h * average_k_2
    return x_new, y_1_new, y_2_new

x[0]   = min_x
y_1[0] = float(sys.argv[1])
y_2[0] = float(sys.argv[2])    

for i in range(1,n_points):
    x[i],y_1[i],y_2[i] = RungeKuttaFourthOrderStep(x[i-1], y_1[i-1], y_2[i-1])
    print x[i], "  ", y_1[i]

np.savetxt("pendulum_data.dat",np.column_stack((x,y_1)), fmt = "%f")
