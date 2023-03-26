#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object3d.hpp"
#include <vecmath.h>
#include <cmath>
#include <iostream>
using namespace std;

// TODO: implement this class and add more fields as necessary,
class Triangle: public Object3D {

public:
	Triangle() = delete;

    // a b c are three vertex positions of the triangle
	Triangle( const Vector3f& a, const Vector3f& b, const Vector3f& c, Material* m) : Object3D(m) {
		vertices[0] = a;
		vertices[1] = b;
		vertices[2] = c;
		auto t1 = b - a, t2 = c - a;
		this -> normal = Vector3f::cross(t1, t2).normalized();
	}

	bool intersect( const Ray& ray,  Hit& hit , float tmin) override {
		/**
		 \brief computer intersection between a triangle and a ray.
		*/
		auto ori = ray.getOrigin();
		auto dir = ray.getDirection();
		auto s = ori - vertices[0];
		auto e1 = vertices[1] - vertices[0];
		auto e2 = vertices[2] - vertices[0];
		auto s1 = Vector3f::cross(dir, e2);
		auto s2 = Vector3f::cross(s, e1);
		auto deno = 1 / (Vector3f::dot(s1, e1));
		auto t = deno * Vector3f::dot(s2, e2);
		auto beta = deno * Vector3f::dot(s1, s);
		auto gamma = deno * Vector3f::dot(s2, dir);
		auto alpha = 1 - beta - gamma;
		bool valid = alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1 && gamma >= 0 && gamma <= 1;
		if (valid && t >= 0 && t < hit.getT() && t > tmin) {
			hit.set(t, this -> material, this -> normal);
			return true;
		} 
		else return false;
	}
	
	Vector3f normal;
	Vector3f vertices[3];
protected:
};

#endif //TRIANGLE_H
