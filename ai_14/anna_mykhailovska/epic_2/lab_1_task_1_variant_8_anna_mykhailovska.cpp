/*
    Lab 1 Task 1
    Михайловська Анна
    ШІ-14
    Варіант 8
*/
#include <iostream>  
#include <math.h>    
using namespace std;

int main() {
    
    float af = 100.0f, bf = 0.001f; // Задані значення a і b типу float з умови

    float sumF = af + bf;
    float sum4F = pow(sumF, 4.0f);                    // (a + b)^4
    float a4F = pow(af, 4.0f);                       // a^4
    float a3bF = 4.0f * pow(af, 3.0f) * bf;         // 4a^3b
    float a2b2F = 6.0f * pow(af, 2.0f) * pow(bf, 2.0f); // 6a^2b^2
    float ab3F = 4.0f * af * pow(bf, 3.0f);         // 4ab^3
    float b4F = pow(bf, 4.0f);                       // b^4
    
    // Обчислюємо чисельник, знаменник і результат для float
    float chysF = sum4F - (a4F + a3bF + a2b2F);
    float znamF = ab3F + b4F;
    float resultF = chysF / znamF;


    double ad = 100.0, bd = 0.001;  // Задані значення a і b типу double з умови

    double sumD = ad + bd;
    double sum4D = pow(sumD, 4);                   // (a + b)^4
    double a4D = pow(ad, 4);                       // a^4
    double a3bD = 4 * pow(ad, 3) * bd;          // 4a^3b
    double a2b2D = 6 * pow(ad, 2) * pow(bd, 2); // 6a^2b^2
    double ab3D = 4 * ad * pow(bd, 3);          // 4ab^3
    double b4D = pow(bd, 4);                       // b^4

    // Обчислюємо чисельник, знаменник і результат для double
    double chysD = sum4D - (a4D + a3bD + a2b2D);
    double znamD = ab3D + b4D;
    double resultD = chysD / znamD;

    cout << "float:  " << resultF << '\n';
    cout << "double: " << resultD << '\n';

    return 0; 
}