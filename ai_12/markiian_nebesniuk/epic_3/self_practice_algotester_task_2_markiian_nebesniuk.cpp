// Задача Алготестер "Допоможе чи заб'є?"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    int k;
    string s;
    cin >> k >> s;                  // k - потрібна кількість, s - повідомлення

    string pattern = "TOILET";
    int count = 0;                  // лічильник входжень
    int pos = 0;                    // позиція, з якої шукаємо

    // find повертає -1, якщо більше немає входжень
    while ((pos = s.find(pattern, pos)) != -1) {
        count++;
        pos += pattern.size();      // пропускаємо знайдене, щоб не було перетину
    }

    if (count >= k)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    return 0;
}