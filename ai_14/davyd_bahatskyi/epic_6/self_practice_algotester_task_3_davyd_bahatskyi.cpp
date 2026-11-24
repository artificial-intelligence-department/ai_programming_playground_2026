/*
 * Task: Self Practice 3 - Algotester 0004 (Office Street. Part 2)
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */

#include <iostream>

struct Company {
  int id;
  long long length;
  long long workers;

  bool operator<(const Company &other) const {
    long long lhs = length * other.workers;
    long long rhs = other.length * workers;
    if (lhs != rhs) {
      return lhs < rhs;
    }
    return id < other.id;
  }
};

std::ostream &operator<<(std::ostream &os, const Company &c) {
  return os << c.id;
}

void swapCompanies(Company &a, Company &b) {
  Company temp = a;
  a = b;
  b = temp;
}

void quickSort(Company *arr, int left, int right) {
  if (left >= right) {
    return;
  }

  int mid = left + (right - left) / 2;
  if (arr[mid] < arr[left]) {
    swapCompanies(arr[left], arr[mid]);
  }
  if (arr[right] < arr[left]) {
    swapCompanies(arr[left], arr[right]);
  }
  if (arr[right] < arr[mid]) {
    swapCompanies(arr[mid], arr[right]);
  }
  Company pivot = arr[mid];

  int i = left;
  int j = right;
  while (i <= j) {
    while (arr[i] < pivot) {
      ++i;
    }
    while (pivot < arr[j]) {
      --j;
    }
    if (i <= j) {
      swapCompanies(arr[i], arr[j]);
      ++i;
      --j;
    }
  }

  if (left < j) {
    quickSort(arr, left, j);
  }
  if (i < right) {
    quickSort(arr, i, right);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = 0;
  if (!(std::cin >> n)) {
    return 0;
  }

  Company *companies = new Company[n];
  for (int i = 0; i < n; ++i) {
    companies[i].id = i + 1;
    std::cin >> companies[i].length;
  }
  for (int i = 0; i < n; ++i) {
    std::cin >> companies[i].workers;
  }

  quickSort(companies, 0, n - 1);

  for (int i = 0; i < n; ++i) {
    if (i > 0) {
      std::cout << ' ';
    }
    std::cout << companies[i];
  }
  std::cout << '\n';

  delete[] companies;
  return 0;
}
