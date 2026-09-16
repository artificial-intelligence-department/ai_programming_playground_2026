#include<iostream>
#include<string>
#include<vector>
#include <algorithm>


int main() {
    int n, a, b;
    std::cout << "введіть кількість автомобілів, розмір гаражу типу a, і типу b" << std::endl;
    std::cin >> n >> a >> b;

    if (std::cin.fail()) {
        std::cout << "Помилка: введено не число." << std::endl;
        exit(0);
    }

    if (n < 0 || a < 0 || b < 0) {
        std::cout << "Помилка: кількість автомобілів та розміри гаражів не можуть бути від'ємними." << std::endl;
        exit(0);
    }
    std::vector<int> garages = {a , b};
    std::sort(garages.begin(), garages.end());
    int targetNumber = 0;
    int x = 0; // кількість гаражів типу a
    int y = 0; // кількість гаражів типу b
while (targetNumber * garages[0] < n) {
    for (int x = 0; x <= targetNumber; ++x) {
        int y = targetNumber - x;
        if (x * garages[1] + y * garages[0] == n) {
            std::cout << "Мінімальна кількість гаражів: " << x + y << std::endl;
            return 0;
        }
    }
    targetNumber++;
}
    std::cout << -1 << std::endl;
    return 0;
}