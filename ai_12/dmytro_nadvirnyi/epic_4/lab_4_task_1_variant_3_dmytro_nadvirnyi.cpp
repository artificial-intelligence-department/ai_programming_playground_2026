#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    const int N = 100;      // максимальна довжина масиву за методичкою
    int n, M;
    int arr[N + 1]; // N + 1, бо після вставки довжина може збільшитись на 1
    cout << "Введіть довжину масиву (1.." << N << "): ";
    while (!(cin >> n) || n < 1 || n > N) {
        if (cin.eof()) return 0;
        cout << "Помилка! Введіть ціле число від 1 до " << N << ": ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    srand(time(0));

    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 21 - 10;
    }

    // Виведення початкового масиву
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Видалення нулів
    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) {
            for (int j = i; j < n - 1; j++) {
                arr[j] = arr[j + 1];
            }
            n--;
            i--;
        }
    }

    // Вставлення після першого парного елемента
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            // M[I-1]+2; для першого елемента (I-1 не існує) беремо сам елемент
            M = (i > 0) ? arr[i - 1] + 2 : arr[i] + 2;

            for (int j = n; j > i + 1; j--) {
                arr[j] = arr[j - 1];
            }

            arr[i + 1] = M;
            n++;
            break;
        }
    }

    // Виведення результату
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}