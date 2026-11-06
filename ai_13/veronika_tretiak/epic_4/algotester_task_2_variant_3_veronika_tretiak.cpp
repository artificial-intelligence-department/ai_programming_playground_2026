/*
Автор: Вероніка Третяк
Задача: Алготестер №2, варіант №3
Група: ШІ-13
*/
#include <iostream>

using namespace std;

int main(){
int n;
cin >> n;
int* arr = new int[n];
for(int i = 0; i < n; i++){
    cin >> arr[i];
}
int left = 0;
int right = n - 1;

while(right - left > 1){
    left += arr[left];
    right -= arr[right];
}
cout << left + 1 << " " << right + 1 << endl;
if(left == right){
    cout << "Collision" << endl;
}else if(left > right){
    cout << "Miss" << endl;
}else{
    cout << "Stopped" << endl;
}
delete[] arr;
arr = nullptr;
return 0;
}