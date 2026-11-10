/*
 * Task: Algotester Lab 6
 * Variant: 1
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */

#include <iostream>
#include <string>

void quick_sort(std::string arr[], int left, int right) {
  if (left >= right)
    return;

  std::string pivot = arr[left + (right - left) / 2];
  int i = left;
  int j = right;

  while (i <= j) {
    while (arr[i] < pivot)
      i++;
    while (arr[j] > pivot)
      j--;

    if (i <= j) {
      std::string temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
      i++;
      j--;
    }
  }

  quick_sort(arr, left, j);
  quick_sort(arr, i, right);
}

int main() {
  int n, k;
  std::cin >> n >> k;

  std::string *words = new std::string[n];

  for (int i = 0; i < n; ++i) {
    std::cin >> words[i];

    // making everything lowercase
    for (char &c : words[i]) {
      if (c >= 'A' && c <= 'Z') {
        c += 32;
      }
    }
  }

  quick_sort(words, 0, n - 1);

  bool letters[26] = {false};
  int streak = 1;

  // because the list is sorted, we look for same words one after another
  for (int i = 1; i <= n; ++i) {
    // check if its inside the range and
    // if the previous word the same as the next one
    if (i < n && words[i] == words[i - 1]) {
      streak++;
    } else {
      // if streak longer that required
      if (streak >= k) {
        for (char c : words[i - 1]) {
          // convert ascii into 0-25 range
          letters[c - 'a'] = true;
        }
      }
      // if streak is too short, reset it
      streak = 1;
    }
  }

  delete[] words;

  // first line of the ouput
  int total = 0;
  for (int i = 0; i < 26; ++i) {
    if (letters[i]) {
      total++;
    }
  }

  if (total == 0) {
    std::cout << "Empty!\n";
  } else {
    std::cout << total << "\n";
    for (int i = 25; i >= 0; --i) {
      if (letters[i]) {
        std::cout << (char)('a' + i) << " ";
      }
    }
    std::cout << "\n";
  }

  return 0;
}
