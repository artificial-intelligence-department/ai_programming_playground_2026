/*Epic 4 - Цікавий масив
Франчук Андрій
Ші - 14*/
#include <iostream>

using namespace std;

int main(){
    int n, S1 = 0, S2 =0;
    cin >> n;

    int *a = new int[n];

    for(int i = 0; i < n; i++){
        cin >> a[i];
        S1 += a[i];
    }

    for(int i = 0; i < n; i++){
        S2 += a[i];
        S1 -= a[i];
        if(S2 == S1){
            cout << "TAK";
            delete[] a;
            return 0;
        }
    }

    cout << "NI";

    delete[] a;
}