#include <iostream>

using namespace std;

int main(){

    int n;
    cin >> n;

    int a[n];
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    if (n < 2) { cout << 0; return 0;}
    
    for(int i = 0; i < n; i++){
        for (int j = 0; j < n - 1 - i; j++){
            if (a[j] > a[j + 1]){
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }

    int fatigue1 = a[n - 2] - a[0]; // викидаємо найбільший a[n - 1]
    int fatigue2 = a[n - 1] - a[1]; // викидаємо найменший елемент a[0]
    
    int min_fatigue;
    if (fatigue1 < fatigue2) min_fatigue = fatigue1;
    else min_fatigue = fatigue2;

    cout << min_fatigue << endl;

    return 0;
}

