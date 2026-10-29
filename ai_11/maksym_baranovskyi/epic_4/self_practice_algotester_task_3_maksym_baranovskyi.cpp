//Перехід дороги
//https://algotester.com/uk/ArchiveProblem/DisplayWithEditor/40670

#include <iostream>
using namespace std;

int main(){

    int n;
    cin >> n;

    int *arr = new int[n];
    int counter = 0;
    for(int *i = arr; i < arr + n; i++){
        cin >> *i;
        if((i > arr && (*(i-1) % 2 == 0 && *i % 2 != 0) || (*(i-1) % 2 != 0 && *i % 2 == 0))){
            counter++;
        }
    }
    delete[] arr;
    arr = nullptr;
    cout << counter;

    return 0;
}