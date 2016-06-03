import matplotlib.pyplot as plt
import numpy as np

A = np.loadtxt('line_2.dat')

#By inspection of the parameter sampling maximum
a = 18.5
b = 2.1
c = 0.95
d = 6.2
x = np.linspace(-15,10,1000)

plt.scatter(A[:,0],A[:,1])
plt.plot(x, a*np.exp(-(x**2)/(2.0 *b**2))+ c*x + d)
plt.savefig('mcmc_parameters.png')
plt.show()
