#include "triangle.h"

Triangle& Triangle::operator=(const Triangle& other) {
    if (this != &other) {
        std::copy(other.vertices, other.vertices + 3, vertices);
    }
    return *this;
}

Triangle& Triangle::operator=(Triangle&& other) noexcept {
    if (this != &other) {
        std::copy(other.vertices, other.vertices + 3, vertices);
    }
    return *this;
}

Figure& Triangle::operator=(const Figure& other) {
    if (const Triangle* t = dynamic_cast<const Triangle*>(&other)) {
        *this = *t;
    }
    return *this;
}

Figure& Triangle::operator=(Figure&& other) noexcept {
    if (Triangle* t = dynamic_cast<Triangle*>(&other)) {
        *this = std::move(*t);
    }
    return *this;
}

Figure::Point Triangle::getCenter() const {
    Figure::Point center;
    center.x = (vertices[0].x + vertices[1].x + vertices[2].x) / 3.0;
    center.y = (vertices[0].y + vertices[1].y + vertices[2].y) / 3.0;
    return center;
}

double Triangle::getArea() const {
    return std::abs((vertices[1].x - vertices[0].x) * (vertices[2].y - vertices[0].y) -
                   (vertices[2].x - vertices[0].x) * (vertices[1].y - vertices[0].y)) / 2.0;
}

bool Triangle::operator==(const Figure& other) const {
    if (const Triangle* t = dynamic_cast<const Triangle*>(&other)) {
        for (int i = 0; i < 3; ++i) {
            if (vertices[i].x != t->vertices[i].x || 
                vertices[i].y != t->vertices[i].y)
                return false;
        }
        return true;
    }
    return false;
}

std::istream& operator>>(std::istream& is, Triangle& triangle) {
    for (int i = 0; i < 3; ++i) {
        is >> triangle.vertices[i].x >> triangle.vertices[i].y;
    }
    return is;
}

void Triangle::print(std::ostream& os) const {
    for (int i = 0; i < 3; ++i) {
        os << "(" 
           << vertices[i].x << ", " 
           << vertices[i].y << ")\n";
    }
}