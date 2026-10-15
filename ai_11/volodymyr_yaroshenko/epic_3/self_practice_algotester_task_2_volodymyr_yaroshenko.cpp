#include <iostream>
#include <algorithm>

using namespace std;

bool upper(int year) {
return year % 400== 0 ||(year % 4== 0 && year % 100!= 0);
}

int main() {
long long n;
cin >> n;
long long half = n / 400; 
int remainder = n % 400; 
long long year_half = half * 97; 
int minimum = remainder;
int maximum = 0;
for (int start= 1; start<= 400; start++) {
    int count = 0;
    for (int i= 0; i<remainder; i++) {
    int year = (start + i - 1) % 400 + 1; 
        if (upper(year)) {
        count++;
}
}
minimum = min(minimum, count);
maximum = max(maximum, count);
}
cout << year_half + minimum << " " << year_half + maximum;
return 0;
}