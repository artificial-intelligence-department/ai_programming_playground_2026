#include <iostream>
using namespace std;
 int n[100];
 int currentsize=0;
 void printstack(){
    if (currentsize==0){
        cout<<"Масив порожній."<<endl;
    }
    else{
        cout<<"Стан масиву: "<<endl;
        for (int i=0; i<currentsize; i++){
            cout<<n[i]<<" ";
        }
    }
    cout<<endl;
 }
int main()
{
    cout<<"Введіть кількість елементів"<<endl;
    cin>>currentsize;
    if (currentsize>0 && currentsize<=100){
        cout<<"Введіть "<<currentsize<<" елементів"<<endl;
        for (int i=0; i<currentsize; i++)
        {
            cin>>n[i];
        }
    }
    else{
        currentsize=0;
    }
    printstack();
int choice;
while (true){
    cout<<"Оберіть подію 1-додати 2-знищити 3-вийти"<<endl;
    cin>>choice;
    switch (choice){
    case 1:
    if (currentsize<100)
    {
        cout<<"Введіть число для додавання: "<<endl;
        cin>>n[currentsize];
        currentsize++;
        printstack();
    }
    else{
        cout<<"Помилка. Стек переповнений."<<endl;
    }
    break;
    case 2:
    if (currentsize>0){
        currentsize--;
        printstack();
    }
    else{
        cout<<"Масив порожній"<<endl;
    }
    break;
    case 3:
    return 0;
    default:
    cout<<"Невідома команда."<<endl;
    break;
    }
}
}