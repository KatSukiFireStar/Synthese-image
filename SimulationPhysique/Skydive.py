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

    def norm_squared(self):
        return self.norm() * self.norm()

# ATTENTION: PENDANT TOUTES LES SIMULATIONS, LA HAUTEUR SERA
# REPRESENTER PAR L'AXE Z

figure, axis = plt.subplots(2,2, figsize = (10,8))
figure.tight_layout(pad=4)

p0 = Vec3(0, 0, 4000)
v0 = Vec3(200 * 1000 / 3600, 0, 0)

g = 10
m = 80
t = 0
dt = 0.01
p = p0
v = v0
coef = 0.315

F_g = Vec3(0, 0, -1 * m * g)

px = list()
pz = list()
pt = list()
pvx = list()
pvz = list()

while p.z >= 0.0:
    pz.append(p.z)
    px.append(p.x)
    pt.append(t)
    pvx.append(v.x)
    pvz.append(v.z)

    F_d = - coef * v.norm() * v
    a:Vec3 = (F_d + F_g) / m

    p = p + dt * v
    v = v + dt * a

    t = t + dt

    print("Vitesse", v)
    print("Acceleration", a)
    print("Coef", coef)

axis[0, 0].plot(pt, pz, 'red')
axis[0, 0].set_xlabel('Temps')
axis[0, 0].set_ylabel('Hauteur')
axis[0, 0].set_title("Hauteur en fonction du temps")

axis[0, 1].plot(pt, px, 'red')
axis[0, 1].set_xlabel('Temps')
axis[0, 1].set_ylabel('Position X')
axis[0, 1].set_title("Position X en fonction du temps")

axis[1, 0].plot(pt, pvx, 'red')
axis[1, 0].set_xlabel('Temps')
axis[1, 0].set_ylabel('Vitesse X')
axis[1, 0].set_title("Vitesse X en fonction du temps")

axis[1, 1].plot(pt, pvz, 'red')
axis[1, 1].set_xlabel('Temps')
axis[1, 1].set_ylabel('Vitesse Z')
axis[1, 1].set_title("Vitesse Z en fonction du temps")

plt.show()
