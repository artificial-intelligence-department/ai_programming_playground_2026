// Algotester Lab 6 variant 1

#include <string>
#include <iostream>
using namespace std;
void Merge (string array[], string left[], int left_n, string right[], int right_n) {
    int i=0, j=0, k=0;
    while(i<left_n and j<right_n) {
        if (left[i]<right[j]) {
            array[k]=left[i];
            i++;

        } else {
            array[k]=right[j];
            j++;
        }
        k++;
    }
    while (i<left_n) {
        array[k]=left[i];
        i++;
        k++;
    }
    while (j<right_n) {
        array[k]=right[j];
        j++;
        k++;
    }
}
void mergeSort(string array[], int length) {
    if(length<2) {
        return;
    }
    int mid = length/2;
    string left[mid];
    string right[length-mid];
    for (int i =0; i<mid; i++) {
        left[i]=array[i];
    }

    for (int i=mid; i<length; i++) {
        right[i-mid]=array[i];
    }
    mergeSort(left, mid);
    mergeSort(right, length-mid);
    Merge(array, left, mid, right, length-mid);

}
int main(){
    int N, K;
    cin >> N >> K;
    string* words=new string[N];
    for (int i=0; i<N; i++) {
        cin >> words[i];
        for (char &c : words[i]) {
            c=tolower(c);
        }
    }
    mergeSort(words, N);
    bool letters[26] = {false};
    int count=1;
    for(int i =0; i<N; i++) {
        if (words[i]==words[i+1]) {
            count++;
        } else {
            if(count>=K) {
                for(char c:words[i]) {
                    letters[c-'a']=true;
                }
                
            }
            count=1;
        }
    }
    int num=0;
    for(int i =0; i<26; i++) {
        if(letters[i]) {
            num++;
        }
    }
    if(num>0) {
        cout << num << endl;
        for(int i=25; i>=0; i--) {
            if (letters[i]) {
                cout << char(i+'a') << " ";
            }
            
        }
    } else {
        cout << "Empty!";
    }

    delete[] words;
    words=nullptr;
}