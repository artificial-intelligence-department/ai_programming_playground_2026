/*Epic 5 - Щасливі рядки
Чернихівський Максим
Ші - 14*/

#include <iostream>
#include <string>

using namespace std;

int main() {
    long long n, m;
    string s, t;
    cin >> n >> m >> s >> t;
    
    long long s4 = 0, t4 = 0; // Лічильники кількості цифр 4
    
    for (int i = 0; i < n; i++){
        if (s[i] == '4'){
            s4++;
        }
    }
    for (int i = 0; i < m; i++){
        if (t[i] == '4'){
            t4++;
        }
    }
    
    long long s7 = n - s4; // Лічильники кількості цифр 7
    long long t7 = m - t4;
    
    // Від усіх пар (n + 1) * (m + 1) прибираємо дублікати (s4 * t4 + s7 * t7) і пустий рядок (- 1)
    long long res = (n + 1) * (m + 1) - (s4 * t4 + s7 * t7) - 1;
    cout << res;
    return 0;
}