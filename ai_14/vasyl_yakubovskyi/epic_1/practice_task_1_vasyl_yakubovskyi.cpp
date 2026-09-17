#include <iostream> //Бібліотека для вводу 

using namespace std;
int main() {
    setlocale(LC_ALL, "uk_UA");
    cout << "Hello world!\n" << std::endl; // команда для виводу у консоль
    cout << "Як справи?\n";

    int num1 = 0; 
    std::cout << "Введіть число: ";
    std::cin >> num1;
    bool imhappy = true;

    if (num1 < 5 || imhappy)
    {
        std::cout << "number smaller than five" << std::endl;
    }else
        std::cout << "discorrect number" << std::endl;
    
    std::cout << "REsult - ";
    
    std::cout << num1 << std::endl;



    return 0;
}