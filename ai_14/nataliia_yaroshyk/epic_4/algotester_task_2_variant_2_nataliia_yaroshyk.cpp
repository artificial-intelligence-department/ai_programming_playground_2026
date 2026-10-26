/*  Algotester lab 2v2
    Ярошик Наталія
    ШІ-14 */
#include <iostream>
using namespace std;

int main(){
    int N;
    int a, b, c; // 3 числа, які треба видалити з масиву
    cin >> N;
    int* r = new int[N];
    for(int i = 0; i < N; i++){
        cin >> r[i];
    }
    cin >> a >> b >> c;

    int newSize = 0;
    for(int i = 0; i < N; i++){
        if(r[i] != a && r[i] != b && r[i] != c){
            newSize++;
        }
    }

    int* newR = new int[newSize];
    int newIndx = 0;

    // Видаляємо a, b, c з масиву

    for(int i = 0; i < N; i++){
        if(r[i] != a && r[i] != b && r[i] != c){
            newR[newIndx] = r[i];
            newIndx++;
        }
    }

    if(newSize < 1){
        newSize = 1;
    }

    cout << newSize - 1<< endl;

    for(int i = 0; i < newSize - 1; i++){
        cout << newR[i] + newR[i + 1] << " ";
    }

    delete[] r;
    delete[] newR;

    return 0;
}