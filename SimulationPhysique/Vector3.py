import math
import dataclasses

@dataclasses.dataclass
class Vec3:
    x: float
    y: float
    z: float

    def __add__(self, other):
        if type(other) == Vec3:
            return Vec3(self.x + other.x, self.y + other.y, self.z + other.z)
        elif type(other) == float:
            return Vec3(self.x + other, self.y + other, self.z + other)


    def __sub__(self, other):
        return Vec3(self.x - other.x, self.y - other.y, self.z - other.z)

    def __rmul__(self, other:float):
        return Vec3(self.x * other, self.y * other, self.z * other)

    def __truediv__(self, other: float):
        return Vec3(self.x / other, self.y / other, self.z / other)

    def norm(self):
        return math.sqrt(self.x * self.x + self.y * self.y + self.z * self.z)

    def norm_squared(self):
        return self.norm() * self.norm()