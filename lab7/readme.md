# Balagur Fate 3 - Симулятор Сражений

## Описание
Система симуляции сражений с NPC (неигровыми персонажами) на карте 100x100, реализованная в двух вариантах: с использованием потоков и корутин.

## Основные возможности
1. Автоматическая симуляция боя с 50 начальными NPC
2. Отображение карты в реальном времени с движением NPC
3. Боевая система с бросками кубиков
4. Два варианта реализации:
   - На основе потоков (многопоточная версия)
   - На основе корутин (однопоточная версия)

## Архитектура

### Структура проекта
```
├── include/
│ ├── common/     # Общие константы и утилиты
│ ├── factory/    # Фабрика NPC
│ ├── game/       # Игровая логика (потоки и корутины)
│ ├── npc/        # Классы NPC
│ ├── observer/   # Наблюдатели за боями
│ └── visitor/    # Посетитель для боевой системы
├── src/
│ ├── factory/
│ ├── game/
│ ├── npc/
│ ├── observer/
│ └── visitor/
└── tests/        # Модульные тесты
```

### Основные компоненты

#### 1. Игровые реализации
- **Версия на потоках** (класс `Game`)
  - Поток движения: Отвечает за перемещение NPC и обнаружение боёв
  - Поток боя: Обрабатывает очередь боёв и разрешает сражения
  - Главный поток: Отображает карту и состояние игры

- **Версия на корутинах** (класс `CoroutineGame`)
  - Одна корутина для обработки движения и боя
  - Главный поток для отображения
  - Использует корутины C++20 для кооперативной многозадачности

#### 2. Система NPC
- Базовый абстрактный класс `NPC`
- Типы:
  - `Orc` (Скорость: 20, убивает Медведей)
  - `Knight` (Скорость: 30, убивает Орков)
  - `Bear` (Скорость: 5, убивает Рыцарей)

#### 3. Боевая система
- Паттерн Посетитель для разрешения боёв
- Механика боя на кубиках:
  - Бросок атаки (1-6)
  - Бросок защиты (1-6)
  - Атака должна быть выше защиты для убийства

#### 4. Система наблюдателей
- Логирование боевых событий в реальном времени:
  - Вывод в консоль
  - Запись в файл (combat_log.txt)

### Потокобезопасные компоненты
- `ThreadSafeContainer`: Управляет коллекцией NPC с защитой мьютексом
- Синхронизация вывода в консоль через `std::mutex`
- Защита очереди боёв в версии с потоками

## Детали реализации

### Реализация корутин
```cpp
struct GameTask {
    struct promise_type {
        GameTask get_return_object();
        std::suspend_always initial_suspend();
        std::suspend_always final_suspend() noexcept;
        void return_void();
        void unhandled_exception();
    };
    // ... управление хендлером
};
```

### Боевая система
1. Расчёт движения:
   - Генерация случайного угла
   - Обновление позиции на основе скорости
   - Контроль границ карты

2. Разрешение боя:
   - Проверка дистанции (10 единиц)
   - Проверка преимущества по типу
   - Сравнение бросков кубиков

### Система отображения
- Обновление карты в реальном времени (интервал 1 секунда)
- Отображение границ символом '#'
- Обозначения NPC:
  - 'O': Орк
  - 'K': Рыцарь
  - 'B': Медведь

## Сборка и запуск

### Требования
- Компилятор с поддержкой C++20 (для корутин)
- CMake 3.15+
- Google Test (для модульных тестов)

### Исполняемые файлы
- `BalagurFate3_Threaded`: Реализация на потоках
- `BalagurFate3_Coroutine`: Реализация на корутинах
- `unit_tests`: Набор тестов

## Особенности работы
- Симуляция длится 30 секунд
- 50 NPC создаются в случайных позициях при старте
- Каждый NPC имеет свою скорость движения и боевые преимущества
- Результаты боёв определяются бросками кубиков и типами NPC
- В конце выводится список выживших