/*Epic 2 - Зуби
Чернихівський Максим
Ші - 14*/
#include <iostream>
#include <algorithm> // Для функції max

using namespace std;

int main() {
    int n;
    long long k; // Використовуємо long long, бо за умовою K може бути до 10^9
    
    if (!(cin >> n >> k)) {return 0;};

    int current_streak = 0;// Поточна кількість "крутих" зубів підряд
    int max_streak = 0;// Максимальна кількість "крутих" зубів підряд

    // Цикл для зчитування та аналізу кожного зуба

    for (int i = 0; i < n; ++i) {

        long long a;
        cin >> a;

        if (a >= k) {
            // Зуб є "крутим", збільшуємо поточну серію
            current_streak++;
            // Оновлюємо максимум, якщо поточна серія стала довшою
            if (current_streak > max_streak) {
                max_streak = current_streak;
            }
        } else {
            // Ланцюжок перервався, скидаємо лічильник поточної серії в 0
            current_streak = 0;
        }
    }

    // Виводимо знайдений максимум
    cout << max_streak << endl;

    return 0;
}
