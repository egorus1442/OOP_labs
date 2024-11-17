#pragma once
#include "figure.h"

// см octagon.h
template <Scalar T>
class Square : public Figure<T> {
public:
    Square() {
        this->vertices.resize(4);
        for (auto& vertex : this->vertices) {
            vertex = std::make_unique<Point<T>>();
        }
    }

    size_t getVerticesCount() const override { return 4; }
    Point<T> getGeometricCenter() const override;
    double getArea() const override;
}; 