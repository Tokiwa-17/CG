#ifndef MATERIAL_H
#define MATERIAL_H

#include <cassert>
#include <vecmath.h>

#include "ray.hpp"
#include "hit.hpp"
#include <iostream>

// TODO: Implement Shade function that computes Phong introduced in class.
class Material {
public:

    explicit Material(const Vector3f &d_color, const Vector3f &s_color = Vector3f::ZERO, float s = 0) :
            diffuseColor(d_color), specularColor(s_color), shininess(s) {

    }

    virtual ~Material() = default;

    virtual Vector3f getDiffuseColor() const {
        return diffuseColor;
    }

    float clamp(float v) {
        return v ? v >= 0 : 0.0f;
    }

    Vector3f Shade(const Ray &ray, const Hit &hit,
                   const Vector3f &dirToLight, const Vector3f &lightColor) {
        Vector3f shaded = Vector3f::ZERO;
        auto kd = diffuseColor;
        auto ks = specularColor;
        auto V = -ray.getDirection().normalized();
        auto N = hit.getNormal().normalized();
        auto L = dirToLight.normalized();
        auto R = (2 * (Vector3f::dot(N, L) * N) - L).normalized();
        shaded = lightColor * (kd * clamp(Vector3f::dot(L, N)) + ks * pow(clamp(Vector3f::dot(V, R)), shininess));
        return shaded;
    }

protected:
    Vector3f diffuseColor;
    Vector3f specularColor;
    float shininess;
};


#endif // MATERIAL_H
