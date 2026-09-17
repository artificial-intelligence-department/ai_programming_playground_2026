#include <iostream>
using namespace std;
int main() {
    
    int n;
    int a1, a2, a3, a4, a5, a;
    int i=0;
    a=a1;
    cin>>n;
    cin>>a1>>a2>>a3>>a4>>a5;
    a=a1;
   if (a1<a2) 
       {  i=i+2; }
   if (a2<a3) 
       {  i++; }
   if (a3<a4) 
      {  i++; ;}
   if (a4<a5) 
      {  i++; }
  cout<<i;

    return 0;
}