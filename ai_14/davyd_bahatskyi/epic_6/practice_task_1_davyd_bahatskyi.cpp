/*
 * Task: Service Center Repair Queue (Custom Data Structures & RPN)
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */

#include <cctype>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>

// 1. Enums and core structs
enum class DeviceType { PHONE = 1, LAPTOP, TV };
enum class Status { WAITING, REPAIR, DONE };
enum class ActionType { ADD, DELETE };

struct Money {
  int hrn;
  int kop;

  // convert to total kopecks so float rounding cant mess up comparisons or sums
  long long toKop() const { return (long long)hrn * 100LL + kop; }

  static Money fromKop(long long total) {
    Money m;
    m.hrn = (int)(total / 100LL);
    m.kop = (int)(total % 100LL);
    return m;
  }

  Money operator+(const Money &other) const {
    return fromKop(toKop() + other.toKop());
  }

  Money operator-(const Money &other) const {
    return fromKop(toKop() - other.toKop());
  }

  Money operator*(int mult) const { return fromKop(toKop() * (long long)mult); }

  bool operator<(const Money &other) const { return toKop() < other.toKop(); }
};

// return os by reference so chaining like cout << a << b works
std::ostream &operator<<(std::ostream &os, const Money &m) {
  os << m.hrn << "." << (m.kop < 10 ? "0" : "") << m.kop << " UAH";
  return os;
}

struct Date {
  int day;
  int month;
  int year;
};

struct Client {
  char name[16];
  char phone[11];
};

// all 3 fields share the same memory because one order only describes one
// device
union DeviceInfo {
  int imei;
  char serial[12];
  int inches;
};

struct Order {
  int id;
  Client client;
  Date date;
  DeviceType type;
  DeviceInfo info;
  char problem[81];
  int priority;
  Money price;
  Status status;
  char masterName[24];
};

// format one table row using setw so columns line up even with varying lengths
std::ostream &operator<<(std::ostream &os, const Order &o) {
  char detBuf[32];
  if (o.type == DeviceType::PHONE) {
    std::snprintf(detBuf, sizeof(detBuf), "IMEI %06d", o.info.imei);
  } else if (o.type == DeviceType::LAPTOP) {
    std::snprintf(detBuf, sizeof(detBuf), "SN %s", o.info.serial);
  } else {
    std::snprintf(detBuf, sizeof(detBuf), "%d inch", o.info.inches);
  }

  const char *typeStr = (o.type == DeviceType::PHONE)    ? "PHONE"
                        : (o.type == DeviceType::LAPTOP) ? "LAPTOP"
                                                         : "TV";
  const char *statStr = (o.status == Status::WAITING)  ? "WAITING"
                        : (o.status == Status::REPAIR) ? "REPAIR"
                                                       : "DONE";

  char priceBuf[32];
  std::snprintf(priceBuf, sizeof(priceBuf), "%d.%02d", o.price.hrn,
                o.price.kop);

  char dateBuf[32];
  std::snprintf(dateBuf, sizeof(dateBuf), "%02d.%02d.%04d", o.date.day,
                o.date.month, o.date.year);

  os << "| " << std::setw(3) << o.id << " | " << std::left << std::setw(15)
     << o.client.name << " | " << std::setw(10) << o.client.phone << " | "
     << std::setw(10) << dateBuf << " | " << std::setw(6) << typeStr << " | "
     << std::setw(14) << detBuf << " | " << std::right << std::setw(2)
     << o.priority << " | " << std::left << std::setw(7) << statStr << " | "
     << std::right << std::setw(9) << priceBuf << " |";
  return os;
}

// 2. Safe input helpers
bool getLine(char *buf, int sz, bool &cut) {
  cut = false;
  if (!std::cin.getline(buf, sz)) {
    if (std::cin.eof()) {
      return false;
    }
    // if input is longer than buf, cin sets failbit and stops reading,
    // so clear the error flag and eat the leftover chars up to newline
    std::cin.clear();
    int ch = 0;
    while ((ch = std::cin.get()) != '\n' && ch != EOF) {
    }
    cut = true;
  }
  // strip '\r' in case input was pasted from CRLF line endings
  size_t len = std::strlen(buf);
  if (len > 0 && buf[len - 1] == '\r') {
    buf[len - 1] = '\0';
  }
  return true;
}

