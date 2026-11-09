#include <iostream>
#include <vector>

// Перевірка порядку двох елементів: повертає true, якщо a має йти раніше b
bool precedes(int a, int b) {
    int remA = a % 3;
    int remB = b % 3;

    if (remA != remB) {
        return remA < remB;
    }
    if (remA == 1) {
        return a > b; // За спаданням для остачі 1
    }
    else {
        return a < b; // За зростанням для остач 0 та 2
    }
}

// Власна реалізація QuickSort (Швидке сортування) O(N log N)
void customQuickSort(std::vector<int>& arr, int low, int high) {
    if (low >= high) return;

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (precedes(arr[j], pivot) || arr[j] == pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    int p = i + 1;

    customQuickSort(arr, low, p - 1);
    customQuickSort(arr, p + 1, high);
}

// Власна реалізація видалення дублікатів (аналог std::unique)
int removeDuplicates(std::vector<int>& arr) {
    if (arr.empty()) return 0;

    int writeIdx = 0;
    for (size_t readIdx = 1; readIdx < arr.size(); ++readIdx) {
        if (arr[readIdx] != arr[writeIdx]) {
            ++writeIdx;
            arr[writeIdx] = arr[readIdx];
        }
    }
    return writeIdx + 1; // Новий розмір унікального масиву
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    if (!(std::cin >> n)) return 0;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    // 1. Власне сортування
    customQuickSort(a, 0, n - 1);

    // 2. Власне видалення дублікатів
    int m = removeDuplicates(a);

    // 3. Вивід результату
    std::cout << m << "\n";
    for (int i = 0; i < m; ++i) {
        std::cout << a[i] << (i + 1 == m ? "" : " ");
    }
    std::cout << "\n";

    return 0;
}