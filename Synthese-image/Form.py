import math

class Vector3:
    def __init__(self, x:int, y:int, z:int):
        self.x = x
        self.y = y
        self.z = z

    def __sub__(self, other):
        return Vector3(self.x - other.x, self.y - other.y, self.z - other.z)

    def __add__(self, other):
        return Vector3(self.x + other.x, self.y + other.y, self.z + other.z)

    def __mul__(self, other:(float, int)):
        return Vector3(self.x * other, self.y * other, self.z * other)

    def __truediv__(self, other:(float, int)):
        return Vector3(self.x / other, self.y / other, self.z / other)

class Sphere:
    def __init__(self, radius:int, center:Vector3):
        self.radius = radius
        self.center = center

class Rayon:
    def __init__(self, origin:Vector3, direction:Vector3):
        self.origin = origin
        self.direction = direction

class Lampe:
    def __init__(self, position:Vector3, intensity:float):
        self.position = position
        self.intensity = intensity

class Scene:
    def __init__(self, spheres:list[Sphere], lampes:list[Lampe]):
        self.spheres = spheres
        self.lampes = lampes

def intersectSphere(rayon, sphere):
    oc = rayon.origin - sphere.center

    a = length(rayon.direction)**2
    b = 2 * dot(oc, rayon.direction)
    c = length(oc)**2 - sphere.radius**2

    delta = b**2 - 4 * a * c
    if delta >= 0:
        t1 = (-b - math.sqrt(delta)) / (2 * a)
        t2 = (-b + math.sqrt(delta)) / (2 * a)
        if t1 >= 0:
            inter = rayon.origin + rayon.direction * t1
            return t1, inter
        elif t2 >= 0:
            inter = rayon.origin + rayon.direction * t2
            return t2, inter
        else:
            return None
    else:
        return None

def getIntersectionDistance(rayon, t):
    return t * length(rayon.direction)

def length(vector):
    return math.sqrt(vector.x**2 + vector.y**2 + vector.z**2)

def dot(vector1, vector2):
    return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z

def normalize(vector):
    return vector / length(vector)