// atoi("2abc") silently gives 2 and empty "" gives 0, so check every char
// manually
bool toInt(const char *s, int &out) {
  if (!s || s[0] == '\0') {
    return false;
  }
  long long val = 0;
  for (int i = 0; s[i] != '\0'; ++i) {
    if (!std::isdigit((unsigned char)s[i])) {
      return false;
    }
    val = val * 10 + (s[i] - '0');
    if (val > 2147483647LL) {
      return false;
    }
  }
  out = static_cast<int>(val);
  return true;
}

// 3. RPN stack and price evaluator
struct RpnNode {
  Money val;
  RpnNode *next;
};

struct RpnStack {
  RpnNode *top = nullptr;
  int size = 0;

  void push(Money m) {
    RpnNode *node = new RpnNode{m, top};
    top = node;
    size++;
  }

  bool pop(Money &out) {
    if (!top) {
      return false;
    }
    out = top->val;
    RpnNode *tmp = top;
    top = top->next;
    delete tmp;
    size--;
    return true;
  }

  void clear() {
    Money dummy;
    while (pop(dummy)) {
    }
  }

  ~RpnStack() { clear(); }
};

bool parseNum(const char *tok, Money &m) {
  if (!tok || tok[0] == '\0') {
    return false;
  }
  int hrn = 0;
  int kop = 0;
  int dots = 0;
  int intDigs = 0;
  int fracDigs = 0;

  for (int i = 0; tok[i] != '\0'; ++i) {
    char c = tok[i];
    if (c == '.') {
      dots++;
      if (dots > 1) {
        return false;
      }
    } else if (std::isdigit((unsigned char)c)) {
      if (dots == 0) {
        intDigs++;
        if (intDigs > 6) {
          return false;
        }
        hrn = hrn * 10 + (c - '0');
      } else {
        fracDigs++;
        if (fracDigs > 2) {
          return false;
        }
        kop = kop * 10 + (c - '0');
      }
    } else {
      return false;
    }
  }

  // reject bare ".", ".5", or "10."
  if (intDigs == 0 || (dots == 1 && fracDigs == 0)) {
    return false;
  }
  // ".5" after a number means 50 kopecks, not 5
  if (fracDigs == 1) {
    kop *= 10;
  }

  m.hrn = hrn;
  m.kop = kop;
  return true;
}

bool evalRPN(const char *expr, Money &res) {
  if (!expr) {
    std::cout << "Expression error: empty expression.\n";
    return false;
  }

  // copy to local buffer because strtok modifies the string by writing '\0'
  char buf[256];
  std::strncpy(buf, expr, sizeof(buf) - 1);
  buf[sizeof(buf) - 1] = '\0';

  bool hasChar = false;
  for (int i = 0; buf[i]; ++i) {
    if (!std::isspace((unsigned char)buf[i])) {
      hasChar = true;
      break;
    }
  }
  if (!hasChar) {
    std::cout << "Expression error: empty expression.\n";
    return false;
  }

  RpnStack st;
  char *tok = std::strtok(buf, " \t\r\n");

  while (tok != nullptr) {
    if (std::strcmp(tok, "+") == 0 || std::strcmp(tok, "-") == 0 ||
        std::strcmp(tok, "*") == 0) {
      if (st.size < 2) {
        std::cout << "Expression error: insufficient operands for '" << tok
                  << "'.\n";
        st.clear();
        return false;
      }
      // stack is LIFO, so first pop is right operand b (10 3 - means 10 - 3)
      Money b, a;
      st.pop(b);
      st.pop(a);

      if (std::strcmp(tok, "+") == 0) {
        Money c = a + b;
        // check limit on every step so numbers cant overflow later
        if (c.toKop() > 10000000LL) {
          std::cout << "Expression error: amount exceeds 100000.00 UAH.\n";
          st.clear();
          return false;
        }
        st.push(c);
      } else if (std::strcmp(tok, "-") == 0) {
        if (a < b) {
          std::cout << "Expression error: intermediate result is negative.\n";
          st.clear();
          return false;
        }
        st.push(a - b);
      } else {
        if (b.kop != 0 || b.hrn < 1 || b.hrn > 100) {
          std::cout << "Expression error: multiplier must be an integer from 1 "
                       "to 100.\n";
          st.clear();
          return false;
        }
        long long total = a.toKop() * (long long)b.hrn;
        if (total > 10000000LL) {
          std::cout << "Expression error: amount exceeds 100000.00 UAH.\n";
          st.clear();
          return false;
        }
        st.push(Money::fromKop(total));
      }
    } else {
      Money m;
      if (!parseNum(tok, m)) {
        std::cout << "Expression error: '" << tok
                  << "' is not a valid number or operator.\n";
        st.clear();
        return false;
      }
      if (m.toKop() > 10000000LL) {
        std::cout << "Expression error: amount exceeds 100000.00 UAH.\n";
        st.clear();
        return false;
      }
      st.push(m);
    }
    tok = std::strtok(nullptr, " \t\r\n");
  }

  if (st.size != 1) {
    std::cout << "Expression error: numbers remaining in stack: " << st.size
              << ", expected 1.\n";
    st.clear();
    return false;
  }

  st.pop(res);
  if (res.toKop() == 0) {
    std::cout << "Expression error: final result cannot be 0.00 UAH.\n";
    return false;
  }
  return true;
}

