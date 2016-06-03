import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages
import numpy as np
import sys

data = np.loadtxt(sys.argv[1])
filename = sys.argv[1].split('.')[0] + ".pdf"

pp = PdfPages(filename)

fig, axes = plt.subplots(nrows = 2, ncols = 1)

axes[0].plot(data[:,0], data[:,1])
axes[0].set_xlabel('time')
axes[0].set_ylabel('Number of preys')
axes[0].set_title('Number of preys vs. time')

axes[1].plot(data[:,0], data[:,2], color = 'g')
axes[1].set_xlabel('time')
axes[1].set_ylabel('Number of predators')
axes[1].set_title('Number of predators vs. time')

fig.tight_layout()

plt.savefig(pp, format='pdf')

fig = plt.figure()

plt.plot(data[:,1], data[:,2], color = 'r')
plt.xlabel('Number of preys')
plt.ylabel('Number of predators')
plt.title('Number of predators vs. number of preys')
plt.axis('equal')

plt.savefig(pp, format='pdf')

pp.close()
