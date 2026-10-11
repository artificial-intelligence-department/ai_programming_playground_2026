/*
 * Epic 3: Class Practice Task - Monthly Budget Analyzer
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */
#include <cstdlib>
#include <iomanip>
#include <ios>
#include <iostream>

void dailyspendings(const double spending[], int N) {
  std::cout << std::setw(3) << "day" << std::setw(13) << "spendings\n";
  for (int i = 0; i < N; i++) {
    std::cout << std::fixed << std::setw(3) << i + 1 << std::setw(13)
              << std::setprecision(2) << spending[i] << "\n";
  }
}

double sum_rec(const double spending[], int N) {
  if (N <= 0) {
    return 0.0;
  }
  return spending[N - 1] + sum_rec(spending, N - 1);
}

void min_max(const double spending[], int N, double &min_val, double &max_val) {
  min_val = spending[0];
  max_val = spending[0];

  for (int i = 1; i < N; i++) {
    if (min_val > spending[i]) {
      min_val = spending[i];
    }
    if (max_val < spending[i]) {
      max_val = spending[i];
    }
  }
}

void mansort(const double spending[], int N) {
  double copy[31];
  for (int i = 0; i < N; i++) {
    copy[i] = spending[i];
  }

  for (int i = 0; i < N - 1; i++) {
    for (int j = i + 1; j < N; j++) {
      if (copy[i] < copy[j]) {
        double temp = copy[i];
        copy[i] = copy[j];
        copy[j] = temp;
      }
    }
  }

  int count = (N < 3) ? N : 3;
  std::cout << "top-" << count << " spendings: ";
  for (int i = 0; i < count; i++) {
    std::cout << std::fixed << std::setprecision(2) << copy[i];
    if (i < count - 1) {
      std::cout << ", ";
    };
  }
}
void overdue(const double spending[], int N, double limit = 1000) {
  int amount = 0;
  for (int i = 0; i < N; i++) {
    if (spending[i] > limit) {
      std::cout << "day " << i + 1 << ": " << std::fixed << std::setprecision(2)
                << spending[i] << "\n";
      amount++;
    }
  }
  std::cout << "total amount of days over the limit: " << amount << "\n";
}
void average(const double spending[], int N) {
  double sum = sum_rec(spending, N);
  int nonzero = 0;
  for (int i = 0; i < N; i++) {
    if (spending[i] <= 0) {
      continue;
    }
    nonzero++;
  }
  if (nonzero == 0) {
    std::cout << "no money spent";
    return;
  }
  double average = sum / nonzero;
  std::cout << "average money spent per day (excluding days when no money was "
               "spent): "
            << std::fixed << std::setprecision(2) << average << " UAH\n";
}

int main() {
  double budget;
  int N, choice;
  double spending[31];

  std::cout << "type in your budget: ";
  while (!(std::cin >> budget) || budget < 0) {
    std::cerr << "[E] invalid budget. Please enter a positive number: ";
    std::cin.clear();
    std::cin.ignore(10000, '\n');
  }
  std::cout << "amount of days: ";
  while (!(std::cin >> N) || N < 1 || N > 31) {
    std::cerr << "[E] invalid amount of days. Must be between 1 and 31: ";
    std::cin.clear();
    std::cin.ignore(10000, '\n');
  }

  for (int i = 0; i < N; i++) {
    std::cout << "money spent on day " << i + 1 << "/" << N << ": ";
    while (!(std::cin >> spending[i]) || spending[i] < 0) {
      std::cerr << "[E] invalid spending. Must be a non-negative number: ";
      std::cin.clear();
      std::cin.ignore(10000, '\n');
    }
  }

menu:
  do {
    std::cout << "\n\n\n"
              << "1 - show daily spendings\n"
              << "2 - spending stats\n"
              << "3 - days over daily limit\n"
              << "4 - 3 most expensive days\n"
              << "0 - exit\n\n"
              << "type your choice: ";
    if (!(std::cin >> choice)) {
      std::cerr << "[E] invalid input: please enter a number (0-4)\n";
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      goto menu;
    }

    switch (choice) {
    case 0: // exit
      std::cout << "exit\n";
      break;
    case 1: // show daily spendings
      dailyspendings(spending, N);
      break;
    case 2: { // stats
              // min and max money spend in a day. in one function
      double min_val = 0, max_val = 0;
      min_max(spending, N, min_val, max_val);
      std::cout << "minumum spent is " << min_val << "\nmaximum spent is "
                << max_val << "\n";
      // sum spent. recursive function
      double sum = sum_rec(spending, N);
      std::cout << "the sum is " << sum << "\n";

      // rest of budget. if negative, use mod and show overspendings
      double result = budget - sum;
      if (result < 0) {
        std::cout << "budget overrun: ";
      } else {
        std::cout << "budget remainder: ";
      }
      std::cout << std::fixed << std::setprecision(2) << std::abs(result)
                << " UAH\n";

      // average spendings per day. days with 0 are ignored
      average(spending, N);
      // day when the budget was all spent. while loop and break once sum is
      // over the budget. if the budget was enough, show remaining budget
      double spent = 0;
      int final_day = -1;
      int i = 0;
      while (i < N) {
        spent += spending[i];
        if (spent > budget) {
          final_day = i + 1;
          break;
        }
        i++;
      }
      if (final_day == -1) {
        std::cout << "budget lasted till the last day. remaining " << std::fixed
                  << std::setprecision(2) << (budget - spent) << "UAH\n";
      } else {
        std::cout << "all budget was spent on day " << final_day << ", spent "
                  << std::fixed << std::setprecision(2) << spent << " UAH\n";
      }

      break;
    }
    case 3: { // days over budget
              // user types in daily limit
              // if 0 then default is 1000, limit is set as parameter by default
              // display days' number and their amount
      double limit = 0;
      std::cout << "input daily limit: ";
      if (!(std::cin >> limit) || limit <= 0) {
        if (limit != 0) {
          std::cerr << "invalid number. using default 1000 UAH\n";
        }
        overdue(spending, N);
      } else {
        overdue(spending, N, limit);
      }
      break;
    }
    case 4: // 3 most expensive days
            // sort array with cycles.
            // display 3 biggest numbers, if days are less then 3, show the
            // rest starting array stays the same
      mansort(spending, N);
      break;
    default: // error message
      std::cerr << "[E] invalid option\n";
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      goto menu;
      break;
    }
  } while (choice != 0);

  return 0;
}
