/*
 * Задача: self_practice_algotester_task_1 ЦІКАВИЙ МАСИВ
 * Автор: Сачковський Андрій
 * Група: AI-11
*/


//Користовач водить дані для масиву затім масив розбивається на 2 частини перебираються всі можливі варінти розриву
//якщо сума першої половини доріувнює сумі другої то так якщо навпаки то ні 

#include <iostream>

using namespace std;

int main(){
    bool found = false;
    int n ;
    //користовач водить різні значення 
    cin>>n;
    if(n<1 || n>200 ){
        return 0 ;
    }
    int *number  = new int[n];

    for (int i = 0 ; i < n ; i++){
        cin>>*(number+i);
    }
    

//шукається сума першої часитини і другої 
    int suma1 = 0;
    int suma2 = 0;
    int z;

    for (z = 1 ; z < n ; z++){
        suma1 = 0;  
        suma2 = 0;

        for (int i = 0 ; i < z; i++ ){
            suma1 += *(number+i);
        }
        for (int i = z ; i < n; i++ ){
            suma2 += *(number+i);
        }

        if (suma1 == suma2){
            found = true;
            break;   
        }
    }

    if (found){
        cout<<"TAK";
    }
    else {
        cout<<"NI";
    }

    delete [] number;
}