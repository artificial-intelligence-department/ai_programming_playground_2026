/*
 * Task: Lab 4 - Work with 1D arrays
 * Variant: 15
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */
#include <format>
#include <ios>
#include <iostream>
#include <limits>
#include <print>

int read_val(const std::string prompt, int min_val, int max_val) {
  int value;
  std::print("{}", prompt);
  while (true) {
    if (std::cin >> value && value < max_val && value > min_val) {
      return value;
    } else {
      std::println("Error: input must be between {} and {}", min_val, max_val);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}
void circle_left(const int arr[], int size, int K) {
  std::println("printing ring left from {}", K + 1);
  for (int i = 0; i < size; ++i) {
    std::print("{} ", arr[((K - i) % size + size) % size]);
  }
  std::println();
}
void circle_right(const int arr[], int size, int K) {
  std::println("printing ring right from {}", K + 1);
  for (int i = 0; i < size; ++i) {
    std::print("{} ", arr[(K + i) % size]);
  }
  std::println();
}
void del_frst_lst(int arr[], int &size) {
  if (size < 2) {
    size = 0;
    return;
  }
  for (int i = 0; i < size - 2; ++i) {
    arr[i] = arr[i + 1];
  }
  size -= 2;
}

int main() {
  const int N = 100;
  int arr[N];

  int size = read_val(
      std::format("input array size (between {} and {}): ", 3, N), 3, N);

  for (int i = 0; i < size; ++i) {
    arr[i] = read_val(std::format("input {} element: ", i + 1),
                      std::numeric_limits<int>::min(),
                      std::numeric_limits<int>::max());
  }

  int k_idx = read_val(std::format("input starting position K (1-{}): ", size),
                       1, size) -
              1;

  circle_left(arr, size, k_idx);
  del_frst_lst(arr, size);

  if (size > 0) {
    if (k_idx >= size) {
      k_idx = size - 1;
    }
    circle_right(arr, size, k_idx);
  } else {
    std::println("Ring is empty.");
  }

  return 0;
}
