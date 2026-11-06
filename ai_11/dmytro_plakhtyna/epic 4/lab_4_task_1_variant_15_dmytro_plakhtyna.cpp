#include <iostream>
using namespace std;

int main()
{
    int nums[100];     // самі числа
    int rightOf[100];  // rightOf[i] - номер сусіда справа
    int leftOf[100];   // leftOf[i] - номер сусіда зліва
    int n, k;

    cout << "Скільки чисел (від 3 до 100)? ";
    cin >> n;
    while (n < 3 || n > 100)
    {
        cout << "Неправильно, введіть ще раз: ";
        cin >> n;
    }

    for (int i = 0; i < n; i++)
    {
        cout << "Число " << i + 1 << ": ";
        cin >> nums[i];
    }

    // робимо кільце
    for (int i = 0; i < n; i++)
    {
        rightOf[i] = i + 1;
        leftOf[i] = i - 1;
    }
    rightOf[n - 1] = 0;  // справа від останнього - перший
    leftOf[0] = n - 1;   // зліва від першого - останній

    int first = 0;       // номер першого елемента
    int ringSize = n;    // скільки елементів у кільці

    //друк від K-го вліво
    cout << "Введіть K (від 1 до " << ringSize << "): ";
    cin >> k;
    while (k < 1 || k > ringSize)
    {
        cout << "Неправильно, введіть ще раз: ";
        cin >> k;
    }

    int cur = first;
    for (int i = 1; i < k; i++)
        cur = rightOf[cur];  // доходимо до K-го

    cout << "По кільцю вліво: ";
    for (int i = 0; i < ringSize; i++)
    {
        cout << nums[cur] << " ";
        cur = leftOf[cur];   // крок вліво
    }
    cout << endl;

    //видаляємо першого
    int last = leftOf[first];
    int second = rightOf[first];
    rightOf[last] = second;  // останній тепер дивиться на другого
    leftOf[second] = last;   // другий тепер дивиться на останнього
    first = second;          // другий став першим
    ringSize--;

    // видаляємо останнього
    last = leftOf[first];
    int beforeLast = leftOf[last];
    rightOf[beforeLast] = first;
    leftOf[first] = beforeLast;
    ringSize--;

    cout << "Перший і останній елементи видалено." << endl;

    // друк від K-го вправо
    cout << "Введіть K (від 1 до " << ringSize << "): ";
    cin >> k;
    while (k < 1 || k > ringSize)
    {
        cout << "Неправильно, введіть ще раз: ";
        cin >> k;
    }

    cur = first;
    for (int i = 1; i < k; i++)
        cur = rightOf[cur];

    cout << "По кільцю вправо: ";
    for (int i = 0; i < ringSize; i++)
    {
        cout << nums[cur] << " ";
        cur = rightOf[cur];  // крок вправо
    }
    cout << endl;

    return 0;
}