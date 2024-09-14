#include <iostream>
#include "include/lab1.h"

int main()
{
  int lhv;
  std::cout << "введите число: ";
  std::cin  >> lhv;
  std::pair<int, int> s = solve_func(lhv);

  std::cout << "результат: " << s.first << " " << s.second << std::endl;

  return 0;
}  

