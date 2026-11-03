/*
Self practice task 1
Ім'я: Коваль Михайло
Група: ШІ-14
*/


#include <iostream>

int main(){
   long n, m;
   std::cin >> n >> m;

   long **lotery = new long*[n];
   for(int i = 0; i < n; i++){
        lotery[i] = new long[m];
   }
   
   for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            std::cin >> *(*(lotery + i) + j);
        }
   }

   long answer = 0;

   for(int i = 0; i < m; i++){
        long max_number = *(*(lotery + 0) + i);
        for(int j = 0; j < n; j++){
            if(*(*(lotery + j) + i) > max_number){
                max_number = *(*(lotery + j) + i);
            }
        }
        if(i == 0 || max_number < answer){
            answer = max_number;
        }
   }

   std::cout << answer;
   for(int i = 0; i < n; i++){
        delete[] lotery[i];
        lotery[i] = nullptr;
   }
   delete[] lotery;
   lotery = nullptr;

}