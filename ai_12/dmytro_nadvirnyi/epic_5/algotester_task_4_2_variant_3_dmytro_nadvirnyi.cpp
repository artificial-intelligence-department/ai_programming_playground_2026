#include <iostream>

using namespace std;

// Злиття двох підмасивів для сортування за зростанням
void merge(int arr[], int left, int mid, int right, int temp[]) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (int p = left; p <= right; ++p) {
        arr[p] = temp[p];
    }
}

// Сортування злиттям (Merge Sort) — складність O(N * log N)
void mergeSort(int arr[], int left, int right, int temp[]) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, temp);
        mergeSort(arr, mid + 1, right, temp);
        merge(arr, left, mid, right, temp);
    }
}

// Функція власного видалення дублікатів та додавання до результату
void appendUnique(int source[], int sourceCount, int dest[], int &destSize) {
    for (int i = 0; i < sourceCount; ++i) {
        if (destSize == 0 || dest[destSize - 1] != source[i]) {
            dest[destSize++] = source[i];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n) || n <= 0) return 0;

    int* mod0 = new int[n];
    int* mod1 = new int[n];
    int* mod2 = new int[n];
    int* temp = new int[n]; // Допоміжний масив для сортування

    int count0 = 0;
    int count1 = 0;
    int count2 = 0;

    // 1. Розподіл за остачами
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        int rem = ((x % 3)+3)%3;
        if (rem == 0) mod0[count0++] = x;
        else if (rem == 1) mod1[count1++] = x;
        else mod2[count2++] = x;
    }

    // 2. Сортуємо кожну групу алгоритмом Merge Sort
    if (count0 > 1) mergeSort(mod0, 0, count0 - 1, temp);
    if (count1 > 1) mergeSort(mod1, 0, count1 - 1, temp);
    if (count2 > 1) mergeSort(mod2, 0, count2 - 1, temp);

    // 3. Для групи з остачею 1 розвертаємо масив (робимо спадання)
    for (int i = 0; i < count1 / 2; ++i) {
        int t = mod1[i];
        mod1[i] = mod1[count1 - 1 - i];
        mod1[count1 - 1 - i] = t;
    }

    // 4. Послідовно об'єднуємо та фільтруємо дублікати
    int* res = new int[n];
    int resSize = 0;

    appendUnique(mod0, count0, res, resSize);
    appendUnique(mod1, count1, res, resSize);
    appendUnique(mod2, count2, res, resSize);

    // 5. Вивід результату
    cout << resSize << "\n";
    for (int i = 0; i < resSize; ++i) {
        cout << res[i] << (i + 1 == resSize ? "" : " ");
    }
    cout << "\n";

    // Очищення пам'яті
    delete[] mod0;
    delete[] mod1;
    delete[] mod2;
    delete[] temp;
    delete[] res;

    return 0;
}