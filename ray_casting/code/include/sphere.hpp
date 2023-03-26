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
        Vector3f l = center - r.getOrigin();
        bool inSphere = Vector3f::dot(l, l) < radius * radius;
        float projPoint = Vector3f::dot(l, r.getDirection()) / r.getDirection().length();
        if (projPoint < 0 && !inSphere) return false;
        float dSquare = Vector3f::dot(l, l) - projPoint * projPoint;
        if (dSquare > radius * radius) return false;
        float tSquare = radius * radius - dSquare;
        float t;
        if (inSphere) t = (projPoint + sqrt(tSquare));
        else t = (projPoint - sqrt(tSquare)); 
        if (t > h.getT() || t < tmin) return false;
        Vector3f normal = r.pointAtParameter(t) - center;
        h.set(t, material, normal.normalized());
        return true;


        //         Vector3f l = center - r.getOrigin();

        // assert(l.length() > this->radius);// ray origin outside sphere
        
        // float t_p = Vector3f::dot(l, r.getDirection())
        //     / r.getDirection().length();

        // if (t_p < 0) return false;// wrong angle

        // float d_square = l.squaredLength() - t_p * t_p;

        // if (d_square >= radius * radius) return false;// wrong distance

        // float t = t_p - sqrt(radius * radius - d_square);
        // if (t < tmin) return false;// impossible t
        // if (t > h.getT()) return false;// farther t

        // Vector3f n(r.pointAtParameter(t) - center);
        // n.normalize();
        // h.set(t, material, n);

        // return true;
    }

protected:
    Vector3f center;
    float radius;
};


#endif
