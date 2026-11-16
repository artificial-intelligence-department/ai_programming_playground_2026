#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Ініціалізація та ввід даних
    int N, K;
    cin >> N;
    cin >> K;
    vector <int> a(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    // Сортування та видалення елементів засобами STL
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());

    // Оптимізуємо K та виконуєм зсув вліво
    K = K % a.size();
    rotate(a.begin(), a.begin() + K, a.end());

    // Виведння результату
    cout << a.size() << endl;
    for (int i = 0; i < a.size(); i++) {
        if (i != 0) cout << " ";
        cout << a[i];
    }
    return 0;
}