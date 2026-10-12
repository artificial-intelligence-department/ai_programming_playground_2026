/*Задача №0182 "Зуби"*/
#include <iostream>
using namespace std;
int main() {
    int n;
    long long k;
    cin >> n >> k;
    //максимальна кількість значень масиву - межа n
    long long a[100000];
    //
    int CurrentCount = 0, BestCount = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        //Порівнюємо коеф. загостреності зуба з межою загостреності
        if (a[i] >= k) {
            //лічильник загострених зубів підряд
            CurrentCount++;
            if (CurrentCount > BestCount) BestCount= CurrentCount;
        } else {
            CurrentCount = 0;
        }
    }
    cout << BestCount << endl;
    return 0;
}