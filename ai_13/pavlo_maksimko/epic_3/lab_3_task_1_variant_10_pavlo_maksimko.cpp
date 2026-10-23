/*Lab 3, Task 1, Variant 10
Максімко Павло - СШІ-13*/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
    //Точність та кількість є заданими константами за умовою
    const double EPSILON = 0.0001;
    const int n = 20;

    //Оскільки межі х задані, то вони є константами
    const double X_MAX = 1.0; 
    const double X_MIN = 0.1;
    
    //Для обрахування кроку ділимо різницю меж на кількість точок, яка є константою
    const int K = 10;

    //Для х одразу задаємо початкове значення, а у пізніше обраховуватимемо
    double x = X_MIN, y;
    
    //Оскільки крок обраховується константами, то й сам є константою, він незмінний
    const double STEP = (X_MAX - X_MIN) /  K;

    cout << "Загальна формула елемента: a[n] = cos(n * x) / n!" << endl;
    cout << "Отже, a[n + 1]/ a[n] = (cos((n + 1) * x) * n!) / ((n + 1)! * cos (n * x))" << endl;
    cout << "Звідси: a[n + 1] = (a[n] * cos((n + 1) * x)) / ((n + 1) * cos(n * x))" << endl;

    cout << "Значення: " << endl;
    int k = 1;
    while(x <= X_MAX)
    {
        //Задаємо початкові значення для обрахування рекурентним способом
        double a_N = cos(1 * x) / 1;
        double a_E = a_N;

        //Присвоюємо суму 1 (перший елемент) і елемента а, щоб пізніше не втратити перші два елементи в сумі
        double Sum_N = 1 + a_N;
        double Sum_E = 1 + a_E;

        y = exp(cos(x)) * cos(sin(x));
        
        for(int i = 1; i < n; i++)
        {
            //Обчислюємо елемент рекурентною формулою
            a_N = a_N * cos((i + 1) * x) / ((i + 1) * cos(i * x));
            Sum_N += a_N;
        }

        int j = 1;
        while(true)
        {
            a_E = a_E * cos((j + 1) * x) / ((j + 1) * cos(j * x));
            
            //Як тільки модуль елементу стане меншим за задану точність, то додавання до суми закінчиться
            if(fabs(a_E) < EPSILON) break;
            
            Sum_E += a_E;
            j++;
        }

        cout << fixed << setprecision(4) << "X = " << x << '\t' << "SumN = " << Sum_N << '\t' << "SumE = " << Sum_E << '\t' << "Y = " << y << endl;
 
        //Обчислюємо сумою мінімальної межі та кроку та його номеру, щоб уникнути накопичення в double і зберегти точність обчислень
        x = X_MIN + k * STEP;
        k++;
    }

    return 0;
}