#include <iostream>

using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;
    
    long long max_beauty = -1;
    int max_index = -1;
    
    for (int i = 1; i <= n; ++i) { // проходимо по всіх подругах від 1 до n
        long long current_beauty;
        cin >> current_beauty;
        if (current_beauty > max_beauty) {  // якщо зустріли тюльпан, який красивіший за максимум, Марічка його забере. Запам'ятовуємо його красу та номер подруги.
            max_beauty = current_beauty;
            max_index = i;
        }
    }
    cout << max_index << endl; // виводимо номер подруги, тюльпан якої Марічка могла принести додому   

    return 0;
}