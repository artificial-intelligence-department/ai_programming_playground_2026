#include <iostream>
using namespace std;

struct Node {
    int index;
    Node* next;
};

struct Stack {
    Node* top = nullptr;
    ~Stack();
};

void push(Stack& stack, int index) {
    stack.top = new Node{index, stack.top};
}

void pop(Stack& stack) {
    if (stack.top == nullptr){
        return;
    } 

    Node* temp = stack.top;
    stack.top = temp->next;
    delete temp;
}

bool isEmpty(const Stack& stack) {
    return stack.top == nullptr;
}

Stack::~Stack() {
    while (!isEmpty(*this)){
        pop(*this);
    }
}

int main(){
    int n;
    cin >> n;

    Stack opened;
    int openCount = 0, closeCount = 0;
    int lastUnmatchedClose = -1;

    for(int i = 0; i < n; i++){
        char bracket;
        cin >> bracket;
        if(bracket == '<'){
            push(opened, i);
            openCount++;
        } 
        else{
            closeCount++;
            if(isEmpty(opened)){
                lastUnmatchedClose = i;
            }
            else{
                pop(opened);
            }
        }
    }

    if(openCount != closeCount){
        cout << "No way";
    } 
    else{
        cout << lastUnmatchedClose + 1;
    }

    return 0;
}