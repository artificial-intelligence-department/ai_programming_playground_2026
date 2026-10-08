/*
Lab 1 task 1, Нагірний Назарій, ШІ-13, Варіант № 18
*/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

/*
Умова:
((a - b)^3 - a^3) / (b^3 - 3*a*b^2 - 3*a^2*b)
при a = 1000, b = 0.0001
Дії:
1. (a - b) = riznytsia
2. riznytsia ^ 3 = riznytsia_kub
3. a ^ 3 = a_kub
4. riznytsia_kub - a_kub = chiselnyk
5. b ^ 3 = znam1
6. 3 * a * b ^ 2 = znam2
7. 3 * a ^ 2 * b = znam3
8. znam1 - znam2 - znam3 = znamennyk
9. chiselnyk / znamennyk = rezultat
*/

int main()
{
    double a = 1000;
    double b = 0.0001;
    double riznytsia = a - b;
    double riznytsia_kub = pow(riznytsia, 3);
    double a_kub = pow(a, 3);
    double chiselnyk = riznytsia_kub - a_kub;
    double znam1 = pow(b, 3);
    double znam2 = 3 * a * pow(b, 2);
    double znam3 = 3 * pow(a, 2) * b;
    double znamennyk = znam1 - znam2 - znam3;
    double rezultatDouble = chiselnyk / znamennyk;


    float a2 = 1000.0f;
    float b2 = 0.0001f;
    float riznytsiaF = a2 - b2;
    float riznytsia_kubF = pow(riznytsiaF, 3);
    float a_kubF = pow(a2, 3);
    float chiselnykF = riznytsia_kubF - a_kubF;
    float znam1F = pow(b2, 3);
    float znam2F = 3 * a2 * pow(b2, 2);
    float znam3F = 3 * pow(a2, 2) * b2;
    float znamennykF = znam1F - znam2F - znam3F;
    float rezultatFloat = chiselnykF / znamennykF;

    cout << fixed << setprecision(15) << "Double: " 
    << rezultatDouble << endl << "Float:  " << rezultatFloat << endl;

    return 0;

}