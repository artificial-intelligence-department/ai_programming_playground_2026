#include <iostream>
#include <string>
using namespace std;

struct DynArr{
    int *arr = new int[1];
    int size=0;
    int cap=1;

    int& operator[](int index){
        return arr[index];
    }
       
};
ostream&operator<<(ostream &os,  DynArr& myArr){
    for(int i =0; i<myArr.size; i++){
        os<<myArr[i];
        if (i<myArr.size-1){
            os<<' ';
        }
    }
    os<<endl;
    return os;

}
void addCap(DynArr &myArr){
    int *b = new int[myArr.cap*2];
    for(int i =0; i<myArr.size; i++){
        b[i]=myArr.arr[i];
    }
    delete[] myArr.arr;
    myArr.arr= b;
    myArr.cap*=2;
}

void insert(int index,int N, DynArr &myArr){
    while(myArr.cap<=myArr.size+N){
        addCap(myArr);
    }
    for (int i = myArr.size - 1; i >= index; i--) {
    myArr.arr[i + N] = myArr.arr[i];
    }
    for(int i = 0; i<N; i++){
        cin>>myArr.arr[index+i];
    }
    myArr.size += N;
}
void erase(DynArr &myArr, int index, int elements){
    for(int j = index; j<myArr.size-elements; j++){
        myArr.arr[j]=myArr.arr[j+elements];
    }
    myArr.size= myArr.size-elements;
}


int main(){
    DynArr myArr={};
    int Q=0;
    cin>>Q;
    string choice;
    int index, N, val;
    for(int i = 0; i<Q; i++){
        cin>>choice;
        if (choice=="insert"){
            cin>>index>>N;
            insert(index,N,myArr);         
        }else if(choice=="erase"){
            cin>>index>>N;
            erase(myArr,index, N);
        }else if(choice=="size")cout<<myArr.size<<endl;
        else if(choice =="capacity")cout<<myArr.cap<<endl;
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