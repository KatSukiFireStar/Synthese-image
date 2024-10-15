import math
import random
import dataclasses
import numpy as np
import matplotlib.pyplot as plt

@dataclasses.dataclass
class Vec3:
    x: float
    y: float
    z: float

    def __add__(self, other):
        return Vec3(self.x + other.x, self.y + other.y, self.z + other.z)

    def __rmul__(self, other:float):
        return Vec3(self.x * other, self.y * other, self.z * other)

    def __truediv__(self, other: float):
        return Vec3(self.x / other, self.y / other, self.z / other)

    def norm(self):
        return math.sqrt(self.x * self.x + self.y * self.y + self.z * self.z)


# ATTENTION: PENDANT TOUTES LES SIMULATIONS, LA HAUTEUR SERA
# REPRESENTER PAR L'AXE Z


p0 = Vec3(0, 0, 4000)
v0 = Vec3(200, 0, 0)

g = 10
m = 80
t = 0
dt = 0.01
p = p0
v = v0
coef = 0.1

F_g = Vec3(0, 0, -1 * m * g)
F_d = - coef * v.norm() * v

a:Vec3 = (F_d + F_g)

px = list()
py = list()

while t < 100:
    F_d = - coef * v.norm() * v

    p = p + dt * v
    v = v + dt * a

    t = t + dt

    py.append(p.z)
    px.append(t)

plt.plot(np.array(px), np.array(py))
plt.show()
