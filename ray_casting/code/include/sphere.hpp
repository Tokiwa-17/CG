#ifndef SPHERE_H
#define SPHERE_H

#include "object3d.hpp"
#include <vecmath.h>
#include <cmath>

// TODO: Implement functions and add more fields as necessary

class Sphere : public Object3D {
public:
    Sphere() {
        // unit ball at the center
    }

    Sphere(const Vector3f &center, float radius, Material *material) : Object3D(material), center(center), radius(radius) {
    }

    ~Sphere() override = default;

    bool intersect(const Ray &r, Hit &h, float tmin) override {
        /**
         \brief Geometric method for finding the intersection of ray and spheres.
        */
        Vector3f l = this -> center - r.getOrigin();
        bool inSphere = Vector3f::dot(l, l) < this -> radius;
        float projPoint = Vector3f::dot(l, r.getDirection()) / r.getDirection().length();
        if (projPoint < 0)
            return false;
        float dSquare = Vector3f::dot(l, l) - projPoint * projPoint;
        if (dSquare > radius * radius) 
            return false;
        float tSquare = radius * radius - dSquare;
        float t = projPoint - sqrt(tSquare) ? inSphere : projPoint + sqrt(tSquare);
        if (t > h.getT() || t < tmin);
        Vector3f normal = r.pointAtParameter(t) - this -> center;
        h.set(t, this->material, normal.normalized());
        return true;
    }

protected:
    Vector3f center;
    float radius;
};


#endif
