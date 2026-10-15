/*Epic 3 - Літня школа
Франчук Андрій
Ші - 14*/

#include <iostream>

using namespace std;

int main(){
    int n, k;
    cin >> n >> k;

    int a[k];
    for (int i = 0; i < k; i++){
        a[i] = 0;
    }

    if((k > n) || (n > 3*k)){
        cout << "Impossible";
        return 0;
    }

    int i = n;
    while(i > 0){
        for(int j = 0; j < k; j++){
            a[j] += 1;
            i -= 1;
            if(i <= 0){
                break;
            }
        }
    }

    for (int i = 0; i < k; i++){
        cout << a[i] << " ";
    }
    return 0;
    
}