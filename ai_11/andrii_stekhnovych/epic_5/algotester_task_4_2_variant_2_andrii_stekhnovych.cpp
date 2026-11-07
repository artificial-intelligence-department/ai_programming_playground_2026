//Algotester Lab 4v2 (without STL)


#include <iostream>
using namespace std;
int* arrayToSet(int* array, int n, int &count) {
    bool counter[101]={0};
    count=0;
    for (int i=0; i<n; i++) {
        if (counter[array[i]]==false) {
            counter[array[i]]=true;
            count++;
        }
    }
    int* set = new int[count];
    int start=0;
    for(int i=0; i<101; i++) {
        if(counter[i]) {
            set[start]=i;
            start++;
        }
    }
    delete[] array;
    array=nullptr;
    return set; 
}
void sortArray(int* array, int length) {
    for (int i = 0; i<length-1; i++) {
        for (int j=0; j<length-1-i; j++) {
            if(array[i]>array[j]) {
                int temp=array[i];
                array[i]=array[j];
                array[i]=temp;
            }
        }
    }
}
int main() {
    int n, k;
    int unique=0;
    cin >> n >> k;
    int* array = new int[n];
    for (int i=0; i<n; i++) {
        cin >> array[i];
    }
    
    array = arrayToSet(array, n, unique);
    sortArray(array, unique);
    k=k%unique;
    cout << unique << endl;
    for (int i = k; i<unique; i++) {
        cout << array[i] << " ";
    }
    for (int i=0; i<k; i++) {
        cout << array[i] << " ";
    }
    delete[] array;
    array=nullptr;


}