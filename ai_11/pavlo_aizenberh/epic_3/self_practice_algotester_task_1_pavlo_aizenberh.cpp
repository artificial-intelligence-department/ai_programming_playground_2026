//Задача 0521 - "Євро 2012"
#include <iostream>
using namespace std;

int main(){
    int sum = 0;
    int girls[4] = {0};
    for (int i = 0; i < 4; i++){
        cin >> girls[i];
        sum += girls[i];
        if (girls[i] == 0){
            continue;
        }
    }
    cout << sum << endl;
}