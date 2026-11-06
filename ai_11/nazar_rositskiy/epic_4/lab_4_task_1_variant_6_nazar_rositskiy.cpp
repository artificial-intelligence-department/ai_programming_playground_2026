#include <iostream>
#include <cstdlib>

using namespace std;



int main(){

    int n,a,b;

    cout << "Введіть бажану довжину масиву ";
    cin >> n;

    cout << "Введіть межі випадкових чисел ";
    cin >> a >> b;

    int arr[100];
    for(int i = 0; i < n; i++){
        arr[i] = a + rand() % (b - a + 1);
        cout << arr[i] << " ";
    }
    cout << endl;

    int del;
    cout << "Введіть номер елемента, що необхідно видалити ";
    cin >> del;

    for(int i = del - 1; i < n - 1; i++){
        arr[i] = arr[i + 1];
    }
    n--;

    int parne;
    bool finded = 0;
    for(int i = 0; i < n; i++){
        if(arr[i] % 2 == 0){
            parne = i;
            finded = 1;
            break;
        }
    }

    if(finded) {

        for(int i = n; i > parne + 1; i--){
            arr[i] = arr[i - 1];
        }
        
        arr[parne + 1] = arr[parne] + 2;
        n++;

    }

    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }

}