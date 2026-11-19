/*
 * Task: Algotester Lab 78v2 (Part 2) - Dynamic Array Class Template
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */

#include <cstring>
#include <iostream>

template <typename T> class DynamicArray {
private:
  size_t m_size;
  size_t m_capacity;
  T *m_data;

public:
  DynamicArray() : m_size(0), m_capacity(1), m_data(new T[1]) {}

  DynamicArray(const DynamicArray &other)
      : m_size(other.m_size), m_capacity(other.m_capacity),
        m_data(new T[other.m_capacity]) {
    for (size_t i = 0; i < m_size; ++i) {
      m_data[i] = other.m_data[i];
    }
  }

  DynamicArray &operator=(const DynamicArray &other) {
    if (this != &other) {
      T *newData = new T[other.m_capacity];
      for (size_t i = 0; i < other.m_size; ++i) {
        newData[i] = other.m_data[i];
      }
      delete[] m_data;
      m_data = newData;
      m_size = other.m_size;
      m_capacity = other.m_capacity;
    }
    return *this;
  }

  ~DynamicArray() { delete[] m_data; }

  size_t size() const { return m_size; }

  size_t capacity() const { return m_capacity; }

  T &operator[](size_t index) { return m_data[index]; }

  const T &operator[](size_t index) const { return m_data[index]; }

  void insert(size_t index, const T *values, size_t count) {
    if (count == 0) {
      return;
    }

    size_t newSize = m_size + count;
    if (newSize >= m_capacity) {
      size_t newCapacity = m_capacity;
      while (newSize >= newCapacity) {
        newCapacity *= 2;
      }
      T *newData = new T[newCapacity];
      for (size_t i = 0; i < index; ++i) {
        newData[i] = m_data[i];
      }
      for (size_t i = 0; i < count; ++i) {
        newData[index + i] = values[i];
      }
      for (size_t i = index; i < m_size; ++i) {
        newData[i + count] = m_data[i];
      }
      delete[] m_data;
      m_data = newData;
      m_capacity = newCapacity;
    } else {
      for (size_t i = m_size; i > index; --i) {
        m_data[i + count - 1] = m_data[i - 1];
      }
      for (size_t i = 0; i < count; ++i) {
        m_data[index + i] = values[i];
      }
    }

    m_size = newSize;
  }

  void erase(size_t index, size_t count) {
    if (count == 0 || index >= m_size) {
      return;
    }
    if (index + count > m_size) {
      count = m_size - index;
    }

    for (size_t i = index; i + count < m_size; ++i) {
      m_data[i] = m_data[i + count];
    }
    m_size -= count;
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const DynamicArray<T> &arr) {
    for (size_t i = 0; i < arr.m_size; ++i) {
      if (i > 0) {
        os << ' ';
      }
      os << arr.m_data[i];
    }
    return os;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int q = 0;
  if (!(std::cin >> q)) {
    return 0;
  }

  DynamicArray<int> arr;
  char cmd[32];

  for (int qi = 0; qi < q; ++qi) {
    std::cin >> cmd;
    if (std::strcmp(cmd, "insert") == 0) {
      size_t index = 0;
      size_t n = 0;
      std::cin >> index >> n;
      int *values = (n > 0) ? new int[n] : nullptr;
      for (size_t i = 0; i < n; ++i) {
        std::cin >> values[i];
      }
      arr.insert(index, values, n);
      delete[] values;
    } else if (std::strcmp(cmd, "erase") == 0) {
      size_t index = 0;
      size_t n = 0;
      std::cin >> index >> n;
      arr.erase(index, n);
    } else if (std::strcmp(cmd, "size") == 0) {
      std::cout << arr.size() << '\n';
    } else if (std::strcmp(cmd, "capacity") == 0) {
      std::cout << arr.capacity() << '\n';
    } else if (std::strcmp(cmd, "get") == 0) {
      size_t index = 0;
      std::cin >> index;
      std::cout << arr[index] << '\n';
    } else if (std::strcmp(cmd, "set") == 0) {
      size_t index = 0;
      int value = 0;
      std::cin >> index >> value;
      arr[index] = value;
    } else if (std::strcmp(cmd, "print") == 0) {
      std::cout << arr << '\n';
    }
  }

  return 0;
}
