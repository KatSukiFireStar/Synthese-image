import matplotlib.pyplot as plt
from Vector3 import Vec3

# ATTENTION: PENDANT TOUTES LES SIMULATIONS, LA HAUTEUR SERA
# REPRESENTER PAR L'AXE Z

figure, axis = plt.subplots(2,2, figsize = (10,8))
figure.tight_layout(pad=4)

p0 = Vec3(0, 0, 4000)
v0 = Vec3(200 * 1000 / 3600, 0, 0)

g = 10
m = 80
dt = 0.01
coef = 0.315

F_d = - coef * v0.norm() * v0
F_g = Vec3(0, 0, -1 * m * g)

t = 0 + dt
p_dt = p0
p = p0 + dt * v0
v = v0 + dt * (F_d + F_g) / m

px = list()
pz = list()
pt = list()
pvx = list()
pvz = list()

pz.append(p0.z)
px.append(p0.x)
pt.append(0)
pvx.append(v0.x)
pvz.append(v0.z)

while p.z >= 0.0:
    pz.append(p.z)
    px.append(p.x)
    pt.append(t)
    pvx.append(v.x)
    pvz.append(v.z)

    F_d = - coef * v.norm() * v
    a:Vec3 = (F_d + F_g) / m

    (p_dt, p) = (p, 2 * p - p_dt + (dt * dt) * a)
    # p = p + dt * v
    v = (p - p_dt) / dt
    # v = v + dt * a

    t = t + dt

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
