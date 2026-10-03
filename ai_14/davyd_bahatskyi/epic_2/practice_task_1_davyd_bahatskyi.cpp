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
  int len, diff = 0, level = 4;
  char num, capital, special;

  cout << "whats the password length? ";
  if (!(cin >> len) || len < 1 || len > 64) {
    cout << RED << "[E]" << RESET // this makes [E] in the error output red.
         << " Length must be more than 0 and less than 64.\n";
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

  // check if there are numbers in the password
  // and if there are, disable the alert message
  if (num == 'y') {
    diff++; // adds 1 to the amount of different types of characters used
  }
  if (capital == 'y') {
    diff++;
  }

  if (special == 'y') {
    diff++;
  }

  if (len >= 8 && diff >= 2) {
    cout << "\nPassed.\n";
  } else {
    cout << "\nDidn't pass.\n";
  }

  // code thats responsible for the password strength level
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
    cout << "Password level: 1 - very weak.\n"
            "Recomendation: Password is too short. minnimum is 8 characters.\n";
    break; // break here because otherwise it will output each case output
           // instead of only specific one.
  case 2:
    cout << "Password level: 2 - weak.\n"
            "Recomendation: Make password length 8+ and add capital letters, "
            "numbers and " // split into multiple lines for easier code
                           // visibility. doesnt affect the actual output
            "special characters.\n";
    break;
  case 3:
    cout << "Password level: 3 - okay\n"
            "Recomendation: Add another character type and lengthen your "
            "password up to 12 characters.\n";
    break;
  case 4:
    cout << "Password level: 4 - good\n"
            "Recomendation: You can make password 12+ characters long with all "
            "character types included.\n";
    break;
  case 5:
    cout << "Password level: 5 - strong\n"
            "Recomendation: You dont have to do anything else.\n";
    break;
  default: // if level variable didnt get a valid value
    cout << RED << "[E]" << RESET << " Something went wrong.\n";
    return 1;
  }
  // outputs an error if there are no other types of characters except letters
  if (num == 'n' || special == 'n') {
    cout << "Alert: Password made only from letters is easier to guess.\n";
  }

  return 0;
}
