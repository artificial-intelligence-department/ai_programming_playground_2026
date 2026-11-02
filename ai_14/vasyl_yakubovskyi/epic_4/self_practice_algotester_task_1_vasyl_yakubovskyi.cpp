/*
Task: self_practice_algotester_task_1 (Веселі каруселі)
Name: Vasyl Yakubovskyi
Group: ШІ-14(II)
*/


#include <iostream>


using namespace std;


int main(){
    int n, k;
    cin >> k >> n;
    if(k < 1 || k > 100) return 0;
    if(n < 1 || n > 100) return 0;

    int a[n] = {0};
    for(int i = 0; i < n; i++){
        cin >> a[i];
        if(a[i] < 1 || a[i] > 100) return 0;
    }

    for(int i = 1; i < n; i++){

        int temp = a[i];
        int j = i - 1;
        while(j >= 0 && a[j] > temp){
            a[j+1] = a[j];

            j--;
        }

        a[j+1] = temp;
    }
    int count = 0;
    int sum = 0;

    for(int i = 0; i < n; i++){
         sum +=a[i];
        if(sum <= k){
            count ++;
        }else{
            break;
        }
    }

    cout << count << endl;


    return 0;
}