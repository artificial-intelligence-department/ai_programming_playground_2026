//Спільне у змінного 
#include <iostream>
using namespace std;

struct Node {
    int value;
    int gcd;
    Node* next;
};

struct Stack {
    Node* top = nullptr;

    ~Stack();
};

int gcd(int a, int b){
    while(b != 0){
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

void push(Stack& stack, int x){
    int newGcd = x;
    if(stack.top != nullptr){
        newGcd = gcd(x, stack.top->gcd);
    }
    stack.top = new Node{x, newGcd, stack.top};
}

void pop(Stack& stack){
    if(stack.top == nullptr){
        return;
    }
    Node* temp = stack.top;
    stack.top = temp->next;
    delete temp;
}

void clearStack(Stack& stack){
    while(stack.top != nullptr){
        pop(stack);
    }
}

Stack::~Stack(){
    clearStack(*this);
}

int main(){
    int n;
    cin >> n;

    Stack stack;
    for(int i = 0; i < n; i++){
        char type;
        cin >> type;
        if(type == '+'){
            int x;
            cin >> x;
            push(stack, x);
        }
        else if(type == '-'){
            pop(stack);
        }
        else{
            cout << stack.top->gcd << endl;
        }
    }
    return 0;
}