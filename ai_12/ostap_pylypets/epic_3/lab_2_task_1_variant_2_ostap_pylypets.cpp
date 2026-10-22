/*
Лабораторна робота 2, завдання 1, варіант 2
Пилипець Остап ШІ-12
*/
#include <iostream>

int main(){
    int result = 0;
    for(int i = 0; i<100; i++){
        if(i%2 == 0)result += i;
    }
    std::cout << "Result: " << result << std::endl;
    return 0;
}