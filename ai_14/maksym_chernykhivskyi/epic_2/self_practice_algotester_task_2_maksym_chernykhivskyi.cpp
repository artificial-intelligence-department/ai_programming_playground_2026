/*Epic 2 - Стипендія
Чернихівський Максим
Ші - 14*/
#include <iostream>

using namespace std;

int main() {
    int n;
    // Зчитуємо кількість іспитів у семестрі
    if (!(cin >> n)) {return 1;};

    bool all_excellent = true;// Припускаємо, що всі оцінки відмінні
    bool has_failing = false;// Припускаємо, що незадовільних оцінок немає

    // Зчитуємо та аналізуємо кожну оцінку
    for (int i = 0; i < n; ++i) {
        int grade;
        if (!(cin >> grade)) {return 1;};

        // Якщо оцінка < 90, то підвищеної стипендії вже не буде
        if (grade < 90) {
            all_excellent = false;
        }
        // Якщо оцінка < 51, студент взагалі втрачає стипендію
        if (grade < 51) {
            has_failing = true;
        }
    }

    if (has_failing) {
        // Є хоча б одна оцінка менше 51
        cout << "Zabud pro stypendiiu" << endl;
    } 
    else if (all_excellent) {
        // Усі оцінки без винятку від 90 до 100
        cout << "Pidvyshchena" << endl;
    } 
    else {
        // Усі оцінки не менше 51, але підвищену не заробив
        cout << "Zvychaina" << endl;
    }

    return 0;
}
