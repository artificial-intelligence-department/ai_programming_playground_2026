/*
Task: self_practice_algotester_task_1 (Марічка і печиво)
Name: Vasyl Yakubovskyi
Group: ШІ-14(II)
*/


#include <iostream>


using namespace std ;

int main(){

    long long n = 0;
    cin >> n;


    long long nCookies [n] = {0};
    long long sum = 0;

    for (long long i = 0; i < n; i++){
        cin >> nCookies[i];
        if(nCookies[i] <= 0) return  1;
        sum += --nCookies[i];
    }

    cout << sum << endl;

    return 0;
}