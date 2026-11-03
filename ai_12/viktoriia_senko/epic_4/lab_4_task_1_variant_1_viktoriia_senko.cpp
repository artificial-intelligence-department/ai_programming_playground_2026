/*Lab 4 Task 1 Variant 1
Автор:Сенько Вікторія
Група: ШІ-12 group3*/
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
const int N=100;
void randomArray(int a[], int n){
    for(int i=0; i<n; i++){
        a[i]=rand() % 21 - 10;
    }
}
void deleteElement(int a[], int &n, int k){
    for(int i=k; i<n-1; i++ ){
        a[i]=a[i+1];
    }
    n--;
}
void print(int a[], int n){
    for(int i=0; i<n; i++) cout << a[i] <<" ";
    cout << endl;

}
void Zero(int a[], int &n){
    int i=0;
    while(i<n){
        if(a[i]%2 == 0 && n<=N){
            for(int j = n-1; j>i; j--){
                a[j+1]=a[j];
            }
            a[i+1]=0;
            i+=2;
            n++;
        }
        else i++;
    }
}
int main() {
    srand(time(nullptr));
    int n;
    int a[N];
    cout << "Введіть кількість елементів масиву:";
    cin >> n;
    while(cin.fail() || n<=0 || n>N){
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Ви ввели недійсне значення, спробуйте ще раз.";
        cin >> n;
    }
    cout <<"Початковий масив: ";
    randomArray(a,n);
    print(a,n);

    int k;
    cout << "Введіть номер елемента K, який хочете видалити: ";
    cin >> k;
    while(cin.fail() || k<0 || k>=n){
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Ви ввели недійсне значення, спробуйте ще раз."<<endl;
        cin >> k;
    }
    cout << "Масив після видалення елементу K: ";
    deleteElement(a,n,k);
    print(a,n);
    cout << "Масив після вставлення нулів після парних чисел: ";
    Zero(a,n);
    print(a,n);
    return 0;
}