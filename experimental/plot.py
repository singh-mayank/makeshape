import numpy as np
import matplotlib.pyplot as plt
from numpy import genfromtxt

data = genfromtxt('samples.csv', delimiter=',')
print(data.size)
print(data.shape)

x = data[:,0]
y = data[:,1]

plt.scatter(x, y)
plt.show()
