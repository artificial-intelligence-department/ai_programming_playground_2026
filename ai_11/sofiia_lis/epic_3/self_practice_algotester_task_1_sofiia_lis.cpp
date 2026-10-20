/* 
Епік 3. self practice: Algotester, задача "Sorting"
Авторка: Софія Ліс
Група: ші-11
*/

#include <iostream>

using namespace std;

int main() {
    int a[10000];
    int n = 0;
    while (n < 10000 && cin >> a[n]) {
        n++;
    } 
    
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(a[i] > a[j]) {
                int jc = a[i];
                a[i] = a[j];
                a[j] = jc;
            }
        }
    }
    for(int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }

    return 0;
}
