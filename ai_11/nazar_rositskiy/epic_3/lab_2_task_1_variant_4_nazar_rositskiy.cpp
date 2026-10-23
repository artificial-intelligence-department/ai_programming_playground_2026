#include <iostream>

int main(){
    //Ініціалізація змінних
    int sum = 0;

    //Цикл для знаходження суми
    for(int i = 21; i < 100; i=i+3){
        sum = sum + i;
    }
    //Вивід результатів
    std::cout << "Знайти суму цілих додатніх чисел, більших 20, менших 100 і кратних 3:" << std::endl; 
    std::cout << sum << std::endl;
}