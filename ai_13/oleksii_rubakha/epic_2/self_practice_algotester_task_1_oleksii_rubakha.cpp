
/*
Хелловін, Рубаха Олексій, ШІ-13
*/

#include <iostream>

using namespace std;

int minCount(int count){
    int min;
    for (int i = 0; i < count; i++){
        int price;
        cin >> price;

        // Для першої цукерки встановлюємо початковий мінімум
        if (i == 0)
            min = price;
        // Для наступних перевіряємо, чи ця цукерка дешевша
        else if (price < min)
            min = price;
    }
    return min;
}

int main(){
    // Кількість цукерок у мішку Зеника та Марічки
    int n, m;
    cin >> n >> m;

    // Знаходимо найдешевшу цукерку Зеника та Марічки
    int minZenyk = minCount(n);
    int minMarichka = minCount(m);

    // Подарунок складається з найдешевшої цукерки
    // Зеника та найдешевшої цукерки Марічки
    cout << minZenyk + minMarichka;

    return 0;
}