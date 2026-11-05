// lab 4 task 1 variant 15 Andrii Chelyada

#include <iostream>
using namespace std;

int main(){
    int size = 0; // к-сть елементів у кільці зараз, змінюється при видаленні
    int K = 0;    // номер елемента з якого починаємо друк

    cout << "Введіть к-сть елементів: " << endl;
    cin >> size;
    if(size < 1){
        return 0;
    }

    // Динамічний масив рівно на size елементів
    int* arr = new int[size];

    cout << "Введіть елементи: " << endl;
    for (int* p = arr; p < arr + size; p++){
        cin >> *p;
    }

    cout << "Введіть номер початкового елемента К(від 1 до " << size << ")" << endl;
    cin >> K;
    if(K < 1 || K > size){
        delete[] arr;
        return 0;
    }

    // Вказівник на K-й елемент
    int* cur = arr + (K - 1);

    // Пункт 2: друк від K-го елемента по кільцю вліво
    for(int i = 0; i < size; i++){
        cout << *cur << " ";
        if(cur == arr){
            cur = arr + size - 1; // з першого переходимо на останній
        }
        else{
            cur--;
        }
    }
    cout << endl;

    // Пункт 3: видалення останнього та першого елементів
    if (size < 3){
        cout << "Замала к-сть елементів" << endl;
        delete[] arr;
        return 0;
    }
    size--; // видалили останній
    for(int* p = arr; p < arr + size - 1; p++){
        *p = *(p + 1); // зсуваємо все на одну коробку вліво
    }
    size--; // видалили перший

    // Після видалення K міг вийти за межі кільця
    if (K <= size){
        cur = arr + (K - 1);
    }
    else{ // Якщо K більше за новий size, починаємо з останнього елемента
        cout << "К вийшло за межі після видалення, беремо останній елемент" << endl;
        cur = arr + size - 1;
    }

    // Пункт 4: друк від K-го елемента по кільцю вправо
    for (int i = 0; i < size; i++){
        cout << *cur << " ";
        cur++;
        if(cur == arr + size){
            cur = arr; // з останнього переходимо на перший
        }
    }
    cout << endl;

    delete[] arr;
    return 0;
}