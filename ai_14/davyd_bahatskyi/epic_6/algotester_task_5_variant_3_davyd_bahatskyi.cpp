/*
 * Task: Algotester Lab 5v3 - Mountain Map
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */

#include <iostream>

struct Cell {
  int r;
  int c;
};

struct Queue {
  Cell *data;
  int head;
  int tail;
};

Queue createQueue(int capacity) {
  Queue q;
  q.data = new Cell[capacity];
  q.head = 0;
  q.tail = 0;
  return q;
}

void destroyQueue(Queue &q) {
  delete[] q.data;
  q.data = nullptr;
}

void enqueue(Queue &q, int r, int c) {
  q.data[q.tail].r = r;
  q.data[q.tail].c = c;
  ++q.tail;
}

Cell dequeue(Queue &q) {
  Cell front = q.data[q.head];
  ++q.head;
  return front;
}

bool isEmpty(const Queue &q) { return q.head == q.tail; }

int computeDistances(int n, int m, int startR, int startC, int *dist) {
  int total = n * m;
  for (int i = 0; i < total; ++i) {
    dist[i] = -1;
  }

  Queue q = createQueue(total);
  dist[startR * m + startC] = 0;
  enqueue(q, startR, startC);

  const int dr[4] = {-1, 1, 0, 0};
  const int dc[4] = {0, 0, -1, 1};
  int maxDist = 0;

  while (!isEmpty(q)) {
    Cell cur = dequeue(q);
    int curDist = dist[cur.r * m + cur.c];

    for (int d = 0; d < 4; ++d) {
      int nr = cur.r + dr[d];
      int nc = cur.c + dc[d];
      if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
        int idx = nr * m + nc;
        if (dist[idx] == -1) {
          dist[idx] = curDist + 1;
          if (dist[idx] > maxDist) {
            maxDist = dist[idx];
          }
          enqueue(q, nr, nc);
        }
      }
    }
  }

  destroyQueue(q);
  return maxDist;
}

void printMountainMap(int n, int m, int maxDist, const int *dist) {
  for (int r = 0; r < n; ++r) {
    for (int c = 0; c < m; ++c) {
      if (c > 0) {
        std::cout << ' ';
      }
      std::cout << (maxDist - dist[r * m + c]);
    }
    std::cout << '\n';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = 0;
  int m = 0;
  int x = 0;
  int y = 0;
  if (!(std::cin >> n >> m >> x >> y)) {
    return 0;
  }

  int *dist = new int[n * m];
  int maxDist = computeDistances(n, m, x - 1, y - 1, dist);
  printMountainMap(n, m, maxDist, dist);

  delete[] dist;
  return 0;
}
