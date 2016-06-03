import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt("pendulum_data.dat")

plt.plot(data[:,0], data[:,1])
plt.savefig("plot.png")
plt.show()
