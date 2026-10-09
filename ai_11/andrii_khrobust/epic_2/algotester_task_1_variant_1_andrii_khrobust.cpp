    /*Задача: Lab 1v1
Хробуст Андрій
Група ШІ-11
*/
#include <iostream>
using namespace std;
int main() {
    long long H, M;
    cin >> H >> M;//початкові показнки мани і хп
    for (int i = 0; i < 3; i++) {
        long long h, m;
        cin >> h >> m;//витрати на заклинання
        if (h > 0 && m > 0) {//якщо витрачається і мана і хп за раз
            cout << "NO";
            return 0;
        }
        H -= h;//обрахунок ресурсів, що залишилися
        M -= m;
    }
    if (H > 0 && M > 0) {//і ті і ті залишилися
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}