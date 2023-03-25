#pragma once

#include <image.hpp>
#include <algorithm>
#include <queue>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <utility>

class Element {
public:
    virtual void draw(Image &img) = 0;
    virtual ~Element() = default;
};

class Line : public Element {

public:
    int xA, yA;
    int xB, yB;
    Vector3f color;
    void draw(Image &img) override {
        // TODO: Implement Bresenham Algorithm
        printf("Draw a line from (%d, %d) to (%d, %d) using color (%f, %f, %f)\n", xA, yA, xB, yB,
                color.x(), color.y(), color.z());
        // handle situations where slope > 1.
        auto steep = abs(yB - yA) > abs(xB - xA);
        if (steep) {
            std::swap(xA, yA);
            std::swap(xB, yB);
        }
        // handle situations where the line is of negative direction.
        if (xA > xB) {
            std::swap(xA, xB);
            std::swap(yA, yB);
        }
        auto deltax = xB - xA, deltay = abs(yB - yA);
        float err = 0.0f, deltaErr = static_cast<float>(deltay) / static_cast<float>(deltax);
        auto y = yA;
        auto yStep = yB > yA ? 1 : -1;
        for (auto x = xA; x <= xB; x++) {
            if (steep) {
                img.SetPixel(y, x, color);
            } else {
                img.SetPixel(x, y, color);
            }
            err += deltaErr;
            if (abs(err) >= 0.5) {
                y += yStep;
                err -= 1.0f;
            }
        }
    }
};

class Circle : public Element {

public:
    int cx, cy;
    int radius;
    Vector3f color;
    void draw(Image &img) override {
        // TODO: Implement Algorithm to draw a Circle
        printf("Draw a circle with center (%d, %d) and radius %d using color (%f, %f, %f)\n", cx, cy, radius,
               color.x(), color.y(), color.z());
        // draw 1/8 circle
        auto x = 0, y = radius;
        auto d = 1.25 - radius;
        int rightBound = std::ceil(static_cast<float>(radius) / sqrt(2));
        for (; x <= rightBound;) {
            img.SetPixel(x + cx, y + cy, color);
            img.SetPixel(x + cx, -y + cy, color);
            img.SetPixel(-x + cx, y + cy, color);
            img.SetPixel(-x + cx, -y + cy, color);
            img.SetPixel(y + cx, x + cy, color);
            img.SetPixel(y + cx, -x + cy, color);
            img.SetPixel(-y + cx, x + cy, color);
            img.SetPixel(-y + cx, -x + cy, color);
            if (d < 0) {
                d = d + 2 * x + 3;
                x += 1;
            } else {
                d = d + 2 * x - 2 * y + 5;
                x += 1, y -= 1;
            }
        }
    }
};

class Fill : public Element {

public:
    int cx, cy;
    Vector3f color;
    void draw(Image &img) override {
        // TODO: Flood fill
        printf("Flood fill source point = (%d, %d) using color (%f, %f, %f)\n", cx, cy,
                color.x(), color.y(), color.z());
        std::queue<std::pair<int, int>> q;
        q.push(std::make_pair(cx, cy));
        Vector3f originColor = img.GetPixel(cx, cy);
        while(!q.empty()) {
            auto pos = q.front();
            auto tx = pos.first, ty = pos.second;
            q.pop();
            if (tx < 0 || tx >= img.Width() || ty < 0 || ty >= img.Height() || img.GetPixel(pos.first, pos.second) != originColor) 
                continue;
            img.SetPixel(tx, ty, color);
            q.push(std::make_pair(tx - 1, ty));
            q.push(std::make_pair(tx + 1, ty));
            q.push(std::make_pair(tx, ty - 1));
            q.push(std::make_pair(tx, ty + 1));
        }
    }
};