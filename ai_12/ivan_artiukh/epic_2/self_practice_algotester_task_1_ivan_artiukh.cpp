#include <iostream>
#include <numeric>
using namespace std;

int main(){
   int a = 0, b = 0;
   cin>>a>>b;

   if( (b-a) % 12 != 0){
       cout<<-1;
      return 0;
   }

   float diff = (b - (float)a) / 12;
   long long res = (a + b)*6.5;
   cout<<res;
}
