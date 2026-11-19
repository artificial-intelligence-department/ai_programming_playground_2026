/*
Algotester Лабораторна робота №6, Завдання №4, Варіант №1.
Цебуля Вадим
ШІ-12
*/
#include <iostream>
#include <string>

using namespace std;

const int MAX_N = 100001;
string words[MAX_N];  

// Переведення слова в нижній регістр через арифметику над кодами
void toLower(string &s){
        for (int i = 0; i < (int)s.length(); i++){
                if (s[i] >= 'A' && s[i] <= 'Z'){
                        s[i] = s[i] + 32;
                }
        }
}

// Швидке сортування масиву words (опорний елемент — середній)
void quickSort(int lo, int hi){
        if (lo >= hi) return;

        string pivot = words[(lo + hi) / 2];
        int i = lo, j = hi;

        while (i <= j){
                while (words[i] < pivot) i++;
                while (words[j] > pivot) j--;
                if (i <= j){
                        string temp = words[i];
                        words[i] = words[j];
                        words[j] = temp;
                        i++;
                        j--;
                }
        }

        quickSort(lo, j);
        quickSort(i, hi);
}

int main(){
        int n, k;
        cin >> n >> k;

        for (int i = 0; i < n; i++){
                cin >> words[i];
                toLower(words[i]);   // великі й малі літери вважаються однаковими
        }

        quickSort(0, n - 1);

        // Після сортування однакові слова стоять поруч — рахуємо групи
        bool used[26] = {};
        int i = 0;
        while (i < n){
                int j = i;
                while (j < n && words[j] == words[i]) j++;   // межа групи однакових слів
                if (j - i >= k){
                        for (int c = 0; c < (int)words[i].length(); c++){
                                used[words[i][c] - 'a'] = true;
                        }
                }
                i = j;
        }

        int m = 0;
        for (int idx = 0; idx < 26; idx++){
                if (used[idx]) m++;
        }

        if (m == 0){
                cout << "Empty!" << endl;
                return 0;
        }

        // Вивід від останньої літери алфавіту до першої
        cout << m << endl;
        bool first = true;
        for (int idx = 25; idx >= 0; idx--){
                if (used[idx]){
                        if (!first) cout << " ";
                        cout << char('a' + idx);
                        first = false;
                }
        }
        cout << endl;

        return 0;
}