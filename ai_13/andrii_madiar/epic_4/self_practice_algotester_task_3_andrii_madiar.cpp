/*
self-practice algotester task 3 , Андрій Мадяр
*/
#include <iostream>
using namespace std;
int main(){
    int n;
    cin >> n;
    int *arr = new int[n];
    for(int i = 0; i<n; i++){
        cin >> arr[i];
    }
    bool exist = false;
    for(int k = 0; k<n; k++){
        int sum1 = 0, sum2 = 0;
        for(int i = 0; i<=k; i++){//сума всік елементів від 1 до k-го включно
            sum1+=arr[i];
        }
        for(int j = n-1; j>k; j--){//сума від останнього елемента до k-го
            sum2+=arr[j];
        }
        if(sum1==sum2)exist = true;
    }
    (exist) ? (cout << "TAK") : (cout << "NI");//тернарні не така і погана штука якщо писати лінь
    return 0;
}