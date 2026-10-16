/* 
Складний екзамен, Олексій Рубаха, ШІ-13
*/

#include <iostream>

using namespace std;

int main(){
    
    int n;
    cin >> n;

    // Перевіряємо, чи число містить послідовність "47"
    bool f = false;
    while (n > 0){
        // Перевіряємо останні дві цифри числа
        if (n % 100 == 47){
            f = true;
            break;
        }
        // Видаляємо останню цифру числа для подальшої перевірки
        n /= 10;
    }

    if (f)
        cout << "YES";
    else 
        cout << "NO";
    
    return 0;
}