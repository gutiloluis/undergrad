import matplotlib.pyplot as plt
import numpy as np
import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D

R = 6378.1

A = np.loadtxt("trayectoria_0.001_0.5.dat")

x = A[:,1]
y = A[:,2]
z = A[:,3]

mpl.rcParams['legend.fontsize'] = 10

fig = plt.figure()
ax = fig.gca(projection='3d')

ax.plot(x[:60000], y[:60000], z[:60000], label='parametric curve')
ax.legend()

plt.show()
plt.savefig('a.png')


