# include <iostream>
#include  <ctime>
using namespace std;

int main() {
srand(time(nullptr));
int size = 10;
int* a =new int[size];
for(int i=0; i < size; i++) {
a[i] = rand() % 100;
}

for(int i=0; i < size; i++) {
  cout << " " <<  a[i];
}
int value;
int count = 0;
cout << "\nВведіть значення: " << endl;
cin >> value;
for(int i=0; i < size; i++) {
    if(a[i] == value) {
     count++;
    }
}

int new_size = size - count;
int* b = new int[new_size];
int index = 0;

for(int i= 0; i<size; i++) {
 if(a[i] != value) {
    b[index] = a[i];
    index++;
 }
}
delete[] a;
a = b;
size = new_size;
int count2 =0;
int index2 =0;
for(int i =0; i<size; i++) {
    if(a[i] %2 == 0) {
  count2++;
    }
}
int new2_size = size +count2;
int* c = new int[new2_size];
for (int i = 0; i < size; i++) {
    if (a[i] % 2 == 0) {
        c[index2] = 0; 
        index2++;      
    }
    c[index2] = a[i];
    index2++;
}
delete[] b;
a = c;
size = new2_size;
for(int i=0; i <size; i++) {
  cout << " " <<  a[i];
}
    return 0;
}