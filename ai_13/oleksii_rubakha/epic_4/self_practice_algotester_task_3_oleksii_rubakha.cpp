
/* 
    Найбільша зростаючий підмасив
    Олексій Рубаха
    ШІ-13
*/

#include <iostream>

int main(){

    int n;
    std::cin >> n;

    int prev, curr;
    std::cin >> prev;

    int count = 1;
    int max = 1;

    for (int i = 1; i < n; i++){
        std::cin >> curr;

        if (curr > prev){
            count++;
        }else{
            count = 1;
        }

        if (count > max){
            max = count;
        }

        prev = curr;
    }

    std::cout << max;

    return 0;
}