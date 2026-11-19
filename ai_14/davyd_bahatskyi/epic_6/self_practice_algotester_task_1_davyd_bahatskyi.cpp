/*
 * Task: Self Practice 1 - Algotester 0071 (All-Ukrainian Olympiad)
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */

#include <cstring>
#include <iostream>

struct BracketPair {
  int openPos;
  int closePos;
};

std::ostream &operator<<(std::ostream &os, const BracketPair &pair) {
  return os << pair.openPos << ' ' << pair.closePos;
}

template <typename T> class Stack {
private:
  struct Node {
    T value;
    Node *next;
  };

  Node *m_top;

public:
  Stack() : m_top(nullptr) {}

  ~Stack() {
    while (!isEmpty()) {
      pop();
    }
  }

  void push(const T &value) {
    Node *node = new Node{value, m_top};
    m_top = node;
  }

  T pop() {
    Node *temp = m_top;
    T value = temp->value;
    m_top = m_top->next;
    delete temp;
    return value;
  }

  bool isEmpty() const { return m_top == nullptr; }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  const int MAX_LEN = 100005;
  char *expr = new char[MAX_LEN];
  std::cin >> std::ws;
  if (!std::cin.getline(expr, MAX_LEN)) {
    delete[] expr;
    return 0;
  }

  size_t len = std::strlen(expr);
  if (len > 0 && expr[len - 1] == '\r') {
    expr[len - 1] = '\0';
    --len;
  }

  Stack<int> openIndices;
  BracketPair *pairs = new BracketPair[len / 2 + 1];
  size_t pairCount = 0;

  for (size_t i = 0; i < len; ++i) {
    if (expr[i] == '(') {
      openIndices.push(static_cast<int>(i + 1));
    } else if (expr[i] == ')') {
      int openPos = openIndices.pop();
      pairs[pairCount++] = BracketPair{openPos, static_cast<int>(i + 1)};
    }
  }

  std::cout << pairCount << '\n';
  for (size_t i = 0; i < pairCount; ++i) {
    std::cout << pairs[i] << '\n';
  }

  delete[] pairs;
  delete[] expr;
  return 0;
}
