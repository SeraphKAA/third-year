import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

fig = plt.figure(figsize=(7, 4))
ax_3d = fig.add_subplot(projection='3d')

x = np.linspace(0, 10, 50)
y = np.linspace(0, 10, 50)
z = np.cos(x) + y**2
ax_3d.plot(x, y, z)


plt.show()