// 4. Doubly linked list (journal)
struct OrderNode {
  Order order;
  OrderNode *prev;
  OrderNode *next;
};

struct OrderList {
  OrderNode *head = nullptr;
  OrderNode *tail = nullptr;
  int size = 0;

  void pushBack(const Order &o) {
    OrderNode *node = new OrderNode{o, tail, nullptr};
    if (!head) {
      head = tail = node;
    } else {
      tail->next = node;
      tail = node;
    }
    size++;
  }

  // handle all 4 cases (middle, head, tail, single node) so head/tail never
  // dangle
  bool remove(OrderNode *node) {
    if (!node) {
      return false;
    }
    if (node->prev) {
      node->prev->next = node->next;
    } else {
      head = node->next;
    }

    if (node->next) {
      node->next->prev = node->prev;
    } else {
      tail = node->prev;
    }

    delete node;
    size--;
    return true;
  }

  // swap prev and next in place so no extra memory is needed
  void revInPlace() {
    if (!head || head == tail) {
      return;
    }
    OrderNode *cur = head;
    OrderNode *tmp = nullptr;
    while (cur) {
      tmp = cur->prev;
      cur->prev = cur->next;
      cur->next = tmp;
      // step to cur->prev because prev and next just got swapped
      cur = cur->prev;
    }
    tmp = head;
    head = tail;
    tail = tmp;
  }

  void clear() {
    OrderNode *cur = head;
    while (cur) {
      OrderNode *nxt = cur->next;
      delete cur;
      cur = nxt;
    }
    head = tail = nullptr;
    size = 0;
  }

  ~OrderList() { clear(); }
};

// pass list as const& so we dont copy it and cant modify it by mistake
OrderNode *findById(const OrderList &list, int id) {
  OrderNode *cur = list.head;
  while (cur) {
    if (cur->order.id == id) {
      return cur;
    }
    cur = cur->next;
  }
  return nullptr;
}

// 5. Priority queue (stores pointers into journal instead of copying whole
// Orders)
struct QNode {
  Order *orderPtr;
  QNode *next;
};

struct PriorityQueue {
  QNode *head = nullptr;
  int size = 0;

  void push(Order *ord) {
    QNode *node = new QNode{ord, nullptr};
    // highest priority sits at head; >= skips equal priorities to keep FIFO
    // order
    if (!head || ord->priority > head->orderPtr->priority) {
      node->next = head;
      head = node;
    } else {
      QNode *cur = head;
      while (cur->next && cur->next->orderPtr->priority >= ord->priority) {
        cur = cur->next;
      }
      node->next = cur->next;
      cur->next = node;
    }
    size++;
  }

  Order *pop() {
    if (!head) {
      return nullptr;
    }
    QNode *tmp = head;
    Order *ret = head->orderPtr;
    head = head->next;
    delete tmp;
    size--;
    return ret;
  }

  bool remove(const Order *ord) {
    if (!head) {
      return false;
    }
    if (head->orderPtr == ord) {
      QNode *tmp = head;
      head = head->next;
      delete tmp;
      size--;
      return true;
    }
    QNode *cur = head;
    while (cur->next && cur->next->orderPtr != ord) {
      cur = cur->next;
    }
    if (cur->next) {
      QNode *tmp = cur->next;
      cur->next = cur->next->next;
      delete tmp;
      size--;
      return true;
    }
    return false;
  }

