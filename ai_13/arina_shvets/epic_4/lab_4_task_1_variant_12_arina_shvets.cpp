#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){
    int n;
    cout << "Ввести розмір масиву: ";
    cin >> n;

    if (n < 1 || n > 100){
        return 0;
    }

    int a[100];
    srand(time(0));

    for (int i = 0; i < n; i++){
    a[i] = rand() % 100 + 1;
    }

    cout << "Початковий масив: ";
    for (int i = 0; i < n; i++){
        cout << a[i] << " ";
    }
    cout << endl;

    int min = 0;
    int max = 0;

    for(int i = 0; i < n; i++){
        if(a[i] < a[min]){
            min = i;
        }
        if(a[i] > a[max]){
            max = i;
        }
    }

    int temp = a[min];
    a[min] = a[max];
    a[max] = temp;

    double sum = 0;
    for(int i = 0; i < n; i++){
        sum += a[i];
    }
    double avg = sum / n;
    double limit = avg * 1.1;
    int newN = 0;

    for(int i = 0; i < n; i++){
        if(a[i] <= limit){
            a[newN] = a[i];
            newN++;
        }
    }
    n = newN;

    cout << "Змінений масив: ";
    for(int i = 0; i < n; i++){
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}