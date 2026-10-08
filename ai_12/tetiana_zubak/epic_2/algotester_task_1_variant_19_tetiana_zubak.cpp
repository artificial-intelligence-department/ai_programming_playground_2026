/* 
Лаборторна робота, завдання 1, варіант 19
Зубак Тетяна
ШІ-12
*/
#include <iostream>
#include <math.h>
#include <iomanip>
#include <locale>

using namespace std;

int main() {
    setlocale(LC_ALL, "uk_UA");
//перший блок
    double a, b;

    cout << "Введіть значення a: ";
    cin >> a;
    cout << "Введіть значення b: ";
    cin >> b;

    double one = pow(a + b, 4), two = pow(a, 4), three = 4 * pow(a, 3) * b, four = 6 * pow(a, 2) * pow(b, 2), five = 4 * a * pow(b, 3), six = pow(b, 4);

    double result1 =  (one - (two + three + four))/ (five + six);
    
    cout << endl;
    cout << "Для double:" << endl;
    cout << "Перша дія : (a + b)⁴ = " << one << endl;
    cout << "Друга дія : a⁴ = " << two << endl;
    cout << "Третя дія : 4a³b = " << three << endl;
    cout << "Четверта дія : 6a²b² = " << four << endl;
    cout << "Пятая дія : 4ab³ = " << five << endl;
    cout << "Шоста дія : b⁴ = " << six << endl;
    cout << "Результат: " << result1 << endl;

    //другий блок
    float a1 = a, b1 = b;
    float one1 = pow(a1 + b1, 4), two1 = pow(a1, 4), three1 = 4 * pow(a1, 3) * b1, four1 = 6 * pow(a1, 2) * pow(b1, 2), five1 = 4 * a1 * pow(b1, 3), six1 = pow(b1, 4);

    float result2 =  (one1 - (two1 + three1 + four1))/ (five1 + six1);

    cout << endl;
    cout << "Для float:" << endl;
    cout << "Перша дія : (a + b)⁴ = " << one1 << endl;
    cout << "Друга дія : a⁴ = " << two1 << endl;
    cout << "Третя дія : 4a³b = " << three1 << endl;
    cout << "Четверта дія : 6a²b² = " << four1 << endl;
    cout << "Пятая дія : 4ab³ = " << five1 << endl;
    cout << "Шоста дія : b⁴ = " << six1 << endl;
    cout << "Результат: " << result2 << endl;

//третій блок
    double dif = result1 - result2;
    int per = (dif * 100)/ result1;
    cout << endl;
    cout << "Результати відрізняються на " << dif << "(приблизно на" << per << "%)" << endl;

return 0;
}