#include <iostream>

const int MAX_SIZE = 100;

void print(int stack[], int n)
{
    if (n == 0)
        std::cout << "Your stack is empty!";
    else
    {
        std::cout << "Your stack contains: [";
        for (int i = 0; i < n; i++)
        {
            if (i == n - 1)
                std::cout << stack[i] << "]";
            else
                std::cout << stack[i] << ", ";
        }
    }
    std::cout << std::endl;
}

void push(int stack[], int &n, int value)
{
    if (n < MAX_SIZE)
    {
        std::cout << "Added to stack: " << value << std::endl;
        stack[n] = value;
        n++;
        print(stack, n);
    }
    else
        std::cout << "Your stack is overflowed!" << std::endl;
}

void pop(int stack[], int &n)
{
    if (n == 0)
        std::cout << "Your stack is empty!" << std::endl;
    else
    {
        std::cout << "Removed from stack: " << stack[n-1] << std::endl;
        stack[n - 1] = 0;
        n--;
        print(stack, n);
    }
}

int main()
{
    int stack[MAX_SIZE] = {0};
    int N;

    std::cout << "Enter stack lenght: ";
    std::cin >> N;

    std::cout << "Enter your elements of stack: ";
    for (int i = 0; i < N; i++)
        std::cin >> stack[i];

    pop(stack, N);
    pop(stack, N);
    pop(stack, N);
    push(stack, N, 10);
    push(stack, N, 13);
    push(stack, N, -14);

    return 0;
}