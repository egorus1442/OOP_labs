#include "../include/lab1.h"

bool isPerfectSquare(int num) { 
    int root = static_cast<int>(sqrt(num)); 
    return root * root == num; 
} 
 
std::pair<int, int> solve_func(int upper_limit) { 
    std::pair<int, int> result = std::make_pair(0, 0); 
 
    // Перебор всевозможных значений m и n 
    for (int m = upper_limit - 1; m > 0; --m) { 
        for (int n = m - 1; n > 0; --n) { 
            int sum = m + n; 
            int diff = m - n; 
             
            // Проверяем, являются ли (m + n) и (m - n) квадратами 
            if (isPerfectSquare(sum) && isPerfectSquare(diff)) { 
                result = std::make_pair(m, n);
                return result; // Возвращаем первую найденную пару 
            } 
        } 
    } 
 
    return result;  
}