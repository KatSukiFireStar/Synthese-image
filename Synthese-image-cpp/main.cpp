#include <cmath>
#include <iostream>

struct Color {
    float red, green, blue;

    Color(const float red, const float green, const float blue) : red(red), green(green), blue(blue) {}

    static Color white() {
        return Color{255, 255, 255};
    }
};

struct Direction {
    float x, y , z;

    Direction(const float x, const float y, const float z) : x(x), y(y), z(z) {}

    [[nodiscard]] float dot(const Direction d2) const {
        return this->x * d2.x + this->y * d2.y + this->z * d2.z;
    }

    [[nodiscard]] float lenght()const {
        return std::sqrt(this->dot(*this));
    }

    Direction operator/(const float val) const {
        return Direction{this->x / val, this->y / val, this->z / val};
    }

    [[nodiscard]] Direction normalize() const {
        return *this / this->lenght();
    }

    [[nodiscard]] Direction inverse() const {
        return Direction{- this->x, - this->y, - this->z};
    }
};

struct Point {
    float x, y , z;

    Point(const float x, const float y, const float z) : x(x), y(y), z(z) {}

    Point operator+(const Direction d2) const {
        return Point{this->x + d2.x, this->y + d2.y, this->z + d2.z};
    }

    Point operator-(const Direction d2) const {
        return Point{this->x - d2.x, this->y - d2.y, this->z - d2.z};
    }
};

struct Rayon {
    Point origin;
    Direction direction;

    Rayon(const Point origin, const Direction direction) : origin(origin), direction(direction) {}
};

struct Sphere {
    float radius;
    Point center;
    Color albedo;

    Sphere(const float radius, const Point center, const Color albedo) : radius(radius), center(center), albedo(albedo) {}
};

struct Light {
    Point position;
    float intensity;

    Light(const Point position, const float intensity) : position(position), intensity(intensity) {}
};

struct Scene {
    Sphere spheres[];
    Light lights[];

    Scene(const Sphere spheres[], const Light lights[]) : spheres(spheres), lights(lights) {}

    void addSphere(const Sphere sphere) {
        spheres += sphere;
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
