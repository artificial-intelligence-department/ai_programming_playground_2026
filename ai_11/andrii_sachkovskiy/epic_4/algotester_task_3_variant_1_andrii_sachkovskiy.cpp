/*
 * Задача: algotester_task_3_variant_1
 * Автор: Сачковський Андрій
 * Група: AI-11
*/
#include <iostream>

using namespace std;
/*
Користовач водить кілкьість рядків потом водить для кожного рядка слова задча порахувати
скільки слів є з # 
*/

char a[1001][43][43];   // рядок, слово, буква

int main() {
    int N;
    cin >> N ;

    //користовач водить слова 
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= 43; j++) {
            cin >> a[i][j];   
        }
    }



char simvol = '#';
int heshtegi = 0;
for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= 43; j++) {
        for (int k = 0; k < 43; k++) {
            
            if (a[i][j][k] == simvol && (k == 0 || a[i][j][k-1] != simvol)) {
                //первірка на те чи є символ у слові таокж первірка шоб ### рахувалися як одне заклинання 
                heshtegi++;
            }
        }
    }
}
cout << heshtegi;





    return 0;
}
