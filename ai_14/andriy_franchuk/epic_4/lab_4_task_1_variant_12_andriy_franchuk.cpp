#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void minmax(int &min, int &max, const int a[], int n);
double avarage(const int a[], int n);
void deleter(const int a[], int n);

int main(){
    srand(time(nullptr));

    int n;
    cin >> n;

    int a[n];
    for(int i = 0; i < n; i++){
        a[i] = rand();
    }

    for(int i = 0; i < n; i++){
        cout << a[i] << " ";
    }
    cout << endl;

    int min, max;

    minmax(min, max, a, n);

    for(int i = 0; i < n; i++){
        if(a[i] == min){
            a[i] = max;
        }else if(a[i] == max){
            a[i] = min;
        }
    }

    deleter(a, n);
}

void minmax(int &min, int &max, const int a[], int n){
    min = a[0];
    max = a[0];
    for(int i = 0; i < n; i++){
        if(a[i] > max){
            max = a[i];
        } else if(a[i] < min){
            min = a[i];
        }
    }
}

double avarage(const int a[], int n){
    double sum = 0;
    for(int i = 0; i < n; i++){
        sum += a[i];
    }
    return sum/n;
}

void deleter(const int a[], int n){
    double avg = avarage(a, n);
    int N = 0;
    for(int i = 0; i < n; i++){
        if((double)a[i]/avg <= 1.1){
            N += 1;
        }
    }

    int b[N];

    for(int i = 0, j = 0; i < n; i++){
        if((double)a[i]/avg <= 1.1){
            b[j] = a[i];
            j++;
        }
    }
    
    for(int i = 0; i < N; i++){
        cout << b[i] << " ";
    }
    cout << endl;
}