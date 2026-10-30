/*
 * Задача: lab_4_task_1_variant_22
 * Автор: Сачковський Андрій
 * Група: AI-11
*/
#include <iostream>

using namespace std;
//треба програма де є стек користовач водить число воно добавляється в стек або видаляє
int stek[10000];
int n = 0;  
int chislo1;   
int vibor;


int main() {

do {
    
    cout<<"1 - додати, 2 - видалити, 0 - вихід: > "<<endl;
    cin>>vibor;

    switch (vibor){
        case 1:
               
               if (n == 10000) {
                   cout<<"Стек повний!"<<endl;
               } else {
                   cout<<"Ведіть число> ";   
                   cin>>chislo1;
                   stek[n]= chislo1;
                   n++;                       
               }
               break;

        case 2:
               
               if (n == 0) {
                   cout<<"Стек порожній!"<<endl;
               } else {
                   n--;
               }
               break;
        
        case 0:
               return 0;
               break;

        default:
               
               cout<<"Невірний вибір"<<endl;
               break;
    }

    
     cout<<"Стек: ";
    for (int i = 0; i < n; i++) {
        cout<<stek[i]<<" ";
    }
    cout<<endl<<endl;

} while(true);                  

}