/*Epic 4 - Замовлення від стоматологів
Бурбан Данило
Ші - 14*/
#include <iostream>
#include <algorithm>
using namespace std;
int main(){
    int n, m;
    cin >> n >> m;
    int **arr = new int*[n];
    for(int i = 0; i < n; i++){
        arr[i] = new int[m];
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> arr[i][j];
        }
    }
    int *arr_alt = new int[n*m];
    int number_of_elements=0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            arr_alt[number_of_elements]=arr[i][j];
            number_of_elements++;
        }
    }
sort(arr_alt,arr_alt+number_of_elements);
    int *arr_alt_alt = new int[number_of_elements];
    int number_of_results = 0;
    for(int i=0;i<number_of_elements;i++){
        if(arr_alt[i]==arr_alt[i+1]){
            arr_alt_alt[number_of_results]=arr_alt[i];
            number_of_results++;
        }
    }

    cout<<number_of_results<<endl;
    for(int i=0;i<number_of_results;i++){
        cout<<arr_alt_alt[i]<<" ";
    }

    for(int i = 0; i < n; i++){    
        delete[] arr[i];
        arr[i] = nullptr;
    }
    delete[] arr;
    delete[] arr_alt;
    delete[] arr_alt_alt;
}