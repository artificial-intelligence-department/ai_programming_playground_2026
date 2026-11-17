#include <iostream>
#include <algorithm>//функції проситимуть позицію початку і позицію що зразу після кінця
using namespace std;
int main(){
    int N;
    cin >> N;
    int *arr = new int[N];
    for(int i = 0; i<N; i++){
        cin >> arr[i];
    }
    int *ptr1 = partition(arr, arr+N, [](int x){//всі що мають остачу 0 до ptr1(не включно)
        return(x % 3 == 0);});
    int *ptr2 = partition(ptr1, arr+N, [](int x){//всі що мають остачу 1 з ptr1 до ptr2
        return(x % 3 == 1);});
        sort(arr, ptr1);
        sort(ptr1, ptr2);//просто сортує по зростанню
        sort(ptr2, arr+N);
        reverse(ptr1, ptr2);//бо тут нам треба по спаданню
        int *allUnique = unique(arr, arr+N);//повертає вказівник на позицію з НЕунікальними елементами
        cout << allUnique - arr <<endl;
        for(int i = 0; i<allUnique-arr; i++){//різниця вказівників- цке кількість елементів між ними
            cout << arr[i] << " ";
        }
    return 0;
}