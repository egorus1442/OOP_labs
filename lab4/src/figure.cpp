// Подключаем заголовочный файл с объявлением класса Figure
#include "figure.h"

// Реализация конструктора копирования для класса Figure
template <Scalar T>
Figure<T>::Figure(const Figure& other) {
    // Резервируем память под вершины, чтобы избежать лишних перевыделений памяти
    vertices.reserve(other.vertices.size());
    // Копируем каждую вершину из другого объекта
    for (const auto& vertex : other.vertices) {
        // Создаем новую уникальную вершину как копию существующей
        vertices.push_back(std::make_unique<Point<T>>(*vertex));
    }
}

// Реализация конструктора перемещения (используется реализация по умолчанию)
template <Scalar T>
Figure<T>::Figure(Figure&& other) noexcept = default;

// Реализация оператора присваивания копированием
template <Scalar T>
Figure<T>& Figure<T>::operator=(const Figure& other) {
    // Проверка на самоприсваивание
    if (this != &other) {
        // Очищаем текущий вектор вершин
        vertices.clear();
        // Резервируем память под новые вершины
        vertices.reserve(other.vertices.size());
        // Копируем каждую вершину из другого объекта
        for (const auto& vertex : other.vertices) {
            vertices.push_back(std::make_unique<Point<T>>(*vertex));
        }
    }
    return *this;
}

// Реализация оператора присваивания перемещением (используется реализация по умолчанию)
template <Scalar T>
Figure<T>& Figure<T>::operator=(Figure&& other) noexcept = default;

// Реализация метода печати фигуры
template <Scalar T>
std::ostream& Figure<T>::print(std::ostream& os) const {
    // Выводим заголовок
    os << "Figure vertices:\n";
    // Выводим каждую вершину фигуры
    for (const auto& vertex : vertices) {
        os << *vertex << "\n";
    }
    return os;
}

// Реализация метода ввода фигуры
template <Scalar T>
std::istream& Figure<T>::input(std::istream& is) {
    // Изменяем размер вектора вершин в соответствии с типом фигуры
    vertices.resize(getVerticesCount());
    // Считываем координаты для каждой вершины
    for (auto& vertex : vertices) {
        // Создаем новую вершину
        vertex = std::make_unique<Point<T>>();
        // Считываем координаты вершины
        is >> *vertex;
    }
    return is;
}

// Явная инстанциация шаблона для различных числовых типов
// Это нужно для того, чтобы компилятор создал код для каждого типа
template class Figure<int>;      // Для целочисленных координат
template class Figure<float>;    // Для координат с плавающей точкой
template class Figure<double>;   // Для координат с двойной точностью