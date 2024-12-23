# удалить комменты:
1. ctrl+h
2. включить режим Regex
3. ввести `(^[ ]*?\/\/.*?\n|\/\/.*(?=\n))`
4. replace all на пустую строку
5. профит

# Подробный разбор реализации класса Thirteen

## 1. Правило пяти (Rule of Five)

Правило пяти в C++ гласит, что если класс определяет хотя бы одну из следующих функций, он должен явно определить все пять:

1. Деструктор
2. Конструктор копирования
3. Оператор присваивания копированием
4. Конструктор перемещения
5. Оператор присваивания перемещением

Это правило важно для классов, управляющих ресурсами (например, динамической памятью).

### Пример в нашем коде:

```
// Деструктор
virtual ~Thirteen() noexcept;

// Конструктор копирования
Thirteen(const Thirteen& other);

// Оператор присваивания копированием
Thirteen& operator=(const Thirteen& other);

// Конструктор перемещения
Thirteen(Thirteen&& other) noexcept;

// Оператор присваивания перемещением
Thirteen& operator=(Thirteen&& other) noexcept;
```

## 2. Конструктор копирования vs Конструктор перемещения

### Конструктор копирования:
- Создает новую копию объекта
- Выделяет новую память
- Копирует все данные
- Исходный объект остается неизменным
- Используется при передаче по значению или явном копировании

Пример:
```
Thirteen::Thirteen(const Thirteen& other) {
    size = other.size;
    digits = new unsigned char[size];
    std::copy(other.digits, other.digits + size, digits);
}
```

### Конструктор перемещения:
- Перемещает ресурсы из одного объекта в другой
- Не выделяет новую память
- Забирает указатель на данные
- Исходный объект становится пустым
- Используется с временными объектами или std::move

Пример:
```
Thirteen::Thirteen(Thirteen&& other) noexcept {
    size = other.size;
    digits = other.digits;
    other.digits = nullptr;
    other.size = 0;
}
```

## 3. Управление памятью

### new и delete
- `new` выделяет память в куче (heap)
- `delete` освобождает память для одиночного объекта
- `delete[]` освобождает память для массива объектов

Почему `delete[]`:
- При выделении массива через `new[]`, компилятор сохраняет размер массива
- `delete[]` использует этот размер для правильного освобождения памяти
- Использование простого `delete` приведет к утечке памяти

### Поля класса
```
private:
unsigned char digits; // указатель на динамический массив
size_t size; // размер массива
```

- `digits` - указатель на динамически выделенную память
- `size` - хранит размер выделенной памяти
- Оба поля управляются конструкторами и деструктором

## 4. Механизм перемещения

Перемещение в C++ - это оптимизация, которая позволяет избежать копирования данных:

1. Временный объект создается
2. Его ресурсы "крадутся" (перемещаются)
3. Исходный объект обнуляется

Пример использования:
```
Thirteen a("123");
Thirteen b = std::move(a);  // a теперь пустой, данные перемещены в b
```

## 5. Обработка исключений

### try-catch блоки
Используются для обработки ошибок:

```
try {
    Thirteen num("ABC");  // может выбросить исключение
} catch (const std::invalid_argument& e) {
    // Обработка ошибки
    std::cerr << e.what() << std::endl;
}
```

В нашем классе исключения выбрасываются:
- При некорректных цифрах (>= 13)
- При некорректных символах в строке
- При попытке вычесть большее число из меньшего

## 6. Дружественные функции

Дружественные функции (friend) в C++ имеют доступ к приватным членам класса. В нашей реализации они не используются, так как:
- Все необходимые операции реализованы как методы класса
- Внешний доступ к приватным полям не требуется

Пример возможного использования:
```
friend std::ostream& operator<<(std::ostream& os, const Thirteen& num);
```