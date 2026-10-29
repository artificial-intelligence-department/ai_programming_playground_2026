/*Epic 4 - Халява
Франчук Андрій
Ші - 14*/
#include <iostream>

using namespace std;

int main(){
    int n;
    cin >> n;

    int *a = new int[n];

    for(int i = 0; i < n; i++){
        cin >> *(a+i);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (*(a+j) > *(a+j+1)){
                int temp = *(a+j);
                *(a+j) = *(a+j+1);
                *(a+j+1) = temp;
            }
        }
    }

    int counter = 1;
    for (int i = 1; i < n; i++) {
        if (*(a+i) != *(a+i-1)) counter++;
    }

    cout << counter << endl;
}