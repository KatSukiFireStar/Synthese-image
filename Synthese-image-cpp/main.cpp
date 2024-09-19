#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Color {
    float red, green, blue;

    Color(const float red, const float green, const float blue) : red(red), green(green), blue(blue) {}

    Color() : red(0), green(0), blue(0) {}

    static Color white() {
        return Color{255, 255, 255};
    }

    static Color black() {
        return Color{0, 0, 0};
    }
};

struct Direction {
    float x, y , z;

    Direction(const float x, const float y, const float z) : x(x), y(y), z(z) {}

    [[nodiscard]] float dot(const Direction d2) const {
        return this->x * d2.x + this->y * d2.y + this->z * d2.z;
    }

    [[nodiscard]] float lenght()const {
        return sqrt(this->dot(*this));
    }

    [[nodiscard]] float lenght_squared()const {
        return this->dot(*this);
    }

    Direction operator/(const float val) const {
        return Direction{this->x / val, this->y / val, this->z / val};
    }

    [[nodiscard]] Direction normalize() const {
        const float len = this->lenght();
        return Direction{this->x / len, this->y / len, this->z / len};
    }

    [[nodiscard]] Direction inverse() const {
        return Direction{- this->x, - this->y, - this->z};
    }

    Direction operator*(const float val) const {
        return Direction{this->x * val, this->y * val, this->z * val};
    }

    Direction operator+(const Direction d2) const {
        return Direction{this->x + d2.x, this->y + d2.y, this->z + d2.z};
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

    Direction operator-(const Point p2) const {
        return Direction{this->x - p2.x, this->y - p2.y, this->z - p2.z};
    }
};

struct Rayon {
    Point origin;
    Direction direction;

    Rayon(const Point origin, const Direction direction) : origin(origin), direction(direction) {}

    [[nodiscard]] float getIntersectionDistance(const float t) const {
        return this->direction.lenght() * t;
    }
};

struct Sphere {
    float radius;
    Point center;
    Color albedo;

    Sphere(const float radius, const Point center, const Color albedo) : radius(radius), center(center), albedo(albedo) {}
};

struct Light {
    Point position;
    Color intensity;

    Light(const Point position, const Color intensity) : position(position), intensity(intensity) {}
};

struct Scene {
    vector<Sphere> spheres;
    vector<Light> lights;

    Scene(const vector<Sphere>& spheres, const vector<Light>& lights) : spheres(spheres), lights(lights) {}

    Scene() : spheres(), lights(){}

    void addSphere(const Sphere &sphere) {
        spheres.push_back(sphere);
    }

    void addLight(const Light &light) {
        lights.push_back(light);
    }
};

struct Intersection {
    bool isIntersection;
    float distance;
    Point intersection;
    Sphere sphere;

    Intersection(const bool isIntersection, const float distance, const Point intersection, const Sphere &sphere) : isIntersection(isIntersection), distance(distance), intersection(intersection), sphere(sphere) {}

    Intersection() : isIntersection(false), distance(0), intersection(Point{0,0,0}), sphere(Sphere(0, Point{0,0,0}, Color::white())) {}
};

Intersection intersectSphere(const Rayon &ray, const vector<Sphere> &spheres) {
    vector<Intersection> intersections;
    for (Sphere sphere : spheres){
        Direction oc = ray.origin - sphere.center;

        float a = ray.direction.lenght_squared();
        float b = 2 * oc.dot(ray.direction);
        float c = oc.lenght_squared() - (sphere.radius * sphere.radius);

        float delta = b * b - 4 * a * c;

        if (delta >= 0) {
            float t1 = (-b - sqrt(delta)) / (2 * a);
            float t2 = (-b + sqrt(delta)) / (2 * a);
            if (t1 >= 0){
                intersections.push_back(Intersection{true, t1, ray.origin + ray.direction * t1, sphere});
            }else if (t2 >= 0) {

                intersections.push_back(Intersection{true, t2, ray.origin + ray.direction * t2, sphere});
            }
        }
    }
    if (intersections.empty()) {
        return {};
    }
    int min = INT_MAX;
    Intersection minIntersection = Intersection();
    for (Intersection intersection : intersections) {
        if (ray.getIntersectionDistance(intersection.distance) < min) {
            min = ray.getIntersectionDistance(intersection.distance);
            minIntersection = intersection;
        }
    }
    return minIntersection;
}

float sq(const float val) {
    return val * val;
}

int main() {
    // imagePink();

    float width = 800;
    float height = 600;

    string fullPath = "../raycastImage.ppm";
    ofstream fileOut;
    fileOut.open(fullPath.c_str());
    fileOut << "P3" << endl << width << " " << height << endl << "255" << endl;

    int focal = 10000;

    Scene scene = Scene();

    Sphere sphere = Sphere(180, Point{0,0,200}, Color{0,0,1});
    scene.addSphere(sphere);
    Light lampe = Light(Point{300, -200, 200}, Color{100000, 100000, 100000});
    scene.addLight(lampe);
    Light lampe2 = Light(Point{0, -500, 200}, Color{100000, 0, 0});
    scene.addLight(lampe2);

    Sphere sol = Sphere(10000, Point{0,10400,-1000}, Color{1,1,1});
    scene.addSphere(sol);

    Sphere sphere2 = Sphere(180, Point{-200,-400,200}, Color{1,1,1});
    scene.addSphere(sphere2);

    for (int y = 0; static_cast<float>(y) < height; y++) {
        for (int x = 0; static_cast<float>(x) < width; x++) {
            Point pixel = Point(x * 2 - width , y * 2 - height, 0);
            Point origin = Point(0,0, -focal);
            Direction direction = pixel - origin;

            Rayon rayon = Rayon(pixel, direction);
            Intersection it = intersectSphere(rayon, scene.spheres);

            if (it.isIntersection) {
                Sphere sph = it.sphere;
                Color col = Color();
                Direction N = it.intersection - sph.center;
                Direction norm = N.normalize();

                for (Light light : scene.lights) {
                    Rayon rayonLampe = Rayon(it.intersection + (norm / 100), light.position - it.intersection + (norm / 100));

                    Direction l_i = rayonLampe.direction.inverse();
                    Color sphereAlbedo = sph.albedo;

                    Intersection it2 = intersectSphere(rayonLampe, scene.spheres);
                    if (!it2.isIntersection) {
                        float v = abs(norm.dot(l_i));
                        float len_l = rayonLampe.direction.lenght_squared();

                        col.red += light.intensity.red / len_l * sphereAlbedo.red * v;
                        col.green += light.intensity.green / len_l * sphereAlbedo.green * v;
                        col.blue += light.intensity.blue / len_l * sphereAlbedo.blue * v;
                    }else {
                        float len_l = rayonLampe.direction.lenght();
                        if (len_l < rayonLampe.getIntersectionDistance(it2.distance)) {
                            float v = abs(norm.dot(l_i));

                            col.red += light.intensity.red / sq(len_l) * sphereAlbedo.red * v;
                            col.green += light.intensity.green / sq(len_l) * sphereAlbedo.green * v;
                            col.blue += light.intensity.blue / sq(len_l) * sphereAlbedo.blue * v;
                        }
                    }

                    if (col.red > 255) {
                        col.red = 255;
                    }
                    if (col.blue > 255) {
                        col.blue = 255;
                    }
                    if (col.green > 255) {
                        col.green = 255;
                    }
                }
                fileOut << static_cast<int>(col.red) << " " << static_cast<int>(col.green) << " " << static_cast<int>(col.blue) << endl;
            }else {
                fileOut << "0 0 0" << endl;
            }
        }
        fileOut << endl;
    }

    return 0;
}
