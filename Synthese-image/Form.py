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
    return False