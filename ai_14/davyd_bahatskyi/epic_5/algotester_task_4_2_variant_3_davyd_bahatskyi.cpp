/*
 * Task: Algotester Lab 4_2
 * Variant 3
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */
#include <iostream>

void radix(int *arr, int n, bool reverse = false) {
  if (n <= 1) {
    return;
  }

  // create a temp array to avoid
  // overwriting numbers in main array
  int *temp = new int[n];

  for (int bit = 0; bit < 10; ++bit) {

    // counting how many numbers with bit 1 we have
    int o = 0;
    for (int i = 0; i < n; ++i) {
      if (((arr[i] >> bit) & 1) == 0) {
        o++;
      }
    }

    // copying all numbers into a temporary array
    // first half is numbers with first bit 0 and
    // second half is numbers with first bit 1
    int z = 0;
    for (int i = 0; i < n; ++i) {
      if (((arr[i] >> bit) & 1) == 0) {
        temp[z++] = arr[i];
      } else {
        temp[o++] = arr[i];
      }
    }

    // copying all numbers back from temporary array
    // into the main one
    for (int i = 0; i < n; ++i) {
      arr[i] = temp[i];
    }
  }
  if (reverse) {
    for (int i = 0; i < n; i++) {
      arr[i] = temp[n - i - 1];
    }
  }
  delete[] temp;
}

int main() {
  int rem0[1000], rem1[1000], rem2[1000];
  int size;
  std::cin >> size;

  int i0 = 0, i1 = 0, i2 = 0;
  for (int i = 0; i < size; ++i) {
    int temp;
    std::cin >> temp;
    if (temp % 3 == 0) {
      rem0[i0++] = temp;
    } else if (temp % 3 == 1) {
      rem1[i1++] = temp;
    } else {
      rem2[i2++] = temp;
    }
  }

  radix(rem0, i0);
  radix(rem1, i1, true);
  radix(rem2, i2);
  int result[1000] = {}, ip = 0;

  for (int i = 0; i < i0; ++i) {
    result[ip++] = rem0[i];
  }
  for (int i = 0; i < i1; ++i) {
    result[ip++] = rem1[i];
  }
  for (int i = 0; i < i2; ++i) {
    result[ip++] = rem2[i];
  }

  ip = 0;
  for (int i = 0; i < size; ++i) {
    if (i == 0 || result[i - 1] != result[i]) {
      result[ip++] = result[i];
    }
  }

  std::cout << ip << '\n';
  for (int i = 0; i < ip; ++i) {
    std::cout << result[i] << " ";
  }
  return 0;
}
