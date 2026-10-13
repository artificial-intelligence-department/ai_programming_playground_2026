
/*
Algotester lab1 
Дохнюк Богдан 
ШІ-14
Варіант 2 
*/
#include <iostream>
using namespace std;


int main() {
	
long long h1,h2,h3,h4,d1,d2,d3,d4, max, min;
//введення даних	
cin>>h1>>h2>>h3>>h4;
cin>>d1;
cin>>d2;
cin>>d3;
cin>>d4;

bool brek = false;

h1-=d1; //перше відпилювання

//знаходження мінімального / максимального
max = h1; min = h1;
if(max<h2)max = h2;
if(max<h3)max = h3;
if(max<h4)max = h4;

if(min>h2)min = h2;
if(min>h3)min = h3;
if(min>h4)min = h4;

if(max>=2*min)brek = true;

h2-=d2; //друге відпилювання

//знаходження мінімального / максимального
max = h1; min = h1;
if(max<h2)max = h2;
if(max<h3)max = h3;
if(max<h4)max = h4;

if(min>h2)min = h2;
if(min>h3)min = h3;
if(min>h4)min = h4;

if(max>=2*min)brek = true;

h3-=d3; //третє відпилювання

max = h1; min = h1;
if(max<h2)max = h2;
if(max<h3)max = h3;
if(max<h4)max = h4;

if(min>h2)min = h2;
if(min>h3)min = h3;
if(min>h4)min = h4;

if(max>=2*min)brek = true;

h4-=d4; //четверте відпилювання

max = h1; min = h1;
if(max<h2)max = h2;
if(max<h3)max = h3;
if(max<h4)max = h4;

if(min>h2)min = h2;
if(min>h3)min = h3;
if(min>h4)min = h4;

if(max>=2*min)brek = true;

if(h1<0 || h2<0 || h3<0 || h4<0)cout<<"ERROR";
else if(!brek && h1==h2 && h2==h3 && h3==h4)cout<<"YES";
else cout<<"NO";

	
	return 0;
}