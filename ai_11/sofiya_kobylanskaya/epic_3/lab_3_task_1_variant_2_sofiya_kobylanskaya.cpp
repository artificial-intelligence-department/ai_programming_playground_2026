/*
Epic 3
Lab_3_task_1
Кобилянська Софія ШІ-11 варіант 2
*/

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    const double PI = 3.14159265358979323846;
    double a = PI / 5.0;
    double b = 9.0 * PI / 5.0;
    int k = 10;
    double step = (b - a) / k;
    int n = 40;
    double eps = 0.0001;

    for (int i = 0; i <= k; i++)
    {
        double x = a + i * step;

        double Y = -log(abs(2.0 * sin(x / 2.0)));

        double SN = 0.0;
        for (int j = 1; j <= n; j++)
        {
            SN += cos(j * x) / j;
        }

        double SE = 0.0;
        int j = 1;
        double ak = cos(j * x) / j;
        while (abs(ak) >= eps)
        {
            SE += ak;
            j++;
            ak = cos(j * x) / j;
        }

        cout << "X = " << x << " SN = " << SN << " SE = " << SE << " Y = " << Y << endl;
    }

    return 0;
}