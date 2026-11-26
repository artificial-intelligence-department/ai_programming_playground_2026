#include <iostream>
#include <string>
using namespace std;

template <typename T>
class DynArr{
    private:
    T *arr = new T[1];
    int size=0;
    int cap=1;
    void addCap(){
        T *b = new T[cap*2];
        for(int i =0; i<size; i++){
            b[i]=arr[i];
        }
        delete[] arr;
        arr= b;
        cap*=2;
    }
    public:
    T& operator[](int index){
        return arr[index];
    }

    void showSize(){
        cout<<size<<'\n';
        return ;
    }
    void showCap(){
        cout<<cap<<'\n';
        return;
    }

    void insert(int index,int N){
        while(cap<=size+N){
            addCap();
        }
        for (int i = size - 1; i >= index; i--) {
        arr[i + N] = arr[i];
        }
        for(int i = 0; i<N; i++){
            cin>>arr[index+i];
        }
        size += N;
    }
    void erase(int index, int elements){
        for(int j = index; j<size-elements; j++){
            arr[j]=arr[j+elements];
        }
        size= size-elements;
    }
    
    friend ostream&operator<<(ostream &os, DynArr<T> &myArr){
        for(int i =0; i<myArr.size; i++){
            os<<myArr[i];
            if (i<myArr.size-1){
                os<<' ';
            }
        }
        os<<endl;
        return os;
    }
};
int main(){
    DynArr<int> myArr={};
    int Q=0;
    cin>>Q;
    string choice;
    int index, N, val;
    for(int i = 0; i<Q; i++){
        cin>>choice;
        if (choice=="insert"){
            cin>>index>>N;
            myArr.insert(index,N);         
        }else if(choice=="erase"){
            cin>>index>>N;
            myArr.erase(index, N);
        }else if(choice=="size")myArr.showSize();
        else if(choice =="capacity")myArr.showCap();
        else if(choice=="get"){
            cin>>index;
            cout<<myArr[index]<<endl;
        }else if(choice == "set"){
            cin>>index>>val;
            myArr[index]=val;
        }else if(choice=="print"){
            cout<<myArr;
        }
    }    
}