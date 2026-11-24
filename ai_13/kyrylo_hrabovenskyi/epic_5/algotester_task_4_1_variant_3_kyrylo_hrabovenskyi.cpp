#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    if (!(std::cin >> n)) return 0;

    std::vector<int> rem0, rem1, rem2;

    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        int rem = (x % 3 + 3) % 3; // Коректна остача для від'ємних чисел
        if (rem == 0) rem0.push_back(x);
        else if (rem == 1) rem1.push_back(x);
        else rem2.push_back(x);
    }

    // Сортування груп
    std::sort(rem0.begin(), rem0.end());
    std::sort(rem1.begin(), rem1.end(), std::greater<int>());
    std::sort(rem2.begin(), rem2.end());

    // Видалення дублікатів у кожній групі
    rem0.erase(std::unique(rem0.begin(), rem0.end()), rem0.end());
    rem1.erase(std::unique(rem1.begin(), rem1.end()), rem1.end());
    rem2.erase(std::unique(rem2.begin(), rem2.end()), rem2.end());

    // Об'єднання результатів
    std::vector<int> result;
    result.reserve(rem0.size() + rem1.size() + rem2.size());
    result.insert(result.end(), rem0.begin(), rem0.end());
    result.insert(result.end(), rem1.begin(), rem1.end());
    result.insert(result.end(), rem2.begin(), rem2.end());

    // Виведення результату
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << result[i] << (i + 1 == result.size() ? "" : " ");
    }
    std::cout << "\n";

    return 0;
}