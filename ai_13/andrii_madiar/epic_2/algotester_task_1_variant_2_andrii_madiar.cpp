/*
algotester task 1, Мадяр Андрій, ШІ-13, варівнт 2
*/
#include <iostream>
//бібліотека щоб знайти максимум так як нам об'ясняли на лекції(використання INT_MIN INT_MAX)
#include <climits>

using namespace std;

int main() {
    //ввід змінних
    long long h[4];
    long long d[4];
    for (int i = 0; i < 4; i++) {
        cin >> h[i];
    }
    for (int i = 0; i < 4; i++) {
        cin >> d[i];
    }
    //створюю bool для перевірок
    bool hasError = false;
    bool flipped = false;
    //цикл для відпиляння ніжок
    for (int i = 0; i < 4; i++) {
        h[i] -= d[i];
        //перевірка чи довжина не стала від'ємною
        if (h[i] < 0) {
            hasError = true;
        }
        //цикл для знаходження теперішнього максимуму
        long long currMax = INT_MIN;
        for(int j = 0; j < 4; j++){
            if(currMax < h[j]) currMax = h[j]; 
        }
        //цикл для знаходження теперішнього мінімуму
        long long currMin = INT_MAX;
        for(int j = 0; j < 4; j++){
            if(currMin > h[j]) currMin = h[j]; 
        }
        //перевірка чи стіл не перевернувся
        if (currMax >= 2 * currMin) {
            flipped = true;
        }
    }
    //вивід помилки якщо виконалася умова цього виводу
    if (hasError) {
        cout << "ERROR" << endl;
        return 0;
    }
    //вивід YES якщо умови для цього виконалися(стіл не перевернувся та всі ніжки однакової довжини)
    if (!flipped && h[0] == h[1] && h[1] == h[2] && h[2] == h[3] && h[0] > 0) {
        cout << "YES" << endl;
    } 
    //вивід NO для всіх інших випадків
    else {
        cout << "NO" << endl;
    }

    return 0;
}
