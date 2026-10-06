/* Лабараторна робота 1, завдання 1 
   варіант 4 
   Човган Софія Ші 14*/

#include <iostream>
#include <math.h> 
using namespace std; 
int main() {
    float a, b;
    cout << "Enter the a definition: ";
    cin >> a;
    cout << "Enter the b definition: ";
    cin >> b;
     double a1, b1; //Double variant
    cout << "Enter the a1 definition: ";
    cin >> a1;
    cout << "Enter the b1 definition: ";
    cin >> b1;
    // Розбиваємо приклад (a + b)⌃3 - (а)⌃3 / 3ab⌃2 + b⌃3 + 3a⌃2b
    // #1 (a + b)⌃3
    float c, d;
    c = a + b;
    d =  pow(c, 3);
    // #2 (а)⌃3
    float e;
    e = pow(a, 3);
    // #3 (a + b)⌃3 - (а)⌃3 - обрахування чисельника
    float ch;
    ch = d - e;
    // #4 3ab⌃2
    float g;
    g = 3 * a * pow(b, 2);
    // #5 
    float h;
    h = pow(b, 3);
    // #6 3a⌃2b
    float i;
    i = 3 * pow(a, 2) * b;
    // #7 Збираємо знаменник
    float zn;
    zn = g + h + i;
    // #8 Результати
    float res1;
    res1 = ch/zn;
    
    // Ті ж дії для типу double
    // #1 (a + b)⌃3
    double c1, d1;
    c1 = a1 + b1;
    d1 =  pow(c1, 3);
    // #2 (а)⌃3
    double e1;
    e1 = pow(a1, 3);
    // #3 (a + b)⌃3 - (а)⌃3 - обрахування чисельника
    double ch1;
    ch1 = d1 - e1;
    // #4 3ab⌃2
    double g1;
    g1 = 3 * a1 * pow(b1, 2);
    // #5 
    double h1;
    h1 = pow(b1, 3);
    // #6 3a⌃2b
    double i1;
    i1 = 3 * pow(a1, 2) * b1;
    // #7 Збираємо знаменник
    double zn1;
    zn1 = g1 + h1 + i1;
    // #8 Результати
    double res2;
    res2 = ch1/zn1;
    cout << "Result1: " << res1 << endl;
    cout << "Result2: " << res2 << endl;
    return 0;
}