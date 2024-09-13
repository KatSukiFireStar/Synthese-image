import math

class Sphere:
    def __init__(self, radius, center):
        self.radius = radius
        self.center = center

class Rayon:
    def __init__(self, origin, direction):
        self.origin = origin
        self.direction = direction

class Vector3:
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

    def __sub__(self, other):
        return Vector3(self.x - other.x, self.y - other.y, self.z - other.z)

    def __add__(self, other):
        return Vector3(self.x + other.x, self.y + other.y, self.z + other.z)


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
            return t1
        elif t2 >= 0:
            return t2
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