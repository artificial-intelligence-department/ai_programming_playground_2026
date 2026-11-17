/*
    Задача: Алготестер. Лабораторна №4. Рішення без STL
    Автор: Ільницька Софія
    Група: ШІ-14
*/
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int N[100];
    int M[100];    
    int result[200]; 

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> N[i];
    }
    int m; 
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> M[i];
    }

    // Сортуємо обидва масиви, щоб відповідь виходила по зростанню
    sort(N, N + n);
    sort(M, M + m);

    int countN;       // яка це за рахунком копія числа у своєму масиві
    int countM;       // скільки разів це число є в іншому масиві
    int k;            // скільки чисел зараз лежить у result

    // N - M
    // Беремо копію з N, якщо для неї немає пари в M
    k = 0;
    for (int i = 0; i < n; i++) {
        countN = 0;
        countM = 0;

        // рахуємо, яка це за рахунком копія числа N[i] (від початку до позиції i)
        for (int j = 0; j <= i; j++) {
            if (N[i] == N[j]) {
                countN++;
            }
        }
        // рахуємо, скільки таких чисел є в усьому масиві M
        for (int j = 0; j < m; j++) {
            if (N[i] == M[j]) {
                countM++;
            }
        }

        // копій у N більше, ніж у M: ця копія без пари, тому йде в різницю
        if (countN > countM) {
            result[k] = N[i];
            k++;
        }
    }
    cout << k << endl;
    for (int i = 0; i < k; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
    cout << endl;

    // M - N 
    // Те саме, що блок 1, але ролі масивів поміняні
    k = 0;
    for (int i = 0; i < m; i++) {
        countM = 0;
        countN = 0;

        // яка це за рахунком копія числа M[i] у масиві M
        for (int j = 0; j <= i; j++) {
            if (M[i] == M[j]) {
                countM++;
            }
        }
        // скільки таких чисел є в усьому масиві N
        for (int j = 0; j < n; j++) {
            if (M[i] == N[j]) {
                countN++;
            }
        }

        // копія з M без пари в N: йде в різницю
        if (countM > countN) {
            result[k] = M[i];
            k++;
        }
    }
    cout << k << endl;
    for (int i = 0; i < k; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
    cout << endl;

    // Перетин
    // Беремо копію з N, якщо для неї є пара в M
    k = 0;
    for (int i = 0; i < n; i++) {
        countN = 0;
        countM = 0;

        // яка це за рахунком копія числа N[i] у масиві N
        for (int j = 0; j <= i; j++) {
            if (N[i] == N[j]) {
                countN++;
            }
        }
        // скільки таких чисел є в M
        for (int j = 0; j < m; j++) {
            if (N[i] == M[j]) {
                countM++;
            }
        }

        // пара є (умова обернена до блоку 1), то копія входить у перетин
        if (countN <= countM) {
            result[k] = N[i];
            k++;
        }
    }
    cout << k << endl;
    for (int i = 0; i < k; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
    cout << endl;

    // Об'єднання
    k = 0;
    // Кладемо в result весь масив N
    for (int i = 0; i < n; i++) {
        result[k] = N[i];
        k++;
    }
    // З M докидаємо тільки ті копії, яких не вистачає в N
    for (int i = 0; i < m; i++) {
        countM = 0;
        countN = 0;

        // яка це за рахунком копія числа M[i] у масиві M
        for (int j = 0; j <= i; j++) {
            if (M[i] == M[j]) {
                countM++;
            }
        }
        // скільки таких чисел є в N
        for (int j = 0; j < n; j++) {
            if (M[i] == N[j]) {
                countN++;
            }
        }

        // Якщо у N такої копії немає, то додаємо
        if (countM > countN) {
            result[k] = M[i];
            k++;
        }
    }
    // числа з M додавались у кінець, тому ставимо все по порядку
    sort(result, result + k);
    cout << k << endl;
    for (int i = 0; i < k; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
    cout << endl;

    // Симетрична різниця
    // Це блок 1 і блок 2, зліплені в один результат
    k = 0;
    // Копії з N без пари в M
    for (int i = 0; i < n; i++) {
        countN = 0;
        countM = 0;

        for (int j = 0; j <= i; j++) {
            if (N[i] == N[j]) {
                countN++;
            }
        }
        for (int j = 0; j < m; j++) {
            if (N[i] == M[j]) {
                countM++;
            }
        }

        if (countN > countM) {
            result[k] = N[i];
            k++;
        }
    }
    // Копії з M без пари в N (k не обнуляємо, дописуємо в кінець)
    for (int i = 0; i < m; i++) {
        countM = 0;
        countN = 0;

        for (int j = 0; j <= i; j++) {
            if (M[i] == M[j]) {
                countM++;
            }
        }
        for (int j = 0; j < n; j++) {
            if (M[i] == N[j]) {
                countN++;
            }
        }

        if (countM > countN) {
            result[k] = M[i];
            k++;
        }
    }
    // сортуємо, бо числа з M ідуть після чисел з N
    sort(result, result + k);
    cout << k << endl;
    for (int i = 0; i < k; i++) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}