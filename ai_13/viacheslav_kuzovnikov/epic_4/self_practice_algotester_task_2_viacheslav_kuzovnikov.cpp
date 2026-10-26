/*
Найдовший зростаючий підмасив
Кузовніков В'ячеслав Євгенійович
ШІ-13
*/

#include <iostream>
using namespace std;
int main(){
    int size = 0 ;
    cin >> size;
    if (size < 1 || size > 100000){
        return 1;
    }

    int prev;
    cin >> prev; 
    if (prev < 1 || prev > 1000000000){
            return 1;
        }

    int max_len = 1;
    int current_len = 1; 

    for (int i = 1; i < size; i++) {
        int current;
        cin >> current; 
        if (current < 1 || current > 1000000000){
            return 1;
        }

        if (current > prev) {
            current_len++;
        } else {
            current_len = 1; 
        }

        if (current_len > max_len) {
            max_len = current_len;
        }

        prev = current; 
    }

    cout << max_len;

    return 0;
}