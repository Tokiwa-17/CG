#ifndef CAMERA_H
#define CAMERA_H

#include "ray.hpp"
#include <vecmath.h>
#include <float.h>
#include <cmath>


class Camera {
public:
    Camera(const Vector3f &center, const Vector3f &direction, const Vector3f &up, int imgW, int imgH) {
        this->center = center;
        this->direction = direction.normalized();
        this->horizontal = Vector3f::cross(this->direction, up).normalized();
        this->up = Vector3f::cross(this->horizontal, this->direction);
        this->width = imgW;
        this->height = imgH;
    }

    // Generate rays for each screen-space coordinate
    virtual Ray generateRay(const Vector2f &point) = 0;
    virtual ~Camera() = default;

    int getWidth() const { return width; }
    int getHeight() const { return height; }

protected:
    // Extrinsic parameters
    Vector3f center;
    Vector3f direction;
    Vector3f up;
    Vector3f horizontal;
    // Intrinsic parameters
    int width;
    int height;
};

// TODO: Implement Perspective camera
// You can add new functions or variables whenever needed.
class PerspectiveCamera : public Camera {

public:
    PerspectiveCamera(const Vector3f &center, const Vector3f &direction,
            const Vector3f &up, int imgW, int imgH, float angle) : Camera(center, direction, up, imgW, imgH) {
        // angle is in radian.
        this -> angle = angle;
        c.x() = imgW / 2;
        c.y() = imgH / 2;
        f.x() = width / 2 / tan(angle / 2);
        f.y() = height / 2 / tan(angle / 2);
    }

    Ray generateRay(const Vector2f &point) override {
        // 
        Vector3f dir((point.x() - c.x()) / f.x(), (c.y() - point.y()) / f.y(), 1);
        dir.normalize();
        auto R = Matrix3f(horizontal, -up, direction);
        return Ray(center, R * dir);
    }
    Vector2f c;
    Vector2f f;
    float angle;
};

#endif //CAMERA_H
