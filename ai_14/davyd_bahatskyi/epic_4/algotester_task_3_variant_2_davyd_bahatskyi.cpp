/*
 * Task: Algotester Lab 3 - Variant 2
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */
#include <iostream>
#include <print>

int main() {
  int N, M;
  std::cin >> N;
  int *a = new int[N];
  for (int i = 0; i < N; ++i) {
    std::cin >> a[i];
  }

  std::cin >> M;
  int *b = new int[M];
  for (int i = 0; i < M; ++i) {
    std::cin >> b[i];
  }

  int uni = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      if (a[i] == b[j]) {
        uni++;
        break;
      }
    }
  }

  std::println("{}\n{}", uni, M + N - uni);

  delete[] a;
  delete[] b;
  return 0;
}