  void clear() {
    while (head) {
      QNode *tmp = head;
      head = head->next;
      delete tmp;
    }
    size = 0;
  }

  ~PriorityQueue() { clear(); }
};

// 6. Circular list of masters
struct Master {
  char name[24];
  int completedCount;
  Money revenue;
  Master *next;
};

struct MasterRing {
  Master *head = nullptr;
  Master *current = nullptr;
  int count = 0;

  bool init(int n, char names[][24]) {
    if (n <= 0) {
      return false;
    }
    count = n;
    Master *prev = nullptr;
    for (int i = 0; i < n; ++i) {
      Master *m = new Master;
      std::strncpy(m->name, names[i], sizeof(m->name) - 1);
      m->name[sizeof(m->name) - 1] = '\0';
      m->completedCount = 0;
      m->revenue = Money{0, 0};
      m->next = nullptr;

      if (!head) {
        head = m;
      } else {
        prev->next = m;
      }
      prev = m;
    }
    // tie tail back to head so assignment loops forever round-robin
    prev->next = head;
    current = head;
    return true;
  }

  Master *nextMaster() {
    if (!current) {
      return nullptr;
    }
    Master *res = current;
    current = current->next;
    return res;
  }

  Master *findByName(const char *name) {
    if (!head) {
      return nullptr;
    }
    Master *cur = head;
    do {
      if (std::strcmp(cur->name, name) == 0) {
        return cur;
      }
      cur = cur->next;
    } while (cur != head);
    return nullptr;
  }

  void clear() {
    if (!head) {
      return;
    }
    Master *cur = head;
    // loop count times instead of while(cur) because a circle has no nullptr
    for (int i = 0; i < count; ++i) {
      Master *nxt = cur->next;
      delete cur;
      cur = nxt;
    }
    head = current = nullptr;
    count = 0;
  }

  ~MasterRing() { clear(); }
};

// 7. Action stack (undo history)
struct Action {
  ActionType type;
  Order orderCopy;
  Action *next;
};

struct ActionStack {
  Action *top = nullptr;

  void push(ActionType t, const Order &o) {
    Action *a = new Action{t, o, top};
    top = a;
  }

  bool pop(ActionType &t, Order &o) {
    if (!top) {
      return false;
    }
    t = top->type;
    o = top->orderCopy;
    Action *tmp = top;
    top = top->next;
    delete tmp;
    return true;
  }

  void clear() {
    while (top) {
      Action *tmp = top;
      top = top->next;
      delete tmp;
    }
  }

  ~ActionStack() { clear(); }
};

// 8. Validation, recursion, and QuickSort
bool isLeap(int y) { return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0); }

