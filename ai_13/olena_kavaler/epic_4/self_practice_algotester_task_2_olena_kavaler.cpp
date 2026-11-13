
/*
Автор: Олена Кавалер
Група: ШІ-13
*/

#include <iostream>
using namespace std;

int main() {

    int n;
    cin >> n;

    int** arr = new int*[n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[n];
       
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
        }
    }

    int count = 0; // скільки клітинок стоять неправильно
    int num = 1; // яке число має стояти зараз

    // діагоналі з лівого краю n-1, ..., 0
    for (int startrow = n - 1; startrow >= 0; startrow--) {
        int i = startrow;
        int j = 0;
        while (i < n && j < n) {
            if (arr[i][j] != num) {
                count++;
            }
            num++;
            i++;
            j++;
        }
    }

    // діагоналі зверху 1, ..., n-1
    for (int startcol = 1; startcol < n; startcol++) {
        int i = 0;
        int j = startcol;
        while (i < n && j < n) {
            if (arr[i][j] != num) {
                count++;
            }
            num++;
            i++;
            j++;
        }
    }

    cout << count << endl;

    for (int i = 0; i < n; i++) {
        delete[] arr[i];
    }
    delete[] arr;

    return 0;
}