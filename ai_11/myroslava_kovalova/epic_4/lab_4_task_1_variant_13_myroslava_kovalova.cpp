/* Лабораторна робота 4, завдання 1, варіант 13
Ковальова Мирослава
ШІ-11
*/
#include <iostream>
using namespace std;

int randomNum(){
    static unsigned int rand_num = 3425;
    rand_num = rand_num*3902801+6757477;
    return rand_num % 30;
}

int main(){
    int a[100]={0};
    int n =0;

    while(true){
        cout<<"Введіть розмір масиву\n";
        cin>>n;
        if(n>100 || n<=0 || cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            cout<<"\nНекоректний ввід. Введіть ціле число від 1 до 100.\n";
        }else break;
    }

    for (int i =0; i<n; i++){
        a[i] = randomNum();
        cout<<a[i]<<" ";
    }
    
    int min = a[0];
    for (int i = 1; i<n;i++){
        if (a[i]<min) min=a[i]; 
    }

    //count виступає у ролі зсуву
    int count = 0;
    for (int i = 0; i<n; i++){
        if (a[i]==min){
            count++;
        }else{
           a[i-count]=a[i];
        }
    }
    
    n-=count;
    if (n+3>100){
        cout<<"\nНеможливо додати значення. Вихід за межі розмірів масиву\n";
        return 0;
    }
    int sum = 0;
    for (int i = 0; i<n; i++){
        sum+=a[i];
    }

    if (n==0){
        cout<<"\nВсі елементи масива однакові.\n";
        return 0;
    }
    int avarage = sum/n;
    for (int i = n+2, j=n-1; i>=3; i--, j--){
        a[i]=a[j];
    }
    for (int i = 0; i<3; i++){
        a[i]=avarage;
    }
    
    n+=3;
    cout<<"\nФінальний масив\n";
    for (int i = 0; i<n; i++){
        cout<<a[i]<<" ";
    }

    return 0;
}