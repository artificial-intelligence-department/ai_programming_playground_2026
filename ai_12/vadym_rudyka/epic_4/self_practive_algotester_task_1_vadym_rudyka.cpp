#include <iostream>
using namespace std;
// Максимальна кількість елементів: 1000 * 1000 = 1,000,000
// Глобальні масиви автоматично ініціалізуються нулями і виділяються в сегменті даних (не в стеку)
int elements[1000001];
int duplicates[500001];

// швидке сортування для масиву елементів
void quickSort(int left, int right) {
    if (left >= right) return;
    
    int pivot = elements[left + (right - left) / 2];
    int i = left;
    int j = right;
    /* Quicksort працює так, що він розділяє масив на дві частини: елементи менші за pivot і елементи більші за pivot.
    Після цього рекурсивно сортує обидві частини. */
    while (i <= j) {
        while (elements[i] < pivot) i++;
        while (elements[j] > pivot) j--;
        if (i <= j) {
            int temp = elements[i];
            elements[i] = elements[j];
            elements[j] = temp;
            i++;
            j--;
        }
    }
    
    quickSort(left, j);
    quickSort(i, right);
}

int main() {
    int n, m;
    if (!(cin >> n >> m)) return 0;

    int total_elements = n * m;

    // Зчитування всіх елементів матриці
    for (int i = 0; i < total_elements; ++i) {
        cin >> elements[i];
    }

    // Сортуємо масив вручну
    quickSort(0, total_elements - 1);

    int dup_count = 0;
    
    // Пошук дублікатів (оскільки числа зустрічаються не більше 2 разів, однакові будуть поруч)
    for (int i = 0; i < total_elements - 1; ++i) {
        if (elements[i] == elements[i + 1]) {
            duplicates[dup_count] = elements[i];
            dup_count++;
            i++; // Пропускаємо другий елемент пари
        }
    }

    // Виведення результату
    cout << dup_count << "\n";
    for (int i = 0; i < dup_count; ++i) {
        cout << duplicates[i] << (i + 1 == dup_count ? "" : " ");
    }
    cout << "\n";

    return 0;
}
