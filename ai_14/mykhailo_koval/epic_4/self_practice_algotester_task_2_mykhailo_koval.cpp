/*
Self practice task 2
Ім'я: Коваль Михайло
Група: ШІ-14
*/

#include <iostream>

int main(){
   long k, n;
   std::cin >> k >> n;
   if(k < 1 || k > 100 || n < 1 || n > 100){
        return 0;
   }

   long *prices = new long[n];
   for(int i = 0; i < n; i++){
        std::cin >> *(prices + i);
        if(*(prices + i) < 1 || *(prices + i) > 100){
            return 0;
        }
   }

   for(int j = 0; j < n - 1; j++){
        for(int i = 0; i < n - 1 - j; i ++){
            if(*(prices + i) > *(prices + i + 1)){
                long x = *(prices + i);
                *(prices + i) = *(prices + i + 1);
                *(prices + i + 1) = x;
            }
        }
   }

   int count = 0;
   for(int i = 0; i < n; i++){
        long y = k -= *(prices + i);
        if(y < 0){
            break;
        }
        count++;
   }

   std::cout << count;

   delete[] prices;
   prices = nullptr;
   return 0;
}
