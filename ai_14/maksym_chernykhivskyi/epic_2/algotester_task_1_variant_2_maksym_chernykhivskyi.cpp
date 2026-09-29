/*Epic 2 - lab 1v2
Чернихівський Максим
Ші - 14*/

#include <iostream>

using namespace std; 

int main() {
    // Масиви для зберігання початкових висот ніжок (h) та довжини, яку треба відрізати (r)
    long long h[4];
    long long r[4];
    
    // Зчитування початкових висот 4 ніжок стола
    for (int i = 0; i < 4; ++i) {
        cin >> h[i];
    }
    
    // Зчитування довжин, які необхідно відрізати від кожної ніжки
    for (int i = 0; i < 4; ++i) {
        cin >> r[i];
    }
    
    // Перевірка на коректність даних: якщо відрізають більше, ніж довжина ніжки, програма виводить "ERROR" і завершує роботу
    for (int i = 0; i < 4; ++i) {
        if (h[i] < r[i]) {
            cout << "ERROR\n";
            return 0;
        }   
    }

    bool flipped = false;

    for (int i = 0; i < 4; ++i) {
        // Відпилювання ніжок
        h[i] -= r[i];
        
        // Пошук мінімальної та максимальної висоти ніжок
        long long h_min = h[0];
        long long h_max = h[0];
        for (int j = 1; j < 4; ++j) {
            if (h[j] < h_min) h_min = h[j];
            if (h[j] > h_max) h_max = h[j];
        }
      
        // Якщо найдовша ніжка в два або більше рази більша за найменшу - стіл перевернувся
        if (h_max >= 2 * h_min) {
            flipped = true;
        }
    }

    bool all_equal = (h[0] == h[1] && h[1] == h[2] && h[2] == h[3]);
    bool not_zero = (h[0] > 0);

    // Якщо всі ніжки рівні, не нульові і стіл ніразу не перевертався — виводимо "YES", інакше - "NO"
    if (all_equal && not_zero && !flipped) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}
