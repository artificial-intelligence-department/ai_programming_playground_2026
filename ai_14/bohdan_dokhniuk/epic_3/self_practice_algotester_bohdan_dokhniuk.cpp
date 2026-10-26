
/*  
self practice 
Дохнюк Богдан 
ШІ-14
задача : Зуби 
*/
#include <iostream>
using namespace std;
int main () {
int n,k,a;
cin>>n>>k;
int best = 0;
int pot = 0;
for(int i = 0; i<n;i++)
{
cin>>a;
if(a>=k) pot++;
else pot=0;
if(pot>best)best=pot;
}

cout<<best;

return 0;
}