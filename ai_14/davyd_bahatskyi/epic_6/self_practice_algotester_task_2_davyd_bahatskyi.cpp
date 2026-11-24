/*
 * Task: Self Practice 2 - Algotester 0165 (Dangerous Task)
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */

#include <iostream>

enum class PlankState { DYNAMITE = 0, SAFE = 1 };

struct Queue {
  int *data;
  int head;
  int tail;
};

Queue createQueue(int capacity) {
  Queue q;
  q.data = new int[capacity];
  q.head = 0;
  q.tail = 0;
  return q;
}

void destroyQueue(Queue &q) {
  delete[] q.data;
  q.data = nullptr;
}

void enqueue(Queue &q, int value) { q.data[q.tail++] = value; }

int dequeue(Queue &q) { return q.data[q.head++]; }

bool isEmpty(const Queue &q) { return q.head == q.tail; }

void bfsPlanks(int n, int start, int step, const PlankState *planks,
               int *dist) {
  for (int i = 1; i <= n; ++i) {
    dist[i] = -1;
  }

  Queue q = createQueue(n + 1);
  dist[start] = 0;
  enqueue(q, start);

  const int dirs[2] = {-step, step};
  while (!isEmpty(q)) {
    int cur = dequeue(q);
    for (int d = 0; d < 2; ++d) {
      int next = cur + dirs[d];
      if (next >= 1 && next <= n && planks[next] == PlankState::SAFE &&
          dist[next] == -1) {
        dist[next] = dist[cur] + 1;
        enqueue(q, next);
      }
    }
  }

  destroyQueue(q);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = 0;
  int a = 0;
  int b = 0;
  if (!(std::cin >> n >> a >> b)) {
    return 0;
  }

  PlankState *planks = new PlankState[n + 1];
  for (int i = 1; i <= n; ++i) {
    char ch = '0';
    std::cin >> ch;
    planks[i] = (ch == '1') ? PlankState::SAFE : PlankState::DYNAMITE;
  }

  int *distRico = new int[n + 1];
  int *distKowalski = new int[n + 1];

  bfsPlanks(n, a, 4, planks, distRico);
  bfsPlanks(n, b, 7, planks, distKowalski);

  int bestTime = -1;
  for (int i = 1; i <= n; ++i) {
    if (distRico[i] != -1 && distKowalski[i] != -1) {
      int total = distRico[i] + distKowalski[i];
      if (bestTime == -1 || total < bestTime) {
        bestTime = total;
      }
    }
  }

  std::cout << bestTime << '\n';

  delete[] distKowalski;
  delete[] distRico;
  delete[] planks;
  return 0;
}
