#include <iostream>
using namespace std;


int main(){

    const int n_element = 100;
    int array_A[n_element]; 
    int n_moment = 0;
    int plus_minus = 0;
    char choice; 

    start: 

    cout << n_moment << "/" << n_element << " елементів масиву" << endl;
    
    plus:
    cout << "Скільки ви хочете додати елементів: ";   //вводимо скільки хочемо додати
    cin >> plus_minus;
    if(plus_minus > (n_element - n_moment)){
        cout << "Ви ввели забагато елементів. Додамо максимальну кількість елементів, що ще лишилися для цього масиву" << endl;
        plus_minus = n_element - n_moment;
    }
    if(cin.fail() || plus_minus < 0){
        cout << "Ви ввели недопустиме значення. Спробуйте ще раз." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        goto plus;
    }
    if(plus_minus == 0){
        cout << "A = { ";
        for(int j =0; j <n_moment; j++){
            cout << *(array_A + j) << " ";
        }
        cout << "}" << endl;
    }
 
    for(int i = 1; i <= plus_minus; i++){    //покроково додаємо елементи
        enter_plus:
        cout << "Введіть новий елемент масиву A: ";
        cin >> *(array_A + n_moment);
        if(cin.fail()){
            cout << "Ви ввели недопустиме значення. Спробуйте ще раз." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            goto enter_plus;
        }
        cout << "Додано: " << *(array_A + n_moment)  << endl;
        n_moment++;
        cout << "A = { ";
        for(int j =0; j <n_moment; j++){
            cout << *(array_A + j) << " ";
        }
        cout << "}" << endl;
    }
    plus_minus = 0;


    minus:  
    cout << "Скільки ви хочете відняти елементів: "; //вводимо скільки хочемо відняти
    cin >> plus_minus;
    if(plus_minus > n_moment){
        cout << "Ви хочете відняти більше ніж на даний момент є. Віднімемо всі елементи" << endl;
    }
    if(cin.fail() || plus_minus < 0){
        cout << "Ви ввели недопустиме значення. Спробуйте ще раз." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        goto minus;
    }
    if(plus_minus == 0){
        cout << "A = { ";
        for(int j =0; j <n_moment; j++){
            cout << *(array_A + j) << " ";
        }
        cout << "}" << endl;
    }
 

    for(int i = 1; i <= plus_minus; i++){    //покроково віднімаємо елементи
        if(n_moment == 0) break;
        cout << "Знято: " << *(array_A + n_moment - 1)  << endl;
        n_moment--;
        cout << "A = { ";
        for(int j =0; j <n_moment; j++){
            cout << *(array_A + j) << " ";
        }
        cout << "}" << endl;
    }

   
    choice:
    cout << "Хочете ще раз? (y/n): ";
    cin >>  choice;

    switch(choice){

        case 'y': 
        goto start;
        break;

        case 'n':
        return 0;

        default: 
        cout << "Не припустиме значення, спробуйте ще раз" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        goto choice;

    }
   
    return 0;   
}
