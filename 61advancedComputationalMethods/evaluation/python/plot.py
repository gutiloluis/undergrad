import numpy as np
import matplotlib.pyplot as plt

A = np.loadtxt("a.dat")

plt.plot(A[:,0], A[:,1])
plt.savefig("plot.png")
