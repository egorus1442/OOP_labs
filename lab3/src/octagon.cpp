#include "octagon.h"

Figure::Point Octagon::getCenter() const {
    Figure::Point center = {0, 0};
    for (int i = 0; i < 8; ++i) {
        center.x += vertices[i].x;
        center.y += vertices[i].y;
    }
    center.x /= 8.0;
    center.y /= 8.0;
    return center;
}

double Octagon::getArea() const {
    double area = 0;
    for (int i = 0; i < 8; ++i) {
        int j = (i + 1) % 8;
        area += vertices[i].x * vertices[j].y;
        area -= vertices[j].x * vertices[i].y;
    }
    return std::abs(area) / 2.0;
}

Octagon& Octagon::operator=(const Octagon& other) {
    if (this != &other) {
        std::copy(other.vertices, other.vertices + 8, vertices);
    }
    return *this;
}

Octagon& Octagon::operator=(Octagon&& other) noexcept {
    if (this != &other) {
        std::copy(other.vertices, other.vertices + 8, vertices);
    }
    return *this;
}

Figure& Octagon::operator=(const Figure& other) {
    if (const Octagon* o = dynamic_cast<const Octagon*>(&other)) {
        *this = *o;
    }
    return *this;
}

Figure& Octagon::operator=(Figure&& other) noexcept {
    if (Octagon* o = dynamic_cast<Octagon*>(&other)) {
        *this = std::move(*o);
    }
    return *this;
}

bool Octagon::operator==(const Figure& other) const {
    if (const Octagon* o = dynamic_cast<const Octagon*>(&other)) {
        for (int i = 0; i < 8; ++i) {
            if (vertices[i].x != o->vertices[i].x || 
                vertices[i].y != o->vertices[i].y)
                return false;
        }
        return true;
    }
    return false;
}

std::istream& operator>>(std::istream& is, Octagon& octagon) {
    for (int i = 0; i < 8; ++i) {
        is >> octagon.vertices[i].x >> octagon.vertices[i].y;
    }
    return is;
}

void Octagon::print(std::ostream& os) const {
    for (int i = 0; i < 8; ++i) {
        os << "(" 
           << vertices[i].x << ", " 
           << vertices[i].y << ")\n";
    }
}