/*
 * Задача: algotester_task_2_variant_3
 * Автор: Сачковський Андрій
 * Група: AI-11
*/
#include <iostream>
using namespace std;
/*є масив 1 дрон займає крайне пложення ліве 2 крайнє парве залежності від цифри вони пересовуються на n 
кроків треба визначити де вони зустрінуться
*/

int main() {
    //користовач водить різні значення 

    int n;
    cin >> n;

    int a[1001];
    for (int i = 1; i <= n; i++) {
        // число має бути від 1 до 5, інакше просимо ввести ще раз
        do {
            cin >> a[i];
        } while (a[i] < 1 || a[i] > 5);
    }

    // логіка дронів

int l = 1, r = n; 
int f, g;
do {
    // перевірка (і до першого ходу теж)
    if ( l == r){
        cout<<l<<" "<<r<<endl<<"Collision";
        break;
    }
    else if (l > r){
        cout<<l<<" "<<r<<endl<<"Miss";
        break;
    }
    else if (r == l + 1){
        cout<<l<<" "<<r<<endl<<"Stopped";
        break;
    }

    f = a[l];
    g = a[r];

    l += f;
    r -= g;
}
while (true);

    return 0;
}