#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // Прискорення введення/виведення
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    if (!(std::cin >> n) || n <= 0) return 0;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    // 1. Розбиття на 3 частини:
    // Відокремлюємо остачу 0 на початок
    auto it1 = std::partition(a.begin(), a.end(), [](int x) {
        return x % 3 == 0;
    });

    // У хвості, що залишився, відокремлюємо остачу 1 від остачі 2
    auto it2 = std::partition(it1, a.end(), [](int x) {
        return x % 3 == 1;
    });

    // Тепер масив має 3 піддіапазони:
    // [a.begin(), it1) -> остача 0
    // [it1, it2)       -> остача 1
    // [it2, a.end())   -> остача 2

    // 2. Сортування кожної частини за умовами:
    std::sort(a.begin(), it1);                          // Остача 0: за зростанням
    std::sort(it1, it2, std::greater<int>());           // Остача 1: за спаданням
    std::sort(it2, a.end());                            // Остача 2: за зростанням

    // 3. Видалення дублікатів
    auto last = std::unique(a.begin(), a.end());
    a.erase(last, a.end());

    // 4. Виведення результату
    std::cout << a.size() << "\n";
    for (size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i] << (i + 1 == a.size() ? "" : " ");
    }
    std::cout << "\n";

    return 0;
}