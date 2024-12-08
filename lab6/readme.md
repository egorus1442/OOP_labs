# Balagur Fate 3 - Редактор подземелий

## Описание проекта
Редактор подземелий для RPG игры Balagur Fate 3, позволяющий создавать и управлять NPC (non-player characters) на игровой карте размером 500x500 метров.

## Основной функционал
1. Создание NPC разных типов (Орк, Рыцарь, Медведь) с указанием координат и имени
2. Сохранение и загрузка NPC из файла
3. Отображение списка всех NPC
4. Боевой режим с указанием дальности

## Архитектура проекта

### Структура директорий
├── include/ # Заголовочные файлы
│ ├── factory/ # Фабрика для создания NPC
│ ├── game/ # Основная игровая логика
│ ├── npc/ # Классы NPC
│ ├── observer/ # Наблюдатели за событиями
│ └── visitor/ # Посетитель для боевой системы
├── src/ # Исходный код
│ ├── factory/
│ ├── game/
│ ├── npc/
│ ├── observer/
│ └── visitor/
└── tests/ # Модульные тесты

### Основные компоненты

#### 1. NPC (Non-Player Characters)
- Базовый абстрактный класс `NPC` (`include/npc/npc.h`)
- Наследники:
  - `Orc` (Орк)
  - `Knight` (Рыцарь)
  - `Bear` (Медведь)

```
class NPC {
public:
    virtual void accept(CombatVisitor& visitor) = 0;
    virtual std::string getType() const = 0;
    // ... другие методы
};
```

#### 2. Фабрика (`NPCFactory`)
Отвечает за создание NPC и работу с файлами:
- Создание NPC по типу
- Сохранение NPC в файл
- Загрузка NPC из файла

```
class NPCFactory {
public:
    static std::shared_ptr<NPC> createNPC(const std::string& type, 
                                        const std::string& name, 
                                        double x, 
                                        double y);
    static void saveToFile(const std::vector<std::shared_ptr<NPC>>& npcs, 
                          const std::string& filename);
    static std::vector<std::shared_ptr<NPC>> loadFromFile(const std::string& filename);
};
```

#### 3. Боевая система
Использует паттерн Visitor для реализации боевых взаимодействий:
- Орки убивают медведей
- Медведи убивают рыцарей
- Рыцари убивают орков

```
class CombatVisitor {
public:
    void visit(Orc& orc);
    void visit(Knight& knight);
    void visit(Bear& bear);
    // ... другие методы
};
```

#### 4. Система наблюдателей
Реализует паттерн Observer для логирования боевых событий:
- `ConsoleObserver`: вывод в консоль
- `FileObserver`: запись в файл log.txt

```
class CombatObserver {
public:
    virtual void onCombat(const std::string& attacker, 
                         const std::string& defender, 
                         bool killed) = 0;
    virtual void onDeath(const std::string& npcName) = 0;
};
```

## Как это работает

### 1. Создание NPC
1. Пользователь выбирает тип NPC
2. Вводит имя и координаты
3. `NPCFactory` создает соответствующий объект
4. NPC добавляется в вектор активных NPC

### 2. Боевой режим
1. Пользователь указывает дальность боя
2. Система проверяет все пары NPC на возможность боя (по дистанции)
3. Для каждой подходящей пары:
   - Первый NPC атакует второго
   - Второй NPC атакует первого
   - Результаты фиксируются наблюдателями
4. Погибшие NPC удаляются из игры

### 3. Сохранение/Загрузка
- При сохранении каждый NPC записывается в файл в формате:
  `тип имя x y`
- При загрузке файл читается построчно и NPC воссоздаются через фабрику

## Сборка проекта
Проект использует CMake для сборки. Основные цели:
- `game_lib`: основная библиотека
- `BalagurFate3`: исполняемый файл
- `unit_tests`: модульные тесты

## Тестирование
Проект включает модульные тесты для всех основных компонентов:
- Тесты создания NPC
- Тесты боевой системы
- Тесты сохранения/загрузки

Для запуска тестов:
```
./unit_tests
```