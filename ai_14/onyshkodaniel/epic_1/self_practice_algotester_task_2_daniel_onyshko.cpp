#include <iostream>

int main() {
    int n;
    std::cin >> n;

    // Масив для збереження елементів
    long long a[100];
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    // dp[i] буде зберігати довжину найдовшої ланцюжка, яка закінчується на елементі a[i]
    int dp[100];
    int max_len = 1;

    // Заповнюємо відповіді для кожного елемента
    for (int i = 0; i < n; i++) {
        dp[i] = 1; // Кожен елемент сам по собі — це ланцюжок довжиною 1

        // Шукаємо попередні менші елементи
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                }
            }
        }

        // Оновлюється максимальну довжину
        if (dp[i] > max_len) {
            max_len = dp[i];
        }
    }
//Виводить
    std::cout << max_len << std::endl;

    return 0;
}