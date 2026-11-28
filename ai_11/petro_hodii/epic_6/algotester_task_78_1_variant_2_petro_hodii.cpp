#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Masiv{
private:
    int size = 0;
    int capacity = 1;
    T* mas = new T[capacity];

public:
    void Size(){
        cout << size << endl;
    }
    void Capacity(){
        cout << capacity << endl;
    }
    T* Resize(){
        capacity *= 2;
        int* tmp = new int[capacity];
        for(int i = 0; i < size; i++){
            tmp[i] = mas[i];
        }
        return tmp;
    }
    void Insert(int index, int num){
        
            for(int i = size-1; i >= index; i--){
                mas[i+1] = mas[i];
            }
            mas[index] = num;
            size++;
            if(size == capacity){
            int* tmp = Resize();
            delete[] mas;
            mas = tmp;
            }
    }
    void Erase(int index, int count){
        for(int i = 0; i < count; i++){
            mas[index+i] = 0;
        }
        for(int i = index+count; i < size; i++){
            mas[i-count] = mas[i];
        }
        size -= count;
    }
    const T& operator[](int index) const {
        return mas[index];
    }
    T& operator[](int index){
        return mas[index];
    }
    friend ostream& operator<<(ostream& os, const Masiv& m) {
        for (int i = 0; i < m.size; i++) {
            os << m[i] << " ";
        }
        return os;
    }
    void Get(int index){
        cout << (*this)[index] << endl;
    }
    void Set(int index, int number){
        (*this)[index] =  number;
    }
    void Delete(){
        delete[] mas;
        mas = nullptr;
    }
};

int main(){
    int n;
    string action;
    cin >> n;
    Masiv<int> mas;

    for(int i = 0; i < n; i++){
        cin >> action;
        if(action == "insert"){
            int a,b,num;
            cin >> a >> b;
            for(int j = 0; j < b; j++){
                cin >> num;
                mas.Insert(a,num);
                a++;
            }
        }
        else if(action == "erase"){
            int a,b;
            cin >> a >> b;
            mas.Erase(a,b);
        }
        else if(action == "size"){
            mas.Size();
        }
        else if(action == "capacity"){
            mas.Capacity();
        }
        else if(action == "get"){
            int a;
            cin >> a;
            mas.Get(a);
        }
        else if(action == "set"){
            int a,b;
            cin >> a >> b;
            mas.Set(a,b);
        }
        else if(action == "print"){
            cout << mas << endl;
        }
    }

    mas.Delete();

    return 0;
}