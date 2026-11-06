/*
Задача Алготестер "Сапер"
Небеснюк Маркіян
ШІ-12
*/

#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    char N[n];

    string result;

    int k = 0; // Змінна-лічильник для сусідніх зірочок

    // Зчитуванян символів полотна
    for (int i = 0; i < n; i++) {
        cin >> N[i];
    }

    // Аналіз кожного символа
    for (int i = 0; i < n; i++) {
        k = 0;
        
        if (N[i] == '*') result += '*';
        else if (N[i] == '.') {
            if (N[i + 1] == '*') k++; 
            if (N[i - 1] == '*') k++;
            result += (k + '0');
        }
    }

    cout << result << endl; // Вивід підсумкового рядка
    
    return 0;
}