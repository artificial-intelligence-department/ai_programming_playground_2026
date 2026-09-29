/*
 * Epic 2: Class Practice Task - Password Strength Analyzer
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */
#include <iostream>
using namespace std;

// making errors red
const char *RED = "\033[1;31m";
const char *RESET = "\033[0m";

int main() {
  int len, diff = 0, level = 0;
  char num, capital, special;

  cout << "whats the password length? ";
  if (!(cin >> len) || len < 1 || len > 64) {
    cout << RED << "[E]" << RESET << " Length must be less than 64.\n";
    return 1;
  }
  cout << "are there numbers? ";
  if (!(cin >> num) || (num != 'y' && num != 'n')) {
    cout << RED << "[E]" << RESET
         << " The answer should be either 'y' or 'n'.\n";
    return 1;
  }
  cout << "are there capital letters? ";
  if (!(cin >> capital) || (capital != 'y' && capital != 'n')) {
    cout << RED << "[E]" << RESET
         << " The answer should be either 'y' or 'n'.\n";
    return 1;
  }
  cout << "are there special characters? ";
  if (!(cin >> special) || (special != 'y' && special != 'n')) {
    cout << RED << "[E]" << RESET
         << " The answer should be either 'y' or 'n'.\n";
    return 1;
  }

  if (num == 'y') {
    diff++;
  }
  if (capital == 'y') {
    diff += 1;
  }

  if (special == 'y') {
    diff += 1;
  }

  if (len >= 8 && diff >= 2) {
    cout << "passed\n";
  } else {
    cout << "didn\'t pass\n";
  }

  if (len < 6) {
    level = 1;
  } else if (len < 8 || diff == 0) {
    level = 2;
  } else if (diff == 1) {
    level = 3;
  } else if (len >= 12 && diff == 3) {
    level = 5;
  } else {
    level = 4;
  }

  switch (level) {
  case 1:
    cout << "password is very weak.\n"
            "password is too short. minnimum is 8 characters.\n";
    break;
  case 2:
    cout << "password is weak.\n"
            "make password length 8+ and add capital letters, numbers and "
            "special characters.\n";
    break;
  case 3:
    cout << "password is okay\n"
            "add another character type and lengthen your password up to 12 "
            "characters\n";
    break;
  case 4:
    cout << "password is good\n"
            "you can make password 12+ characters long with all character "
            "types included\n";
    break;
  case 5:
    cout << "password is strong\n"
            "you dont have to do anything else\n";
    break;
  }

  return 0;
}
