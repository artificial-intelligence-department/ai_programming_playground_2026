
/* 
Епік 5. Алготестер 4.1 Варіант 2.
Авторка: Ташогло Влада
Група: ші-11
*/

#include <iostream>
using namespace std;

// Злиття двох відсортованих частин масиву в один впорядкований діапазон
void merge(int* arr, int left, int mid, int right) {
    int n1 = mid - left + 1; // Розмір лівої частини
    int n2 = right - mid;     // Розмір правої частини

    // Тимчасові масиви для копіювання лівої та правої половин
    int* l = new int[n1];
    int* r = new int[n2];

    for (int i = 0; i < n1; ++i) {
        l[i] = arr[left + i];
    }
    for (int i = 0; i < n2; ++i) {
        r[i] = arr[mid + 1 + i];
    }

    int i = 0;    // Поточний індекс у лівому масиві
    int j = 0;    // Поточний індекс у правому масиві
    int k = left; // Поточний індекс запису в основний масив

    // Порівнюємо елементи та записуємо менший з них назад у arr
    while (i < n1 && j < n2) {
        if (l[i] <= r[j]) {
            arr[k++] = l[i++];
        } else {
            arr[k++] = r[j++];
        }
    }

    // Копіюємо залишок елементів з лівого масиву, якщо вони залишилися
    while (i < n1) {
        arr[k++] = l[i++];
    }

    // Копіюємо залишок елементів з правого масиву, якщо вони залишилися
    while (j < n2) {
        arr[k++] = r[j++];
    }

    // Звільняємо тимчасово виділену пам'ять
    delete[] r;
    delete[] l;
}

// Рекурсивне сортування злиттям (Merge Sort)
void mergeSort(int* arr, int left, int right) {
    // Базовий випадок: якщо підмасив містить 0 або 1 елемент
    if (left >= right) return;

    // Знаходимо індекс середини без ризику переповнення
    int mid = left + (right - left) / 2;

    // Рекурсивно сортуємо ліву та праву частини
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    // Об'єднуємо відсортовані частини
    merge(arr, left, mid, right);
}

int main() {
    int n, k;
    cin >> n >> k;

    // Виділяємо пам'ять та зчитуємо початковий масив
    int* arr1 = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> arr1[i];
    }

    // Масив для унікальних елементів
    int* arr2 = new int[n];
    int count = 0;

    // Видаляємо дублікати: перевіряємо, чи поточний елемент уже є в arr2
    for (int i = 0; i < n; ++i) {
        bool found = false;
        for (int j = 0; j < count; ++j) {
            if (arr1[i] == arr2[j]) {
                found = true;
                break;
            }
        }
        // Якщо елемент новий — зберігаємо його
        if (!found) {
            arr2[count++] = arr1[i];
        }
    }

    // Сортуємо отриманий масив унікальних значень
    mergeSort(arr2, 0, count - 1);

    // Захист від k >= count (беремо залишок від ділення)
    if (count > 0) k %= count;

    // Виконуємо циклічний зсув масиву вліво на k позицій
    int* result = new int[count];
    int c = 0;

    // Спочатку переносимо елементи починаючи з k-ї позиції до кінця
    for (int i = k; i < count; ++i) {
        result[c++] = arr2[i];
    }
    // Потім дописуємо початок масиву (від 0 до k-1)
    for (int i = 0; i < k; ++i) {
        result[c++] = arr2[i];
    }

    // Виведення кількості елементів та результуючого масиву
    cout << c << endl;
    for (int i = 0; i < count; ++i) {
        cout << result[i] << ' ';
    }

    // Звільнення всієї виділеної динамічної пам'яті
    delete[] arr1;
    delete[] arr2;
    delete[] result;
    return 0;
}
