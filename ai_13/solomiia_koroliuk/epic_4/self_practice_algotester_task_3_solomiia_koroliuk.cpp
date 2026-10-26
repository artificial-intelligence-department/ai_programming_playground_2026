/* Task 0077 - Інтерактивне число */

#include <iostream>

using namespace std;

int main(){

    int l = 1;
    int r = 1000000000;

    while (l <= r){
        int mid = (l + r) / 2;
        cout << mid << endl;

        string n;
        cin >> n;

        if (n == "=") break;
        else if (n == "<") l = mid + 1;
        else if (n == ">") r = mid - 1;

    }
    return 0;
}