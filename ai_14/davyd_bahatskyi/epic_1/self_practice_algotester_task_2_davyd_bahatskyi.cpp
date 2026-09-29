/*
 * Завдання: Депутатські гроші
 * Автор: Багацький Давид Павлович
 * Група: ШІ-14
 */
#include <iostream>

using namespace std;

int main() {
  long long n;
  if (!(cin >> n))
    return 0;

  // Номінали купюр від найбільшої до найменшої
  int bills[] = {500, 200, 100, 50, 20, 10, 5, 2, 1};

  long long count = 0;

  for (int bill : bills) {
    count += n / bill;
    n %= bill;
  }

  cout << count << "\n";

  return 0;
}
