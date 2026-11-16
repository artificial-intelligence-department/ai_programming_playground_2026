/*
1v3 Lab
Name: Onyshko Daniel
Group: ШІ-14
*/



#include <iostream>
using namespace std;

int main() {

    
    long long cub_c, cub_p = 0; // Створюється поточне та минуле число
    cin >> cub_p; 

      if(cub_p <= 0) {
        cout << "ERROR" ; return 0; // Перевірка чи дорівнює нулю, якщо так то завершуж роботу
    }

    for (int i = 1; i<5; i++){ // Ну тут вже цикл виконується 4 рази (зчитується число )

        cin >> cub_c;
        if(cub_p < cub_c){
             cout << "LOSS" ; return 0;
        }
        if(cub_c <= 0){
             cout << "ERROR" ; return 0;
        }

        cub_p = cub_c;
        
    }
    
    

    cout << "WIN";

    return 0;
}