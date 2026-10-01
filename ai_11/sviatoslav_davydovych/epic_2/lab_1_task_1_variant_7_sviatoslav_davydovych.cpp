/* Лабораторна робота N1(task 1)
Автор: Давидович Святослав
Група: ШІ-11
 */
#include <iostream>
#include <iomanip>
// не використовуємо <cmath>, оскільки операція pow повільна, а степені невеликі

using namespace std;

double calculate_double(double a, double b){
    double c,d,e,f,g,h,i,j;

    c = (a-b)*(a-b)*(a-b);
    d = a*a*a;
    e = c - d;
    f = b*b*b;
    g = 3*a*b*b;
    h = 3*a*a*b;
    i = f-g-h;
    j = e/i;

    return j;
}

float calculate_float(float a, float b){
    float c,d,e,f,g,h,i,j;

    c = (a-b)*(a-b)*(a-b);
    d = a*a*a;
    e = c - d;
    f = b*b*b;
    g = 3*a*b*b;
    h = 3*a*a*b;
    i = f-g-h;
    j = e/i;

    return j;
}
int main() {
    // записуємо запропоновані значення параметрів
    const double a = 1000, b = 0.0001;

    // при передачі, обчисленні та записі відбудеться неявне перетворення типів, що впливає на результат
    double result1 = calculate_double(a,b), result2 = calculate_float(a,b);

    // встановлюємо точність 10 знаків після коми(цілком достатньо для порівняння)
    cout << fixed << setprecision(10); 
    cout << "результат обчислення виразу:" << endl;
    cout << "при використанні типу даних double: " << result1 << endl;
    cout << "при використанні типу даних float: " << result2 << endl;
    cout << "пояснення: відмінність результатів зумовлена різною точністю(знаків після коми) типів даних" << endl;

    return 0;
}