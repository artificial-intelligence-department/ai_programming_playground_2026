/*
 * Task: Self Practice 4 - Algotester 0010 (Young Artist)
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */

#include <iostream>

struct PaintOp {
  int l;
  int r;
  int color;
};

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

int findNext(int *nextFree, int x) {
  int root = x;
  while (nextFree[root] != root) {
    root = nextFree[root];
  }
  while (x != root) {
    int next = nextFree[x];
    nextFree[x] = root;
    x = next;
  }
  return root;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = 0;
  int m = 0;
  if (!(std::cin >> n >> m)) {
    return 0;
  }

  Stack<PaintOp> history;
  for (int i = 0; i < m; ++i) {
    PaintOp op;
    std::cin >> op.l >> op.r >> op.color;
    history.push(op);
  }

  int *colors = new int[n + 1];
  int *nextFree = new int[n + 2];
  for (int i = 1; i <= n; ++i) {
    colors[i] = 0;
    nextFree[i] = i;
  }
  nextFree[n + 1] = n + 1;

  while (!history.isEmpty()) {
    PaintOp op = history.pop();
    int pos = findNext(nextFree, op.l);
    while (pos <= op.r) {
      colors[pos] = op.color;
      nextFree[pos] = findNext(nextFree, pos + 1);
      pos = nextFree[pos];
    }
  }

  for (int i = 1; i <= n; ++i) {
    if (i > 1) {
      std::cout << ' ';
    }
    std::cout << colors[i];
  }
  std::cout << '\n';

  delete[] nextFree;
  delete[] colors;
  return 0;
}
