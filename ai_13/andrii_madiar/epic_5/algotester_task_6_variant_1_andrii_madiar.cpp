#include <iostream>
#include <string>
#include <cctype>
using namespace std;
void mergeSort(string *a, string *temp, int start, int end){
    if(start >= end) return;//умова виходу з рекурсії
    int mid = start + (end - start) / 2;
    mergeSort(a, temp, start, mid);//рекурсивне сортування лівої і правої половини
    mergeSort(a, temp, mid+1, end);
    int i = start, j = mid+1, k = start;
    while (i <= mid && j <= end){
        if(a[i] <= a[j]){//порівнювання поточних найменших елементів
            temp[k++] = a[i++];
        }else{//запис залежно від результату і зсув вказівників
            temp[k++] = a[j++];
        }
    }
    while(i <= mid)temp[k++] = a[i++];//дописування тої половини яку ще не вичерпали
    while(j <= end)temp[k++] = a[j++];

    for(int m = start; m <= end; m++){
        a[m] = temp[m];//перепризначення тимчасових елементів у сам масив
    }
}
int main(){
    int n, k;
    cin >> n >> k;
    bool empty = true, letters[26] = {false};
    string *s = new string[n];//масив стрінгів лол
    string *temp = new string[n];
    for(int i = 0; i<n; i++){
        cin >> s[i];
        for(int j = 0; j<s[i].length(); j++)s[i][j] = tolower(s[i][j]);//робимо всі символи маленькими
    }
    mergeSort(s, temp, 0, n-1);
    int currentCount = 1;
    for (int i = 0; i < n; i++) {
        if (i+1<n && s[i] == s[i+1]){//поскільки вже відсортовано то треба лише перевіряти доки не буде слова яке відрізняється
            currentCount++;
        }else{//якщо співпадіння закінчилися йде перевірка чи слів достатньо
            if (currentCount >= k){
                empty = false;
                for (int j = 0; j<s[i].length(); j++){
                    letters[s[i][j] - 'a'] = true;//перевірка які букви наявні
                }
            }currentCount = 1;//скидування значення
        }
    }
    if(empty){
        cout << "Empty!";
    }else{
        int count = 0;
        for(int i = 25; i >= 0; i--){//обрахунок і вивід кількості унікальних букв
            if(letters[i])count++;
    }
    cout << count <<endl;
    for(int i = 25; i >= 0; i--){//виводимо якщо наявні, від 'z' до 'a' 
        if(letters[i])cout << char('a' + i) << " ";
    }
}
delete[] s;
delete[] temp;
    return 0;
}