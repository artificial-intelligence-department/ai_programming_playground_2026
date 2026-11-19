#include <iostream>
#include <cmath>
#include <string>

using namespace std;

int main() {

    int n; // Довжина зашифрованого повідомлення
    cin >> n;

    string s; // Зашифроване повідомлення
    cin >> s;

    int k = sqrt(n);

    char a[10][10];

    int g = 0; // Індекс поточного символу рядка s
    for(int i =0;i < k;i++){
        for(int j = 0;j < k;j++){
            a[i][j] = s[g]; // Записуємо символ у матрицю
            g++;
        }
    }

    // Розшифрування повідомлення по діагоналях
    for(int d = 0;d < 2 * k - 1;d ++) {
        for(int i = 0;i < k;i++) {
            int j = d - i; // Знаходимо стовпець: i + j = d
            if(j >= 0 && j < k) {
                cout << a[i][j]; // Виводимо символ діагоналі
            }
        }
    }
    cout << endl;
   
    
    return 0;
}