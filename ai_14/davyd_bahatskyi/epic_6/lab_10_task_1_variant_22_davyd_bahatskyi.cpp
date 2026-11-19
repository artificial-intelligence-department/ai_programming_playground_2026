/*
 * Task: Lab 10, Variant 22 - Doubly Linked List with char* key
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */

#include <cerrno>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int MAX_KEY_LEN = 256;

struct Node {
  char *key;
  Node *prev;
  Node *next;
};

struct DblLinkedList {
  Node *head;
  Node *tail;
  size_t size;
};

void clearInputBuffer() {
  int ch = 0;
  while ((ch = std::getchar()) != '\n' && ch != EOF) {
  }
}

bool readLine(const char *prompt, char *buffer, int maxLen) {
  if (prompt != nullptr) {
    std::printf("%s", prompt);
  }
  if (std::fgets(buffer, maxLen, stdin) == nullptr) {
    return false;
  }

  size_t len = std::strlen(buffer);
  if (len > 0 && buffer[len - 1] == '\n') {
    buffer[len - 1] = '\0';
    --len;
  } else {
    clearInputBuffer();
  }

  if (len > 0 && buffer[len - 1] == '\r') {
    buffer[len - 1] = '\0';
  }
  return true;
}

int readNonNegativeInt(const char *prompt) {
  char buf[64];
  while (true) {
    if (!readLine(prompt, buf, sizeof(buf))) {
      return 0;
    }
    if (buf[0] == '\0') {
      std::printf("Invalid input. Please enter a non-negative integer.\n");
      continue;
    }

    errno = 0;
    char *endPtr = nullptr;
    long val = std::strtol(buf, &endPtr, 10);
    while (*endPtr == ' ' || *endPtr == '\t') {
      ++endPtr;
    }

    if (errno == ERANGE || *endPtr != '\0' || val < 0 || val > INT_MAX) {
      std::printf("Invalid input. Please enter a non-negative integer.\n");
      continue;
    }
    return static_cast<int>(val);
  }
}

char *duplicateString(const char *src) {
  size_t len = std::strlen(src);
  char *copy = new char[len + 1];
  std::strcpy(copy, src);
  return copy;
}

Node *createNode(const char *key) {
  Node *node = new Node;
  node->key = duplicateString(key);
  node->prev = nullptr;
  node->next = nullptr;
  return node;
}

DblLinkedList *createList() {
  DblLinkedList *list = new DblLinkedList;
  list->head = nullptr;
  list->tail = nullptr;
  list->size = 0;
  return list;
}

void pushBack(DblLinkedList *list, const char *key) {
  if (list == nullptr) {
    return;
  }

  Node *node = createNode(key);
  node->prev = list->tail;
  if (list->tail != nullptr) {
    list->tail->next = node;
  } else {
    list->head = node;
  }
  list->tail = node;
  ++list->size;
}

void printList(const DblLinkedList *list) {
  if (list == nullptr || list->head == nullptr) {
    std::printf("List is empty.\n");
    return;
  }

  const Node *cur = list->head;
  while (cur != nullptr) {
    std::printf("%s", cur->key);
    if (cur->next != nullptr) {
      std::printf(" <-> ");
    }
    cur = cur->next;
  }
  std::printf(" (size: %zu)\n", list->size);
}

Node *findByKey(const DblLinkedList *list, const char *key) {
  if (list == nullptr || key == nullptr) {
    return nullptr;
  }

  Node *cur = list->head;
  while (cur != nullptr) {
    if (std::strcmp(cur->key, key) == 0) {
      return cur;
    }
    cur = cur->next;
  }
  return nullptr;
}

bool deleteByKey(DblLinkedList *list, const char *key) {
  Node *target = findByKey(list, key);
  if (target == nullptr) {
    return false;
  }

  if (target->prev != nullptr) {
    target->prev->next = target->next;
  } else {
    list->head = target->next;
  }

  if (target->next != nullptr) {
    target->next->prev = target->prev;
  } else {
    list->tail = target->prev;
  }

  delete[] target->key;
  delete target;
  --list->size;
  return true;
}

bool insertKBeforeKey(DblLinkedList *list, const char *targetKey, int k) {
  Node *target = findByKey(list, targetKey);
  if (target == nullptr) {
    return false;
  }

  char keyBuf[MAX_KEY_LEN];
  for (int i = 0; i < k; ++i) {
    std::printf("Enter key for new element %d of %d: ", i + 1, k);
    if (!readLine(nullptr, keyBuf, sizeof(keyBuf))) {
      return false;
    }

    Node *newNode = createNode(keyBuf);
    newNode->next = target;
    newNode->prev = target->prev;

    if (target->prev != nullptr) {
      target->prev->next = newNode;
    } else {
      list->head = newNode;
    }
    target->prev = newNode;
    ++list->size;
  }
  return true;
}

void destroyList(DblLinkedList **list) {
  if (list == nullptr || *list == nullptr) {
    return;
  }

  Node *cur = (*list)->head;
  while (cur != nullptr) {
    Node *next = cur->next;
    delete[] cur->key;
    delete cur;
    cur = next;
  }

  delete *list;
  *list = nullptr;
}

int main() {
  DblLinkedList *list = createList();
  std::printf("Initial list state:\n");
  printList(list);

  int initialCount = readNonNegativeInt("Enter initial number of elements: ");
  char keyBuf[MAX_KEY_LEN];
  for (int i = 0; i < initialCount; ++i) {
    std::printf("Enter key for element %d: ", i + 1);
    if (readLine(nullptr, keyBuf, sizeof(keyBuf))) {
      pushBack(list, keyBuf);
    }
  }

  std::printf("\nList after creation:\n");
  printList(list);

  if (readLine("\nEnter key of element to delete: ", keyBuf, sizeof(keyBuf))) {
    if (deleteByKey(list, keyBuf)) {
      std::printf("Element \"%s\" deleted.\n", keyBuf);
    } else {
      std::printf("Element \"%s\" not found. Nothing deleted.\n", keyBuf);
    }
  }

  std::printf("List after deletion:\n");
  printList(list);

  if (readLine("\nEnter target key before which to insert: ", keyBuf,
               sizeof(keyBuf))) {
    if (findByKey(list, keyBuf) == nullptr) {
      std::printf("Target key \"%s\" not found. Insertion skipped.\n", keyBuf);
    } else {
      int k = readNonNegativeInt("Enter count K of elements to insert: ");
      insertKBeforeKey(list, keyBuf, k);
    }
  }

  std::printf("List after insertion:\n");
  printList(list);

  destroyList(&list);
  std::printf("\nList after destruction:\n");
  printList(list);

  return 0;
}
