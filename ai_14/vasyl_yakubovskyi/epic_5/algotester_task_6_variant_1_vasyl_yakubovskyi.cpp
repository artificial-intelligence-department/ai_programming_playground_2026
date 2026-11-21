/*
Task 5 lab 6v1
Name: Vasyl Yakubovskyi
Group: ШІ-14(II)
*/

#include <iostream>
#include <cstring>  
#include <cctype> 

using namespace std;

void quickSort(char **a, int begin, int end, bool ascending = true) {
    if (begin >= end) return;

    int i = begin;
    int j = end;
    
    // Копіюємо центральне слово в окремий буфер pivot
    char pivot[12];
    strcpy(pivot, a[begin + (end - begin) / 2]);

    while (i <= j) {
        if (ascending) {
            while (strcmp(a[i], pivot) < 0) i++;
            while (strcmp(a[j], pivot) > 0) j--;
        } else {
            while (strcmp(a[i], pivot) > 0) i++;
            while (strcmp(a[j], pivot) < 0) j--;
        }

        if (i <= j) {
            char *temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    }

    if (begin < j) quickSort(a, begin, j, ascending);
    if (i < end) quickSort(a, i, end, ascending);
}

int main() {

    int n, k;

    cin >> n >> k;

    char **s = new char*[n];
    for (int i = 0; i < n; i++) {
        s[i] = new char[12];
    }

    char buf[12];
    for (int i = 0; i < n; i++) {
        cin >> buf;
        strcpy(s[i], buf);
        int len = strlen(s[i]);
        for (int j = 0; j < len; j++) {
            s[i][j] = tolower(s[i][j]);
        }
    }

    // Сортування слів за алфавітом
    quickSort(s, 0, n - 1);

    // Масив-прапорець для 26 літер англійського алфавіту (від 'a' до 'z')
    bool used[26] = {false};

    // Підрахунок однакових слів та збір їхніх букв
    int current_count = 1; 

    for (int i = 1; i <= n; i++) {
        if (i == n || strcmp(s[i], s[i - 1]) != 0) {
            if (current_count >= k) {
                int len = strlen(s[i - 1]);
                for (int j = 0; j < len; ++j) {
                    char letter = s[i - 1][j];
                    used[letter - 'a'] = true;
                }
            }
            current_count = 1;
        } else {
            current_count++;
        }
    }

    // Збираємо відмічені букви у зворотному порядку (від 'z' до 'a')
    char result[26];
    int m = 0; 

    for (int i = 25; i >= 0; --i) {
        if (used[i]) {
            result[m] = 'a' + i; 
            m++;
        }
    }

    // Вивід
    if (m == 0) {
        cout << "Empty!\n";
    } else {
        cout << m << "\n";
        for (int i = 0; i < m; ++i) {
            cout << result[i];
            if (i + 1 < m) cout << " "; 
        }
        cout << "\n";
    }

    // Звільняємо виділену пам'ять
    for (int i = 0; i < n; i++) {
        delete[] s[i];
    }
    delete[] s;

    return 0;
}