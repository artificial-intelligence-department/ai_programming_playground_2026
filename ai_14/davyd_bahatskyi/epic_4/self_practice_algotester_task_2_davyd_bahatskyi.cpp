/*
 * Task: Algotester 1172 - Odd Array
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */
#include <cstdlib>
#include <iostream>

int main() {
  int size;
  std::cin >> size;

  // Dynamic raw arrays via pointers
  int *oArr = new int[size];
  int *eArr = new int[size];
  int oI = 0, eI = 0;

  for (int i = 0; i < size; ++i) {
    int temp;
    std::cin >> temp;
    if (temp % 2 == 0) {
      *(eArr + eI) = temp;
      ++eI;
    } else {
      *(oArr + oI) = temp;
      ++oI;
    }
  }

  // Interleaving is only possible if counts differ by at most 1
  if (std::abs(oI - eI) > 1) {
    std::cout << -1;
    delete[] oArr;
    delete[] eArr;
    return 0;
  }

  int *pOdd = oArr;
  int *pEven = eArr;

  if (oI >= eI) {
    for (int i = 0; i < eI; ++i) {
      std::cout << *(pOdd++) << " " << *(pEven++) << " ";
    }
    if (oI > eI) {
      std::cout << *pOdd;
    }
  } else {
    for (int i = 0; i < oI; ++i) {
      std::cout << *(pEven++) << " " << *(pOdd++) << " ";
    }
    std::cout << *pEven;
  }
  std::cout << "\n";

  delete[] oArr;
  delete[] eArr;
  return 0;
}
