#!/usr/bin/python

import sys
from mpl_toolkits import mplot3d
import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt(open(sys.argv[1], "rb"), delimiter=",").T
fig = plt.figure()
ax = plt.axes(projection='3d')
ax.scatter3D(data[1], data[2], data[3], c=data[0], cmap='Greens', s=1)
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')
plt.savefig(sys.argv[1] + '.png', dpi=300)
