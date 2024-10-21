import matplotlib.pyplot as plt
from matplotlib import animation
import matplotlib; matplotlib.use("TkAgg")
from Vector3 import Vec3
import numpy as np

x=[]
y=[]

def update(frame):
    pos_x = x[frame]
    pos_y = y[frame]
    data = np.stack([pos_x, pos_y]).T
    scat.set_offsets(data)
    return scat


pointAccroche = Vec3(0,10,0)
sizeRope = 2

p0 = Vec3(-2, 10, 0)
v0 = Vec3(0, 0, 0)
g = 10
m = 1
dt = 0.01
k = 10
attenuation = 0.9

F_g = Vec3(0, -1 * m * g, 0)
a = Vec3(0,0,0)
l = p0.distance(pointAccroche)
res = k * (l - sizeRope)
F_r = res * (pointAccroche - p0)

t = 0 + dt
p_dt = p0
p = p0 + dt * v0
v = v0 + dt * (F_g + F_r) / m

while t < 100:
    x.append(p.x)
    y.append(p.y)

    l = p.distance(pointAccroche)
    res = k * (l - sizeRope)
    F_r = res * (pointAccroche - p)
    a: Vec3 = (F_g + F_r) / m

    # p = p + dt * v
    (p_dt, p) = (p, 2 * p - p_dt + (dt * dt) * a)
    v = (p - p_dt) / dt
    # v = v + dt * a

    t = t + dt

fig, ax = plt.subplots()
scat = ax.scatter(x, y)
ani = animation.FuncAnimation(fig=fig, func=update, frames=len(x), interval=30, repeat=True)
plt.show()
