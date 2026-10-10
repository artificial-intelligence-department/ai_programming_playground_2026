#include <iostream>
using namespace std;

int main()
{
    int result = 0;
    int a = 0;
    cin >> a;
    int b[] = {500, 200, 100, 50, 20, 10, 5, 2, 1};
    for (int i = 0; i < 9; i++){
        int count = a/b[i]; // Рахую цілу частину 
        result += count; // Додаю до результату
        a -= count * b[i]; // Віднімаю від ціни, щоб отримати решту
    }
    cout << result << endl;
}