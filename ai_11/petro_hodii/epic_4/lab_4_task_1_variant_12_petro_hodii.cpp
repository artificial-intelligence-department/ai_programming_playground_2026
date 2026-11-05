#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){
    srand(time(nullptr));
    const int N = 100;
    int a[N];

    int len;
    cout << "Введіть довжину масиву(не більше 100):";
    cin >> len;
    if(cin.fail() || len < 1 || len > 100){
        cout << "Помилка! Ви ввели неправильну довжину масиву." << endl;
        return 1;
    }

    cout << "Початковий масив: ";
    for(int i = 0; i < len; i++){
        a[i] = rand() % 100;
        cout << a[i] << " ";
    }
    cout << endl;

    int minInd = 0;
    int maxInd = 0;
    int sum = 0;
    for(int i = 0; i < len; i++){
        if(a[i] < a[minInd]){
            minInd = i;
        }
        if(a[i] > a[maxInd]){
            maxInd = i;
        }
        sum += a[i];
    }
    int temp = a[minInd];
    a[minInd] = a[maxInd];
    a[maxInd] = temp;

    cout << "Масив після зміни місцями найбільшого і найменшого елемента: ";
    for(int i = 0; i < len; i++){
        cout << a[i] << " ";
    }
    cout << endl;

    double mean = double(sum)/len;
    int last = -1;
    for(int i = 0; i < len; i++){
        if(double(a[i]) < 1.1*mean){
            last++;
            int temp = a[i];
            a[i] = a[last];
            a[last] = temp;
        }
    }

    cout << "Масив після знищення елементів: ";
    for(int i = 0; i < last + 1; i++){
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}