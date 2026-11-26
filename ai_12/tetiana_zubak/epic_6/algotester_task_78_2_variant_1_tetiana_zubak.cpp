#include <iostream>
#include <cstdio>

using namespace std;

template <typename T>
class List{
private:
    class Node{
    public:
        T el;
        Node* next;
        Node* prev;
    };

    Node* first = nullptr;
    Node* last = nullptr;
    int t = 0;

    static Node* made(T a){
        static Node pool[500001];
        static int pool_ptr = 0;
        pool[pool_ptr] = {a, nullptr, nullptr};
        return &pool[pool_ptr++];
    }

    Node* find(int in) const{
        Node* p;
        if(in < t - 1 - in){
            p = first;
            for(int i = 0; i < in; i++) p = p->next;
        } else{
            p = last;
            for(int i = t - 1; i > in; i--) p = p->prev;
        }
        return p;
    }

public:
    void insert(){
        int in, n;
        T a;
        scanf("%d %d", &in, &n);
        if(n == 0) return;

        Node* f = nullptr;
        Node* l = nullptr;

        for(int i = 0; i < n; i++){
            scanf("%d", &a);
            Node* num = made(a);
            if(f == nullptr) f = num;
            else{
                l->next = num;
                num->prev = l;
            }
            l = num;
        }

        if(in == 0){
            l->next = first;
            if(first != nullptr) first->prev = l;
            else last = l;
            first = f;
        } else if(in == t){
            f->prev = last;
            if(last != nullptr) last->next = f;
            else first = f;
            last = l;
        } else{
            Node* p = find(in);
            f->prev = p->prev;
            l->next = p;
            p->prev->next = f;
            p->prev = l;
        }
        t += n;
    }

    void erase(){
        int in, n;
        scanf("%d %d", &in, &n);
        if(n <= 0) return;

        Node* p = find(in);
        Node* before = p->prev;

        for(int i = 0; i < n; i++){
            p = p->next;
        }
        if(before != nullptr) before->next = p;
        else first = p;
        if(p != nullptr) p->prev = before;
        else last = before;
        t -= n;
    }

    void size() const{
        printf("%d\n", t);
    }

    void get() const{
        int in;
        scanf("%d", &in);
        printf("%d\n", find(in)->el);
    }

    void set(){
        int in;
        T newval;
        scanf("%d %d", &in, &newval);
        find(in)->el = newval;
    }

    void print() const{
        cout << *this << "\n";
    }

    friend ostream& operator<<(ostream& os, const List<T>& l){
        Node* p = l.first;
        while(p != nullptr){
            os << p->el;
            if(p->next != nullptr) os << " ";
            p = p->next;
        }
        return os;
    }
};

int main(){
    List<int> l;
    int Q;
    if(scanf("%d", &Q) != 1) return 0;
    char que[10];

    while(Q--){
        scanf("%s", que);
        if(que[0] == 'i') l.insert();
        else if(que[0] == 'e') l.erase();
        else if(que[0] == 'g') l.get();
        else if(que[0] == 'p') l.print();
        else if(que[0] == 's'){
            if(que[1] == 'i') l.size();
            else l.set();
        }
    }

    return 0;
}