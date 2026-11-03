/*
Белаш Матвій ШІ-12
Завдання з алготестеру "Спекотнi днi пiнгвiнiв"
*/
#include <iostream>
using namespace std;

int main(){

    int l=0, w=0, u=0, d=0;
    cin >> l>> w >> u >> d;
    if(l > w || l > (u+d)){
        cout << "Forget about the cocktails, man!";
        return 0;
    }else{ 
        cout << "Three times Sex on the Beach, please!";
        return 0;
    }
}