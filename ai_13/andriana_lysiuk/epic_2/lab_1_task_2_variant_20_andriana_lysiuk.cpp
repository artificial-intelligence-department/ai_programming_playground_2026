/* Lab 1 task 2
Лисюк Андріана
ШІ-13
Варіант 20 */

#include <iostream>
#include <cmath>

using namespace std;
int n = 3;
int m = 1;
int result = 0;
bool result_bool;
int main (){
    cout << "-------1---------" << endl;
    cout << "N: " << n << endl;
    cout << "M: " << m << endl;
    /* Спочатку виконується префіксний інкремент ++n : n збільшується на 1, тепер n = 4,
    Потім обчислюється різниця: m - 4 = 1 - 4 = -3 */
    result = m - ++n;
    cout << "Result:  " << result<< endl;

    cout << "-------2---------" << endl;
    n = 3;
    m = 1;
    /* Префіксний інкремент ++m збільшує m на 1, тепер m = 2
    Префіксний декремент --n зменшує n на 1, тепер n = 2
    Порівнюємо нові значення: 2 > 2 (хибно, тому результат 0) */
    result_bool = ++m > --n;
    cout << "Result: " << result_bool << endl;

    cout << "-------3---------" << endl;
    n = 3;
    m = 1;
    /*Префіксний декремент --n зменшує n на 1, тепер n = 2
    Префіксний інкремент ++m збільшує m на 1, тепер m = 2
    Порівнюємо нові значення: 2 < 2 (хибно, тому результат 0) */
    result_bool = --n < ++m;
    cout << "Result: " << result_bool << endl;

    return 0;
}
