/*
Lab 2 task 1 variant 1
Serhii Yurchenko
*/
#include <iostream>

using namespace std;

 int main(){
int sum = 0;
for (int i = 0;i<200;i++){
    if (i % 3 ==0){
        sum+=i;
    }
}
cout<<"сума цілих додатніх чисел, кратних 3 і менших 200 = "<<sum;
    return 0;
 } 