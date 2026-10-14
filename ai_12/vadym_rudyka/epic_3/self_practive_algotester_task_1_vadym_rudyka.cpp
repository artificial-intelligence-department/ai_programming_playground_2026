#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
// Масив для зберігання результатів кожної партії, а також змінні для підрахунку очок та кількості виграних партій
    char x;
    int kolya = 0;
    int vasya = 0;
    int kolyaGames = 0;
    int vasyaGames = 0;

    for (int i = 0; i < n; i++) {
        cin >> x;

        if (x == 'K')
            kolya++;
        else
            vasya++;

        // Перевіряємо, чи закінчилась партія
        if ((kolya >= 11 || vasya >= 11) &&
            abs(kolya - vasya) >= 2) {

            if (kolya > vasya)
                kolyaGames++;
            else
                vasyaGames++;

            kolya = 0;
            vasya = 0;
        }
    }

    // Рахунок по партіях
    cout << kolyaGames << ":" << vasyaGames << endl;

    // Якщо остання партія не закінчилась
    if (kolya > 0 || vasya > 0) {
        cout << kolya << ":" << vasya << endl;
    }

    return 0;
}