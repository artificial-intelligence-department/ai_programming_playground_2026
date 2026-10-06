/* Лабараторна робота 1, завдання 2 
   варіант 4 
   Човган Софія Ші 14
1) n++*m
2) n++<m
3) m-- >m*/


#include <iostream>

using namespace std; 
int main() {
    float n, m;
cout << "Enter the n definition: ";
cin >> n;
cout << "Enter the m definition: ";
cin >> m;
float res1;
bool res2, res3;

res1 = n ++* m; //1) n++*m оточне значення n множиться на m,
//    результат записується в res1, після цього n збільшується на 1
res2 = n ++< m; //2) n++<m початку поточне значення n порівнюється з m,
//    результат порівняння записується в res2,
//    після цього n збільшується на 1.

res3 = m --> m; //3) m-- >m поточне значення m використовується у виразі,
//    після цього m зменшується на 1.
//    > виконує порівняння значень.

cout << res1 << endl << res2 << endl << res3;
    return 0;
}