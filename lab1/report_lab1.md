# Отчет по лабораторной работе №1 по курсу "Объектно-ориентированное программирование"

Студент: Матвеев Семен Романович \
Учебная группа: M8О-215Б-23 \
Контакты: karmishen@inbox.ru \
Работа выполнена: 09.09.2024\
Преподаватель: Зайцев Данила Евгеньевич

## 1. Тема

Первая программа на C++

## 2. Цель работы

1) Научиться писать простые программы, использующие ввод/вывод через потоки std::cin, std::cout
2) Изучить базовые операторы и конструкции C++
3) Изучить систему сборки CMake
4) Изучить библиотеку для написания unit-тестов Google Test

## 3. Задание

Вариант 11 

## 4. Идея, метод, алгоритм решения задачи

Сделать лаб

## 5. Сценарий выполнения работы

1. Приступить к лабе 
2. Сделать лабу
3. Отдохнуть 

## 6. Распечатка протокола


## 7. Дневник отладки

| №   | Лаб. или дом. | Дата       | Время | Событие                                                                                                        | Действие по исправлению | Примечание |
|:---:|:-------------:|:----------:|:-----:|:--------------------------------------------------------------------------------------------------------------:|:-----------------------:|:----------:|
| 1 | Дом | 07.09.2024 | 22:00 | Некорректное поведение исходной формулы с отрицательными числами | Добавил проверку значений параметров divider и boundary |  |
| 2 | Дом | 07.09.2024 | 22:15 | Некорректное поведение программы при вводе веществнных чисел или строки, начинающейся с целого числа | Добавил проверку символов в потоке std::cin, которые следуют за считанным значением |   |
| 3 | Дом | 08.09.2024 | 23:00 | После одного некорректного ввода программа заканчивает своё выполнение | Заключил ввод значения и его валидацию в цикл while |   |
| 4 | Дом | 08.09.2024 | 23:20 | Невозможность сборки проекта с помощью CMake на Windows | Собрал проект в Docker контейнере, потом перешел на Linux для сборки без контейнера | Перед этим потратил 5 часов в попытках подружить CMake и особенно Google Test с Windows |
| 5 | Дом | 09.09.2024 | 04:20 | Ошибка сборки CMake | Изменил файловую структуру и CMakeLists.txt |   |
| 6 | Дом | 09.09.2024 | 05:00 | Отсутствие unit-тестов | Добавил unit-тесты с помощью фреймворка Google Test |   |


## 8. Замечания автора по существу работы

Все гуд

## 9. Выводы

Я вспомнил, как надо работать с потоками std::cin, std::cout, с базовыми операторами и конструкциями C++. Я научился использовать CMake для сборки проекта и Google Test для unit-тестирования проекта