#include <algorithm>
#include <cmath>
#include <float.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <optional>
#include <memory>
#include <bits/ranges_algo.h>

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

    [[nodiscard]] float length()const {
        return sqrt(this->dot(*this));
    }

    [[nodiscard]] float length_squared()const {
        return this->dot(*this);
    }

    Direction operator/(const float val) const {
        return Direction{this->x / val, this->y / val, this->z / val};
    }

    [[nodiscard]] Direction normalize() const {
        const float len = this->length();
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

    Direction operator-(const Direction d2) const {
        return Direction{this->x - d2.x, this->y - d2.y, this->z - d2.z};
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

    Point center(const Point p2) {
        return Point{(this->x + p2.x) / 2, (this->y + p2.y) / 2, (this->z + p2.z) / 2};
    }

    [[nodiscard]] Point min(const Point p2) const {
        return Point{std::min(this->x, p2.x), std::min(this->y, p2.y), std::min(this->z, p2.z)};
    }

    [[nodiscard]] Point max(const Point p2) const {
        return Point{std::max(this->x, p2.x), std::max(this->y, p2.y), std::max(this->z, p2.z)};
    }
};

struct Rayon {
    Point origin;
    Direction direction;

    Rayon(const Point origin, const Direction direction) : origin(origin), direction(direction) {}

    [[nodiscard]] float getIntersectionDistance(const float t) const {
        return this->direction.length() * t;
    }
};

struct Sphere {
    float radius;
    Point center;
    Color albedo;

    Sphere(const float radius, const Point center, const Color albedo) : radius(radius), center(center), albedo(albedo) {}
};

void swap(Sphere &a, Sphere &b) {
    using std::swap;
    swap(a.radius, b.radius);
    swap(a.center, b.center);
    swap(a.albedo, b.albedo);
}

struct Light {
    Point position;
    Color intensity;

    Light(const Point position, const Color intensity) : position(position), intensity(intensity) {}
};

enum Axis{
    X,Y,Z
};

struct BoundingBox {
    Point pointMin;
    Point pointMax;

    BoundingBox(const Point pointMin, const Point pointMax) : pointMin(pointMin), pointMax(pointMax) {}
    BoundingBox() : pointMin(Point{0,0,0}), pointMax(Point{0,0,0}) {}

    [[nodiscard]] BoundingBox unionBox(const BoundingBox other) const{
        return BoundingBox{this->pointMin.min(other.pointMin), this->pointMax.max(other.pointMax)};
    }

    [[nodiscard]] Axis largestAxis() const {
        Direction axis = this->pointMax - this->pointMin;
        if (axis.x >= axis.y && axis.x >= axis.z) {
            return X;
        }
        if (axis.y >= axis.z) {
            return Y;
        }
        return Z;
    }
};

struct ObjectHierarchy {
    bool isLeaf = true;
    BoundingBox boundingBox;
    vector<Sphere> spheres;

    ObjectHierarchy* leftTree;
    bool hasLeftTree;
    ObjectHierarchy* rightTree;
    bool hasRightTree;

    ObjectHierarchy(const BoundingBox &bounding_box, const vector<Sphere> &spheres) : boundingBox(bounding_box), spheres(spheres), leftTree(), hasLeftTree(false), rightTree(), hasRightTree(false) {}
    ObjectHierarchy() : boundingBox(), spheres(), leftTree(), hasLeftTree(false), rightTree(), hasRightTree(false) {}
    ObjectHierarchy(const BoundingBox &bounding_box, ObjectHierarchy* leftTree, ObjectHierarchy* rightTree) : isLeaf(false), boundingBox(bounding_box), spheres(), leftTree(leftTree), hasLeftTree(true), rightTree(rightTree), hasRightTree(true) {}
};

struct Scene {
    ObjectHierarchy hierarchy;
    vector<Light> lights;

    Scene(const ObjectHierarchy hierarchy, const vector<Light>& lights) : hierarchy(hierarchy), lights(lights) {}

    Scene() : hierarchy(), lights(){}

    void addLight(const Light &light) {
        lights.push_back(light);
    }
};

BoundingBox sphereToBoundingBox(const Sphere &sphere) {
    Point r = Point{sphere.radius, sphere.radius, sphere.radius};
    Point pointMin = Point{sphere.center.x - r.x,sphere.center.y - r.y,sphere.center.z - r.z};
    Point pointMax = Point{sphere.center.x + r.x,sphere.center.y + r.y,sphere.center.z + r.z};
    return BoundingBox{pointMin, pointMax};
}

bool compareSphereX(Sphere &s1, Sphere &s2) {
    return s1.center.x < s2.center.x;
}

bool compareSphereY(Sphere &s1, Sphere &s2) {
    return s1.center.y < s2.center.y;
}

bool compareSphereZ(Sphere &s1, Sphere &s2) {
    return s1.center.z < s2.center.z;
}

ObjectHierarchy buildHierarchy(const vector<Sphere>& spheres) {
    BoundingBox boundingBox = sphereToBoundingBox(spheres[0]);
    for (Sphere sphere : spheres) {
        boundingBox = boundingBox.unionBox(sphereToBoundingBox(sphere));
    }
    if (spheres.size() < 10) {
        return ObjectHierarchy{boundingBox, spheres};
    }
    // switch (boundingBox.largestAxis()) {
    //     case X:
    //         sort(spheres.begin(), spheres.end(), compareSphereX);
    //         break;
    //     case Y:
    //         sort(spheres.begin(), spheres.end(), compareSphereY);
    //         break;
    //     case Z:
    //         sort(spheres.begin(), spheres.end(), compareSphereZ);
    //         break;
    //     default:
    //         break;
    // }

    vector<Sphere> leftSpheres;
    vector<Sphere> rightSpheres;
    int cut = spheres.size() / 2;
    int len = spheres.size();

    for (int i = 0; i < cut; i++) {
        leftSpheres.push_back(spheres[i]);
    }
    for (int i = cut; i < len; i++) {
        rightSpheres.push_back(spheres[i]);
    }

    ObjectHierarchy leftTree = buildHierarchy(leftSpheres);
    ObjectHierarchy rightTree = buildHierarchy(rightSpheres);

    return ObjectHierarchy{boundingBox, (&leftTree), (&rightTree)};
}

struct IntersectionSphere {
    bool isIntersection;
    float distance;
    Point intersection;
    Sphere sphere;

    IntersectionSphere(const bool isIntersection, const float distance, const Point intersection, const Sphere &sphere) : isIntersection(isIntersection), distance(distance), intersection(intersection), sphere(sphere) {}

    IntersectionSphere() : isIntersection(false), distance(0), intersection(Point{0,0,0}), sphere(Sphere(0, Point{0,0,0}, Color::white())) {}
};

IntersectionSphere intersectSphere(const Rayon &ray, const vector<Sphere> spheres) {
    vector<IntersectionSphere> intersections;
    for (Sphere sphere : spheres){
        Direction oc = ray.origin - sphere.center;

        float a = ray.direction.length_squared();
        float b = 2 * oc.dot(ray.direction);
        float c = oc.length_squared() - (sphere.radius * sphere.radius);

        float delta = b * b - 4 * a * c;

        if (delta >= 0) {
            float t1 = (-b - sqrt(delta)) / (2 * a);
            float t2 = (-b + sqrt(delta)) / (2 * a);
            if (t1 >= 0){
                intersections.push_back(IntersectionSphere{true, t1, ray.origin + ray.direction * t1, sphere});
            }else if (t2 >= 0) {

                intersections.push_back(IntersectionSphere{true, t2, ray.origin + ray.direction * t2, sphere});
            }
        }
    }
    if (intersections.empty()) {
        return {};
    }
    float min = FLT_MAX;
    IntersectionSphere minIntersection = IntersectionSphere();
    for (IntersectionSphere intersection : intersections) {
        if (float l = ray.getIntersectionDistance(intersection.distance); l < min) {
            min = l;
            minIntersection = intersection;
        }
    }
    return minIntersection;
}

struct IntersectionBox {
    bool isIntersection;
    float distance;

    explicit IntersectionBox(const float distance) : isIntersection(true), distance(distance) {}
    IntersectionBox() : isIntersection(false), distance(0) {}
};

IntersectionBox intersectCube(const Rayon &ray, const BoundingBox &box) {
    float rinvx = 1.0 / ray.direction.x;
    float rinvy = 1.0 / ray.direction.y;
    float rinvz = 1.0 / ray.direction.z;

    float tx1 = (box.pointMin.x - ray.origin.x) * rinvx;
    float tx2 = (box.pointMax.x - ray.origin.x) * rinvx;

    float tmin = min(tx1, tx2);
    float tmax = max(tx1, tx2);

    float ty1 = (box.pointMin.y - ray.origin.y) * rinvy;
    float ty2 = (box.pointMax.y - ray.origin.y) * rinvy;

    float tminp = max(tmin, min(ty1, ty2));
    float tmaxp = min(tmax, max(ty1, ty2));

    float tz1 = (box.pointMin.z - ray.origin.z) * rinvz;
    float tz2 = (box.pointMax.z - ray.origin.z) * rinvz;

    float tminpp = min(tminp, min(tz1, tz2));
    float tmaxpp = max(tmaxp, max(tz1, tz2));

    if (tmaxpp < tminpp) {
        return IntersectionBox{};
    }

    return IntersectionBox{tminpp};
}

IntersectionSphere intersectObject(const Rayon &ray, const ObjectHierarchy &hierarchy) {
    if (hierarchy.isLeaf) {
        IntersectionBox it = intersectCube(ray, hierarchy.boundingBox);
        if (it.isIntersection) {
            return intersectSphere(ray, hierarchy.spheres);
        }
        return {};
    }
    IntersectionBox it = intersectCube(ray, hierarchy.boundingBox);
    if (!it.isIntersection) {
        return {};
    }
    IntersectionSphere it_left = intersectObject(ray, *hierarchy.leftTree);
    IntersectionSphere it_right = intersectObject(ray, *hierarchy.rightTree);

    if (!it_left.isIntersection) {
        return it_right;
    }
    if (!it_right.isIntersection) {
        return it_left;
    }

    if (it_left.distance < it_right.distance) {
        return it_left;
    }
    return it_right;

}


float sq(const float val) {
    return val * val;
}

int main() {
    clock_t begin = clock();

    float width = 800;
    float height = 600;

    string fullPath = "../raycastImage2.ppm";
    ofstream fileOut;
    fileOut.open(fullPath.c_str());
    fileOut << "P3" << endl << width << " " << height << endl << "255" << endl;

    int focal = 10000;

    Scene scene = Scene();
    vector<Sphere> spheres;

    // Sphere sphere = Sphere(180, Point{0,0,200}, Color{0,0,1});
    // spheres.push_back(sphere);
    // Sphere sphere2 = Sphere(180, Point{-200,-400,200}, Color{1,1,1});
    // spheres.push_back(sphere2);

    int n = 2;
    float d = 300 / n;
    float radius = 80 / n;

    for (int i = -n; i < n; i++) {
        for (int j = -n; j < n; j++) {
            for (int k = -n; k < n; k++) {
                spheres.emplace_back(radius, Point{i * d, j * d, 200 + k * d}, Color::white());
            }
        }
    }

    cout << "Nb spheres: " << spheres.size() << endl;

    Light lampe = Light(Point{300, -200, 200}, Color{100000, 100000, 100000});
    scene.addLight(lampe);
    Light lampe2 = Light(Point{0, -500, 200}, Color{100000, 0, 0});
    scene.addLight(lampe2);

    // Sphere sol = Sphere(10000, Point{0,10400,-1000}, Color{1,1,1});
    // scene.addSphere(sol);

    ObjectHierarchy objectHierarchy = buildHierarchy(spheres);
    scene.hierarchy = objectHierarchy;


    for (int y = 0; static_cast<float>(y) < height; y++) {
        for (int x = 0; static_cast<float>(x) < width; x++) {
            Point pixel = Point(x * 2 - width , y * 2 - height, 0);
            Point origin = Point(0,0, -focal);
            Direction direction = pixel - origin;

            Rayon rayon = Rayon(pixel, direction);

            // IntersectionSphere it = intersectSphere(rayon, scene.hierarchy.spheres);

            IntersectionSphere it = intersectObject(rayon, scene.hierarchy);

            if (it.isIntersection) {
                Sphere sph = it.sphere;
                Color col = Color();
                Direction N = it.intersection - sph.center;
                Direction norm = N.normalize();

                for (Light light : scene.lights) {
                    Rayon rayonLampe = Rayon(it.intersection + (norm / 100), light.position - it.intersection + (norm / 100));

                    Direction l_i = rayonLampe.direction.inverse();
                    Color sphereAlbedo = sph.albedo;

                    IntersectionSphere it2 = intersectObject(rayonLampe, scene.hierarchy);
                    if (!it2.isIntersection) {
                        float v = abs(norm.dot(l_i));
                        float len_l = rayonLampe.direction.length_squared();

                        col.red += light.intensity.red / len_l * sphereAlbedo.red * v;
                        col.green += light.intensity.green / len_l * sphereAlbedo.green * v;
                        col.blue += light.intensity.blue / len_l * sphereAlbedo.blue * v;
                    }else {
                        float len_l = rayonLampe.direction.length();
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
            }
            // else if(inter.isIntersection) {
            //     fileOut << 255 * inter.box.albedo.red << " " << 255 * inter.box.albedo.green << " " << 255 * inter.box.albedo.blue << endl;
            // }
            else{
                fileOut << "250 180 0" << endl;
            }
        }
        fileOut << endl;
    }
    cout << static_cast<float>(clock() - begin)/CLOCKS_PER_SEC << " seconds" << endl;
    return 0;
}