bool chkDate(const char *s, Date &d) {
  if (std::strlen(s) != 10 || s[2] != '.' || s[5] != '.') {
    return false;
  }
  for (int i = 0; i < 10; ++i) {
    if (i == 2 || i == 5) {
      continue;
    }
    if (!std::isdigit((unsigned char)s[i])) {
      return false;
    }
  }
  int day = (s[0] - '0') * 10 + (s[1] - '0');
  int mon = (s[3] - '0') * 10 + (s[4] - '0');
  int yr = (s[6] - '0') * 1000 + (s[7] - '0') * 100 + (s[8] - '0') * 10 +
           (s[9] - '0');

  if (yr < 2000 || yr > 2099 || mon < 1 || mon > 12) {
    return false;
  }

  int daysInMon[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (mon == 2 && isLeap(yr)) {
    daysInMon[2] = 29;
  }
  if (day < 1 || day > daysInMon[mon]) {
    return false;
  }

  d.day = day;
  d.month = mon;
  d.year = yr;
  return true;
}

bool chkPhone(const char *ph) {
  if (std::strlen(ph) != 10 || ph[0] != '0') {
    return false;
  }
  for (int i = 0; i < 10; ++i) {
    if (!std::isdigit((unsigned char)ph[i])) {
      return false;
    }
  }
  return true;
}

bool chkName(const char *nm) {
  size_t len = std::strlen(nm);
  if (len < 1 || len > 15) {
    return false;
  }
  for (size_t i = 0; i < len; ++i) {
    if (!std::isalpha((unsigned char)nm[i])) {
      return false;
    }
  }
  return true;
}

// recursively sum prices of DONE orders from current node to tail
Money revenue(const OrderNode *p) {
  if (!p) {
    return Money{0, 0};
  }
  Money rest = revenue(p->next);
  if (p->order.status == Status::DONE) {
    return p->order.price + rest;
  }
  return rest;
}

// sort only a temp array of pointers so we dont disturb the original journal
void qSort(Order **arr, int l, int r) {
  if (l >= r) {
    return;
  }
  Order *pivot = arr[l + (r - l) / 2];
  int i = l;
  int j = r;

  while (i <= j) {
    // higher price comes first; if price ties, lower ID comes first
    while (pivot->price < arr[i]->price ||
           (!(arr[i]->price < pivot->price) && arr[i]->id < pivot->id)) {
      i++;
    }
    while (arr[j]->price < pivot->price ||
           (!(pivot->price < arr[j]->price) && pivot->id < arr[j]->id)) {
      j--;
    }
    if (i <= j) {
      Order *t = arr[i];
      arr[i] = arr[j];
      arr[j] = t;
      i++;
      j--;
    }
  }
  qSort(arr, l, j);
  qSort(arr, i, r);
}

// 9. Menu handlers
int g_nextId = 101;

void mAdd(OrderList &jrn, PriorityQueue &pq, ActionStack &acts) {
  char nameBuf[64], phoneBuf[64], dateBuf[64], typeBuf[64], infoBuf[64];
  char probBuf[128], prioBuf[64], priceBuf[256];
  bool cut = false;

  std::cout << "Client name: ";
  if (!getLine(nameBuf, sizeof(nameBuf), cut) || cut || !chkName(nameBuf)) {
    std::cout << "Error: name must contain 1 to 15 Latin letters.\n";
    return;
  }

  std::cout << "Phone (10 digits): ";
  if (!getLine(phoneBuf, sizeof(phoneBuf), cut) || cut || !chkPhone(phoneBuf)) {
    std::cout << "Error: phone must be 10 digits starting with 0.\n";
    return;
  }

  std::cout << "Intake date (DD.MM.YYYY): ";
  Date d{};
  if (!getLine(dateBuf, sizeof(dateBuf), cut) || cut || !chkDate(dateBuf, d)) {
    std::cout << "Error: invalid date.\n";
    return;
  }

  std::cout << "Device type (1 phone, 2 laptop, 3 TV): ";
  if (!getLine(typeBuf, sizeof(typeBuf), cut) || cut ||
      std::strlen(typeBuf) != 1 || typeBuf[0] < '1' || typeBuf[0] > '3') {
    std::cout << "Error: device type must be 1, 2, or 3.\n";
    return;
  }
  DeviceType dt = (DeviceType)(typeBuf[0] - '0');
  DeviceInfo dInfo{};

  if (dt == DeviceType::PHONE) {
    std::cout << "Last 6 digits of IMEI: ";
    if (!getLine(infoBuf, sizeof(infoBuf), cut) || cut ||
        std::strlen(infoBuf) != 6) {
      std::cout << "Error: exactly 6 digits required.\n";
      return;
    }
    int imeiVal = 0;
    if (!toInt(infoBuf, imeiVal)) {
      std::cout << "Error: exactly 6 digits required.\n";
      return;
    }
    dInfo.imei = imeiVal;
  } else if (dt == DeviceType::LAPTOP) {
    std::cout << "Serial number: ";
    if (!getLine(infoBuf, sizeof(infoBuf), cut) || cut) {
      std::cout << "Error: invalid serial number.\n";
      return;
    }
    size_t slen = std::strlen(infoBuf);
    if (slen < 1 || slen > 11) {
      std::cout << "Error: invalid serial number.\n";
      return;
    }
    for (size_t i = 0; i < slen; ++i) {
      if (!std::isupper((unsigned char)infoBuf[i]) &&
          !std::isdigit((unsigned char)infoBuf[i])) {
        std::cout << "Error: invalid serial number.\n";
        return;
      }
    }
    std::strncpy(dInfo.serial, infoBuf, sizeof(dInfo.serial) - 1);
    dInfo.serial[sizeof(dInfo.serial) - 1] = '\0';
  } else {
    std::cout << "Screen diagonal (19-100 inches): ";
    int inch = 0;
    if (!getLine(infoBuf, sizeof(infoBuf), cut) || cut ||
        !toInt(infoBuf, inch) || inch < 19 || inch > 100) {
      std::cout << "Error: invalid diagonal.\n";
      return;
    }
    dInfo.inches = inch;
  }

  std::cout << "Problem description: ";
  if (!getLine(probBuf, sizeof(probBuf), cut) || cut ||
      std::strlen(probBuf) < 1 || std::strlen(probBuf) > 80) {
    std::cout << "Error: invalid description.\n";
    return;
  }

  std::cout << "Priority (1 normal, 2 elevated, 3 urgent): ";
  if (!getLine(prioBuf, sizeof(prioBuf), cut) || cut ||
      std::strlen(prioBuf) != 1 || prioBuf[0] < '1' || prioBuf[0] > '3') {
    std::cout << "Error: priority must be 1, 2, or 3.\n";
    return;
  }
  int prio = prioBuf[0] - '0';

  std::cout << "Price (RPN expression): ";
  if (!getLine(priceBuf, sizeof(priceBuf), cut) || cut) {
    std::cout << "Expression error: expression is too long or invalid.\n";
    return;
  }
  Money pr{0, 0};
  if (!evalRPN(priceBuf, pr)) {
    return;
  }

  Order o{};
  o.id = g_nextId++;
  std::strncpy(o.client.name, nameBuf, sizeof(o.client.name) - 1);
  o.client.name[sizeof(o.client.name) - 1] = '\0';
  std::strncpy(o.client.phone, phoneBuf, sizeof(o.client.phone) - 1);
  o.client.phone[sizeof(o.client.phone) - 1] = '\0';
  o.date = d;
  o.type = dt;
  o.info = dInfo;
  std::strncpy(o.problem, probBuf, sizeof(o.problem) - 1);
  o.problem[sizeof(o.problem) - 1] = '\0';
  o.priority = prio;
  o.price = pr;
  o.status = Status::WAITING;
  o.masterName[0] = '\0';

  // add to journal first so pq points to the live node sitting at jrn.tail
  jrn.pushBack(o);
  pq.push(&(jrn.tail->order));
  acts.push(ActionType::ADD, o);

  std::cout << "Order #" << o.id << " added: price " << o.price
            << ", in repair queue: " << pq.size << ".\n";
}

void mShow(const OrderList &jrn, const PriorityQueue &pq) {
  if (jrn.size == 0) {
    std::cout << "Journal is empty.\n";
    return;
  }
  std::cout << "+-----+-----------------+------------+------------+--------+---"
               "-------------+----+---------+-----------+\n";
  std::cout << "|  ID | Client          | Phone      | Date       | Type   | "
               "Details        | Pr | Status  |     Price |\n";
  std::cout << "+-----+-----------------+------------+------------+--------+---"
               "-------------+----+---------+-----------+\n";

  OrderNode *cur = jrn.head;
  while (cur) {
    std::cout << cur->order << "\n";
    cur = cur->next;
  }
  std::cout << "+-----+-----------------+------------+------------+--------+---"
               "-------------+----+---------+-----------+\n";
  std::cout << "Total orders: " << jrn.size << ", in repair queue: " << pq.size
            << "\n";
}

void mAssign(PriorityQueue &pq, MasterRing &masters) {
  if (pq.size == 0) {
    std::cout << "Repair queue is empty.\n";
    return;
  }
  Order *ord = pq.pop();
  Master *m = masters.nextMaster();

  ord->status = Status::REPAIR;
  std::strncpy(ord->masterName, m->name, sizeof(ord->masterName) - 1);
  ord->masterName[sizeof(ord->masterName) - 1] = '\0';

  std::cout << "Order #" << ord->id << " (priority " << ord->priority
            << ") assigned to master " << m->name << ".\n";
  std::cout << "Problem: " << ord->problem << "\n";
  std::cout << "Remaining in queue: " << pq.size << "\n";
}

void mCompRep(OrderList &jrn, MasterRing &masters) {
  char idBuf[64];
  bool cut = false;
  std::cout << "Order ID: ";
  if (!getLine(idBuf, sizeof(idBuf), cut)) {
    return;
  }

  int id = 0;
  if (cut || !toInt(idBuf, id)) {
    std::cout << "Error: order ID must be an integer.\n";
    return;
  }

  OrderNode *node = findById(jrn, id);
  if (!node) {
    std::cout << "Order #" << id << " not found.\n";
    return;
  }
  if (node->order.status == Status::WAITING) {
    std::cout << "Order #" << id << " has not been assigned to a master yet.\n";
    return;
  }
  if (node->order.status == Status::DONE) {
    std::cout << "Order #" << id << " is already completed.\n";
    return;
  }

  node->order.status = Status::DONE;
  Master *m = masters.findByName(node->order.masterName);
  if (m) {
    m->completedCount++;
    m->revenue = m->revenue + node->order.price;
    std::cout << "Order #" << id << " completed. Master " << m->name
              << ": completed " << m->completedCount << ", revenue "
              << m->revenue << ".\n";
  }
}

void mDel(OrderList &jrn, PriorityQueue &pq, ActionStack &acts) {
  char idBuf[64];
  bool cut = false;
  std::cout << "Order ID: ";
  if (!getLine(idBuf, sizeof(idBuf), cut)) {
    return;
  }

  int id = 0;
  if (cut || !toInt(idBuf, id)) {
    std::cout << "Error: order ID must be an integer.\n";
    return;
  }

  OrderNode *node = findById(jrn, id);
  if (!node) {
    std::cout << "Order #" << id << " not found.\n";
    return;
  }
  if (node->order.status != Status::WAITING) {
    std::cout << "Only orders waiting in the queue can be deleted.\n";
    return;
  }

  // save a copy for undo and remove from pq BEFORE freeing node in jrn
  Order copy = node->order;
  pq.remove(&(node->order));
  jrn.remove(node);
  acts.push(ActionType::DELETE, copy);

  std::cout << "Order #" << id << " deleted. In journal: " << jrn.size
            << ", in queue: " << pq.size << ".\n";
}

void mUndo(OrderList &jrn, PriorityQueue &pq, ActionStack &acts) {
  if (!acts.top) {
    std::cout << "No actions to undo.\n";
    return;
  }

  ActionType t;
  Order o;
  acts.pop(t, o);

  if (t == ActionType::ADD) {
    OrderNode *node = findById(jrn, o.id);
    if (node && node->order.status == Status::WAITING) {
      pq.remove(&(node->order));
      jrn.remove(node);
      std::cout << "Undid adding order #" << o.id
                << ": removed from journal and queue.\n";
    } else {
      std::cout << "Cannot undo adding order #" << o.id
                << ": already assigned to a master.\n";
    }
  } else {
    // restore deleted order back to tail of journal and re-insert into queue
    jrn.pushBack(o);
    pq.push(&(jrn.tail->order));
    std::cout << "Undid deleting order #" << o.id
              << ": restored to end of journal and queue.\n";
  }
}

void mRep(const OrderList &jrn, const MasterRing &masters) {
  if (jrn.size == 0) {
    std::cout << "Journal is empty.\n";
    return;
  }

  Order **arr = new Order *[jrn.size];
  OrderNode *cur = jrn.head;
  for (int i = 0; i < jrn.size; ++i) {
    arr[i] = &(cur->order);
    cur = cur->next;
  }

  qSort(arr, 0, jrn.size - 1);

  std::cout << "Orders by price:\n";
  for (int i = 0; i < jrn.size; ++i) {
    char priceBuf[32];
    std::snprintf(priceBuf, sizeof(priceBuf), "%d.%02d", arr[i]->price.hrn,
                  arr[i]->price.kop);
    const char *stStr = (arr[i]->status == Status::WAITING)  ? "WAITING"
                        : (arr[i]->status == Status::REPAIR) ? "REPAIR"
                                                             : "DONE";
    std::cout << "  #" << arr[i]->id << "  " << std::right << std::setw(9)
              << priceBuf << " UAH  " << std::left << stStr << "\n";
  }

  Money diff = arr[0]->price - arr[jrn.size - 1]->price;
  std::cout << "Difference between highest and lowest price: " << diff << "\n";

  // free the temporary pointer array right after printing so nothing leaks
  delete[] arr;

  Money totalRev = revenue(jrn.head);
  std::cout << "Total revenue from completed repairs: " << totalRev << "\n";

  std::cout << "Masters starting from next in rotation:\n";
  if (masters.current) {
    Master *m = masters.current;
    // do-while guarantees the starting master is checked after stepping, not
    // before
    do {
      std::cout << "  " << std::left << std::setw(12) << m->name
                << " completed: " << m->completedCount
                << ", revenue: " << m->revenue << "\n";
      m = m->next;
    } while (m != masters.current);
  }
}

void mRev(OrderList &jrn) {
  if (jrn.size == 0) {
    std::cout << "Journal is empty.\n";
    return;
  }
  jrn.revInPlace();
  std::cout << "Journal reversed: first order is now #" << jrn.head->order.id
            << ", last is #" << jrn.tail->order.id << ".\n";
}

// 10. Main & setup
int main() {
  char countBuf[64];
  bool cut = false;
  std::cout << "Number of masters (1 to 5): ";
  if (!getLine(countBuf, sizeof(countBuf), cut)) {
    return 0;
  }

  int n = 0;
  if (cut || !toInt(countBuf, n) || n < 1 || n > 5) {
    std::cout << "Error: number of masters must be from 1 to 5.\n";
    return 0;
  }

  char namesLine[256];
  std::cout << "Master names separated by spaces: ";
  if (!getLine(namesLine, sizeof(namesLine), cut)) {
    return 0;
  }
  if (cut) {
    std::cout << "Error: master names input is too long.\n";
    return 0;
  }

  char masterNames[5][24];
  int parsed = 0;
  char *tok = std::strtok(namesLine, " \t\r\n");

  while (tok != nullptr) {
    if (parsed >= n) {
      parsed++;
      break;
    }
    size_t tlen = std::strlen(tok);
    if (tlen < 1 || tlen > 23) {
      std::cout << "Error: expected " << n
                << " names of Latin letters (max 23 chars each).\n";
      return 0;
    }
    for (size_t i = 0; i < tlen; ++i) {
      if (!std::isalpha((unsigned char)tok[i])) {
        std::cout << "Error: expected " << n
                  << " names of Latin letters (max 23 chars each).\n";
        return 0;
      }
    }
    std::strncpy(masterNames[parsed], tok, 23);
    masterNames[parsed][23] = '\0';
    parsed++;
    tok = std::strtok(nullptr, " \t\r\n");
  }

  if (parsed != n) {
    std::cout << "Error: expected " << n
              << " names of Latin letters (max 23 chars each).\n";
    return 0;
  }

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (std::strcmp(masterNames[i], masterNames[j]) == 0) {
        std::cout << "Error: master names must be unique.\n";
        return 0;
      }
    }
  }

  MasterRing masters;
  masters.init(n, masterNames);

  OrderList jrn;
  PriorityQueue pq;
  ActionStack acts;

  char choiceBuf[64];
  while (true) {
    std::cout << "\nMenu: 1-Add, 2-Journal, 3-Assign, 4-Complete, 5-Delete, "
                 "6-Undo, 7-Report, 8-Reverse, 0-Exit\n";

    std::cout << "Your choice: ";
    if (!getLine(choiceBuf, sizeof(choiceBuf), cut)) {
      break;
    }

    int choice = -1;
    if (cut || !toInt(choiceBuf, choice)) {
      std::cout << "Error: enter a menu item number.\n";
      continue;
    }
    if (choice < 0 || choice > 8) {
      std::cout << "Error: menu item " << choice << " does not exist.\n";
      continue;
    }
    if (choice == 0) {
      break;
    }

    switch (choice) {
    case 1:
      mAdd(jrn, pq, acts);
      break;
    case 2:
      mShow(jrn, pq);
      break;
    case 3:
      mAssign(pq, masters);
      break;
    case 4:
      mCompRep(jrn, masters);
      break;
    case 5:
      mDel(jrn, pq, acts);
      break;
    case 6:
      mUndo(jrn, pq, acts);
      break;
    case 7:
      mRep(jrn, masters);
      break;
    case 8:
      mRev(jrn);
      break;
    }
  }

  // all 4 structures clean up automatically via destructors when main exits
  return 0;
}
