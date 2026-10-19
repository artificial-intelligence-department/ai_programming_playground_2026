/*lab2 task1
Artem Mnikh
AI_14
*/
#include <iostream>
using namespace std;

double calculateSumOfProgression(double a, int n = 1)
{
    const double EPSILON = 0.0001;
    static double sum = 0.0;
    if (a < EPSILON) return sum;
    sum += a;
    return (calculateSumOfProgression(a * (3 * n - 2) * 1.0 / (3 * n + 4), n + 1));
}

int main()
{
    double first_element = 0.25;
    cout << "Сума послідовності з точністю до 0.0001:" << endl;
    cout << calculateSumOfProgression(first_element) << endl;
    return 0;
}
