#include <iostream>
using namespace std;

int main()
{
    long long a[5] = {0};

    for (int i = 0; i < 5; i++){
        cin >> a[i];
    }

    int win = 1; //Змінна для підрахування значень, які підходять

    //цикл проходить 4 рази по заданним значенням, а на 5 виводить підтверджує виграш
    for (int i = 0; i < 5; i++){
        if (a[i] <= 0){
            cout << "ERROR" << endl;
        } else if (i < 4 && a[i] >= a[1 + i]){ // i < 4, щоб не вийти за межі масиву
            win++;
        } else if (i < 4 && a[i] < a[1 + i]){
            cout << "LOSS" << endl;
            break;
        } else if (i == 4 && win == 5){
            cout << "WIN" << endl;
        }
    }
    return 0;
}