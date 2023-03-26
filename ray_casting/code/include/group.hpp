#ifndef GROUP_H
#define GROUP_H


#include "object3d.hpp"
#include "ray.hpp"
#include "hit.hpp"
#include <iostream>
#include <vector>


// TODO: Implement Group - add data structure to store a list of Object*
class Group : public Object3D {

public:

    Group() {
        this -> objNum = 0;
    }

    explicit Group (int num_objects) {
        this -> objNum = num_objects;
    }

    ~Group() override {

    }

    bool intersect(const Ray &r, Hit &h, float tmin) override {
        bool flag = false;
        for (auto obj : objList) {
            if(obj -> intersect(r, h, tmin)) flag = true;
        }
        return flag;
    }

    void addObject(int index, Object3D *obj) {
        objList.push_back(obj);
    }

    int getGroupSize() {
        return objList.size();
    }

private:
    std::vector<Object3D*> objList;
    int objNum = 0;
};

#endif
	
