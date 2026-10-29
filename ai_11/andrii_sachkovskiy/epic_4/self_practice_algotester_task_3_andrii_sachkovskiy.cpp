/*
 * Задача: self_practice_algotester_task_3  Найдовший зростаючий підмасив
 * Автор: Сачковський Андрій
 * Група: AI-11
*/
//треба знайти найдовшу послідовність яка зростає
#include <iostream>

using namespace std;

int main(){
//користувач водить дані
int n;
cin>>n;

int *massive = new int [n];

for (int i = 0 ; i < n ; i++)
{
cin>>*(massive+i);

}
int z=1;
int best=1;
int i = 1;

while (i < n){
//робиться порівняння з попереднім
if (*(massive+i) > *(massive+i-1))
{
z++;
}
else
{
z = 1;
}                         

if (z > best) best = z;   

i++;                     
}                      

cout<<best;                

delete [] massive;
}