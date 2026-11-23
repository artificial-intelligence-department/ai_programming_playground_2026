#include <iostream>
using namespace std;

template <typename T>
class DynamicArr{
private:
    T* data=new T[1];  
    int arr_size=0;
    int arr_capacity=1;
public:
    int size(){
        return arr_size;
    }

    int capacity(){
        return arr_capacity;
    }

    void insert(int index, int n, T *nums){
        bool isExpanded=false;
        while(n+arr_size>=arr_capacity){
            arr_capacity*=2;
            isExpanded=true;
        }
        if(isExpanded){
            T *tmp=new T[arr_capacity];
            for(int i=0;i<arr_size;i++){
                tmp[i]=data[i];
            }
            delete[] data;
            data=tmp;
        }
        for(int i=arr_size-1;i>=index;i--){
            data[i+n]=data[i];
        }
        for(int i=index;i<index+n;i++){
            data[i]=nums[i-index];
        }
        arr_size+=n;      
    }
        
    void erase(int index, int n){
        for(int i=index+n;i<arr_size;i++){
            data[i-n]=data[i];
        }
        arr_size-=n;
    }

    T& operator[](int index){
        return data[index];
    }   
    friend ostream& operator<<(ostream& os, const DynamicArr<T>& v) {
        for (int i = 0; i < v.arr_size; i++) {
            if (i > 0) os << ' ';
            os << v.data[i];
        }
        return os;
    }
    ~DynamicArr() {
        delete[] data;
    }   
    
};



int main(){
    DynamicArr<int> arr;
    int Q;
    cin>>Q;
    for(int i=0;i<Q;i++){
        char com[10];
        cin>>com;
        if(com[0]=='s'&& com[1]=='i'){
            cout<<arr.size()<<"\n";
        }
        else if(com[0]=='c'){
            cout<<arr.capacity()<<"\n";
        }
        else if(com[0]=='i'){
            int index,n;
            cin>>index>>n;
            int *nums=new int[n];
            for(int i=0;i<n;i++){
                cin>>nums[i];
            }
            arr.insert(index,n,nums);
            delete[] nums;
            cout<<"\n";
        }
        else if(com[0]=='p'){
            cout<<arr<<"\n\n";
        }
        else if(com[0]=='g'){
            int n;
            cin>>n;
            cout<<arr[n]<<"\n";
        }
        else if(com[0]=='s' && com[1]=='e'){
            int n,num;
            cin>>n>>num;
            arr[n]=num;
        }
        else if(com[0]=='e'){
            int index,n;
            cin>>index>>n;
            arr.erase(index,n);
        }
    }
}