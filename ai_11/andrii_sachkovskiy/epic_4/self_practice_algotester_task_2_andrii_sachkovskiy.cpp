/*
 * Задача: self_practice_algotester_task_2 Літня школа
 * Автор: Сачковський Андрій
 * Група: AI-11
*/
//кароче є студенти вони можуть поділитися на команди по 1 2 3 чоловіка визначити чи можна з дантх користовача стоврити команди
//якщо можна то виписати скільки учасників є в кожній команді 

#include <iostream>

using namespace std;

int main(){
int n;
int k;
//користовач водить різні значення 
cin>>n;

cin>>k;

// первірка
if (n < k || n > 3*k){
    cout<<"Impossible";  
    return 0;             
    }


//кожна команда має по 1 студенту шоб не було пустих команд
int *team = new int[k];   

for (int i = 0 ; i < k; i++){
    *(team+i) = 1;        
}
n -= k;                  

//
for (int i = 0 ; i < k; i++){

    if (n >= 2){              
        *(team+i) += 2;       
        n -= 2;               
    }
    else {                    
        *(team+i) += n;       
        n = 0;                
    }

}
//виводимо розміри команд
for (int i = 0 ; i < k; i++){
    cout<<*(team+i)<<" ";     
}



delete [] team;               
}