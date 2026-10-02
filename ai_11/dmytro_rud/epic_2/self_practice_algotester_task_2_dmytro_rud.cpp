#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    // Створюємо вектор для збереження монет
    vector<int> coins(n);
    
    int sum = 0;
    int count1 = 0;
    int count2 = 0;

    // Зчитуємо монети у вектор
    for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }

    // Обробляємо дані з вектора за допомогою if-else
    for (int i = 0; i < n; i++) {
        sum += coins[i];
        
        if (coins[i] == 1) {
            count1++;
        } else {
            count2++;
        }
    }

    // Перевіряємо умови розділення за допомогою if-else
    if (sum % 2 != 0) {
        cout << "NO" << endl;
    } else {
        if (count2 % 2 != 0) {
            if (count1 >= 2) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        } else {
            cout << "YES" << endl;
        }
    }

    return 0;
}
