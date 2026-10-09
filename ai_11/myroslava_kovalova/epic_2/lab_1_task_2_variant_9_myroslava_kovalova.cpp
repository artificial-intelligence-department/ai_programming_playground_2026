/* Лабораторна робота 1, завдання 2
Ковальова Мирослава
ШІ-11 */

#include <iostream>

using namespace std;

int main(){

    int n_input, m_input, n,m, res1;
    bool res2, res3;

    cout<<"Введіть цільночисельні значення n та m через пробіл: ";
    cin>>n_input>>m_input;

    //перед кожним обчисленням виразу надаємо n та m початкові значення введенні користувачем
    n = n_input;
    m = m_input;
    res1 = ++n*++m;
    cout<<"Результат виразу ++n*++m: "<<res1<<endl;
    cout<<"Значення після виконання операцій: n = "<<n<<" m = "<<m<<endl;

    n = n_input;
    m = m_input;
    res2 = m++<n;
    cout<<"Результат виразу m++<n: "<<res2<<endl;
    cout<<"Значення після виконання операцій: n = "<<n<<" m = "<<m<<endl;


    n = n_input;
    m = m_input;
    res3 = n++>m;
    cout<<"Результат виразу n++>m: "<<res2<<endl;
    cout<<"Значення після виконання операцій: n = "<<n<<" m = "<<m<<endl;


    return 0;
}