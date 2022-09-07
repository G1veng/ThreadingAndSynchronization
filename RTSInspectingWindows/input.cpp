#include "input.h"


bool IsNumeric(std::string str) {
  for (int i = 0; i < str.length(); i++)
    if (isdigit(str[i]) == false)
      return false;
  return true;
}


int GetInt(void) {
  std::string input;

  std::cin >> input;
  while (IsNumeric(input) == false) {
    std::cout << "Enter number: ";
    std::cin >> input;
  }

  return std::stoi(input);
}

int GetInt(int lowerBorder, int highBorder) {
  std::string input;

  std::cin >> input;
  while (IsNumeric(input) == false || std::stoi(input) < lowerBorder || stoi(input) >= highBorder) {
    std::cout << "Enter number: ";
    std::cin >> input;
  }

  return stoi(input);
}

int GetInt(int highBorder) {
  std::string input;

  std::cin >> input;
  while (IsNumeric(input) == false || stoi(input) < 0 || stoi(input) >= highBorder) {
    std::cout << "Enter number: ";
    std::cin >> input;
  }

  return stoi(input);
}