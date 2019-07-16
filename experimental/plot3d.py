import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d
#from numpy import genfromtxt

fig = plt.figure()
ax = plt.axes(projection='3d')

#data = genfromtxt('samples.csv', delimiter=',')
#print(data.size)
#print(data.shape)
#x = data[:,0]
#y = data[:,1]
#z = data[:,2]

# Data for three-dimensional scattered points
zdata = 15 * np.random.random(100)
xdata = np.sin(zdata) + 0.1 * np.random.randn(100)
ydata = np.cos(zdata) + 0.1 * np.random.randn(100)
ax.scatter3D(xdata, ydata, zdata, c=zdata, cmap='Greens');

ax.set_xlabel('X Label')
ax.set_ylabel('Y Label')
ax.set_zlabel('Z Label')


plt.show()
