import matplotlib.pyplot as plt
import matplotlib.animation as an
from Vector3 import Vec3
import numpy as np

def update(frame):
    pos_x = x[frame]
    pos_y = y[frame]
    data = np.stack([pos_x, pos_y]).T
    scat.set_offsets(data)
    return scat


x=[]
y=[]

i = 0
while i < 4:
    x.append(i)
    y.append(i)
    i = i + 0.01

fig, ax = plt.subplots()
scat = ax.scatter(x, y)
ani = an.FuncAnimation(fig=fig, func=update, frames=len(x), interval=30, repeat=False)
plt.show()