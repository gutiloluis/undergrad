import matplotlib.pyplot as plt
import numpy as np

fig, axes = plt.subplots(nrows=10, ncols=3, figsize=(15,50))

for i in range(10):

    data = np.loadtxt(str(i)+".dat")
    axes[i,0].plot(data[:,1], data[:,2])
    axes[i,0].set_xlabel('$x$')
    axes[i,0].set_ylabel('$y$')

    axes[i,1].plot(data[:,2], data[:,3])
    axes[i,1].set_xlabel('$y$')
    axes[i,1].set_ylabel('$z$')

    axes[i,2].plot(data[:,1], data[:,3])
    axes[i,2].set_xlabel('$x$')
    axes[i,2].set_ylabel('$z$')
    
plt.savefig("figures.png")
    
