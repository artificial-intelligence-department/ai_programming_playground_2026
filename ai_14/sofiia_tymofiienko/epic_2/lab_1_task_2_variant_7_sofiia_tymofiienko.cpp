#include <iostream>
using namespace std;
int main(){



int n=3;
int m=11;


int res1= m + --n;
 cout <<"Перша дія: "<<res1<< endl;

bool res2=  m++ < ++n;
cout <<"Друга дія: " <<res2<<endl;

bool res3= n-- < --m;
cout <<"Третя дія: "<<res3<<endl;


return 0;
}