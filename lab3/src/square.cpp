#include "square.h"

Figure::Point Square::getCenter() const {
    Figure::Point center;
    center.x = (vertices[0].x + vertices[2].x) / 2.0;
    center.y = (vertices[0].y + vertices[2].y) / 2.0;
    return center;
}

double Square::getArea() const {
    double side = std::sqrt(
        std::pow(vertices[1].x - vertices[0].x, 2) + 
        std::pow(vertices[1].y - vertices[0].y, 2)
    );
    return side * side;
}

Square& Square::operator=(const Square& other) {
    if (this != &other) {
        std::copy(other.vertices, other.vertices + 4, vertices);
    }
    return *this;
}

Square& Square::operator=(Square&& other) noexcept {
    if (this != &other) {
        std::copy(other.vertices, other.vertices + 4, vertices);
    }
    return *this;
}

Figure& Square::operator=(const Figure& other) {
    if (const Square* s = dynamic_cast<const Square*>(&other)) {
        *this = *s;
    }
    return *this;
}

Figure& Square::operator=(Figure&& other) noexcept {
    if (Square* s = dynamic_cast<Square*>(&other)) {
        *this = std::move(*s);
    }
    return *this;
}

bool Square::operator==(const Figure& other) const {
    if (const Square* s = dynamic_cast<const Square*>(&other)) {
        for (int i = 0; i < 4; ++i) {
            if (vertices[i].x != s->vertices[i].x || 
                vertices[i].y != s->vertices[i].y)
                return false;
        }
        return true;
    }
    return false;
}

std::istream& operator>>(std::istream& is, Square& square) {
    for (int i = 0; i < 4; ++i) {
        is >> square.vertices[i].x >> square.vertices[i].y;
    }
    return is;
}

void Square::print(std::ostream& os) const {
    for (int i = 0; i < 4; ++i) {
        os << "(" 
           << vertices[i].x << ", " 
           << vertices[i].y << ")\n";
    }
}