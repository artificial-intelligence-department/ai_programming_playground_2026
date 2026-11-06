/*
Algotester lab 2
Лисюк Андріана
ШІ-13
Варіант 3
*/

#include <iostream>

using namespace std;

int main(){
    int N;
    cin >> N;
    int array[N];
    for(int i = 0; i < N; i++)
        cin >> array[i];

    int L = 0;
    int R = N - 1;
    if(L == R){
        cout << L + 1 << "  " << R + 1 << endl;
        cout << "Collision";
        return 0;
    }
    if(L + 1 == R){
        cout << L + 1 << "  " << R + 1 << endl;
        cout << "Stopped";
        return 0;
    }

    while (L < R){
        L += array[L];
        R -= array[R];
    if(L == R){
        cout << L + 1 << "  " << R + 1 << endl;
        cout << "Collision";
        break;
    }
    if(L > R){
        cout << L + 1 << "  " << R + 1 << endl;
        cout << "Miss";
        break;
    }
    if(L + 1 == R){
        cout << L + 1 << "  " << R + 1 << endl;
        cout << "Stopped";
        break;
    }
}
        return 0;
}