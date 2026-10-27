#include <iostream>
#include <ctime> 
#include <cstdlib>

using namespace std;

int main(){
    srand(time(0));

    int N=100;
    int a[N];

    int n=0;

    do{
       cout<<"\nВведіть довжину масиву: ";
       cin>>n;
    }while(n<1||n>101);


        
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100;
    }
    
    // 2. Друк початкового масиву
    cout << "\nПочатковий масив: ";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    int value;
    cout << "\nУведіть значення для видалення: ";
    cin >> value;

    int pos = -1;

    for (int i = 0; i < n; i++)
    {
        if (a[i] == value)
        {
            pos = i;
            break;
        }
    }
    if (pos != -1)
    {
        for (int i = pos; i < n - 1; i++)
        {
            a[i] = a[i + 1];
        }

        n--;

        cout << "\nЕлемент зі значенням " << value << " був видалений" << endl;
    }
    else
    {
        cout << "\nЕлемент зі значенням " << value << " не знайдено." << endl;
    }
    
    int K;
    cout << "\nУведіть зсув k : ";
    cin >> K;

    K=K%n;
    int adw[100];
    for(int i=0;i<n;i++){
       adw[i]=a[i];
    }
    for(int i=0;i<n;i++){
        int smiz=0;
        if(i+K>=n){
          smiz=i+K-n;
        }
        else{
            smiz=i+K;
        }
        a[smiz]=adw[i];
    }

    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    return 0;
}