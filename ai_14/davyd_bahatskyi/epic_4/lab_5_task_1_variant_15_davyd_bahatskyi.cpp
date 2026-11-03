/*
 * Task: Lab 4 - Functions and Arrays
 * Variant: 15
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */
#include <format>
#include <iostream>
#include <limits>
#include <print>

constexpr int N = 100;

int read_val(const std::string &prompt, int min_val, int max_val,
             bool isprompt = true) {
  int value;
  while (true) {
    if (isprompt) {
      std::print("{}({} to {}): ", prompt, min_val, max_val);
    }
    if (std::cin >> value && value <= max_val && value >= min_val) {
      return value;
    } else {
      std::println("Error: input must be between {} and {}", min_val, max_val);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}

void task(const int arr[][N], long &max, int &column, int &n) {
  for (int col = 0; col < n - 1; ++col) {
    long sum = 0;
    for (int row = 0; row < n - col - 1; ++row) {
      sum += arr[row][col];
    }
    std::println("column {0} sum (excluding {0} elements): {1}", col + 1, sum);
    if (sum > max) {
      max = sum;
      column = col;
    }
  }
}

int main() {
  int arr[N][N] = {};

  int n = read_val("input matrix size", 2, 100);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      arr[i][j] = read_val(std::format("input number at coords {},{}", i, j),
                           std::numeric_limits<int>::min(),
                           std::numeric_limits<int>::max(), false);
    }
  }

  long max = std::numeric_limits<long>::min();
  int column = 0;

  task(arr, max, column, n);

  std::println("\nmax number is {} in column {}", max, column + 1);

  return 0;
}
