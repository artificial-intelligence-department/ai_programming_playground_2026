#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cctype>

using namespace std;

// ==========================================
//                   ENUM
// ==========================================

enum class DeviceType {
    PHONE = 1,
    LAPTOP = 2,
    TV = 3
};

enum class Status {
    WAITING,
    REPAIR,
    DONE
};

enum class ActionType {
    ADD,
    REMOVE
};

const char* statusToStr(Status s) {
    switch (s) {
        case Status::WAITING: return "WAITING";
        case Status::REPAIR:  return "REPAIR";
        case Status::DONE:    return "DONE";
        default:              return "UNKNOWN";
    }
}

const char* deviceTypeToStr(DeviceType t) {
    switch (t) {
        case DeviceType::PHONE:  return "PHONE";
        case DeviceType::LAPTOP: return "LAPTOP";
        case DeviceType::TV:     return "TV";
        default:                 return "UNKNOWN";
    }
}

// ==========================================
//                 СТРУКТУРИ
// ==========================================

struct Money {
    int hrn;
    int kop;
};

struct Date {
    int day;
    int month;
    int year;
};

struct Client {
    char name[16];
    char phone[11];
};

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

struct OrderNode {
    Order order;
    OrderNode* prev;
    OrderNode* next;
};

struct OrderList {
    OrderNode* head;
    OrderNode* tail;
    int size;
};

struct QNode {
    Order* order;
    QNode* next;
};

struct PriorityQueue {
    QNode* head;
    int size;
};

struct Master {
    char name[24];
    int completedCount;
    Money revenue;
    Master* next;
};

struct Action {
    ActionType type;
    Order orderCopy;
    Action* next;
};

struct ActionStack {
    Action* top;
};

struct RpnNode {
    Money val;
    RpnNode* next;
};

// ==========================================
//                   ДАТИ
// ==========================================

bool isLeapYear(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int daysInMonth(int month, int year) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            return 0;
    }
}

// ==========================================
//                   MONEY
// ==========================================

Money normalizeMoney(long long totalKop) {
    int hrn = static_cast<int>(totalKop / 100);
    int kop = static_cast<int>(totalKop % 100);
    return Money{hrn, kop};
}

long long toKop(const Money& m) {
    return static_cast<long long>(m.hrn) * 100 + m.kop;
}

Money operator+(const Money& a, const Money& b) {
    long long kop = toKop(a) + toKop(b);
    return normalizeMoney(kop);
}

Money operator-(const Money& a, const Money& b) {
    long long kop = toKop(a) - toKop(b);
    return normalizeMoney(kop);
}

Money operator*(const Money& a, int factor) {
    long long kop = toKop(a) * static_cast<long long>(factor);
    return normalizeMoney(kop);
}

bool operator<(const Money& a, const Money& b) {
    return toKop(a) < toKop(b);
}

ostream& operator<<(ostream& os, const Money& m) {
    int absHrn = (m.hrn >= 0) ? m.hrn : -m.hrn;
    int absKop = (m.kop >= 0) ? m.kop : -m.kop;
    if (m.hrn < 0 || m.kop < 0) {
        os << '-';
    }
    os << absHrn << '.' << setfill('0') << setw(2) << absKop;
    os << setfill(' ');
    return os;
}

// ==========================================
//                 ВАЛІДАЦІЯ
// ==========================================

bool isValidLatinWord(const char* s, int maxLen) {
    if (s == nullptr || maxLen < 1) return false;
    int len = static_cast<int>(strlen(s));
    if (len < 1 || len > maxLen) return false;
    for (int i = 0; i < len; ++i) {
        if (!isalpha(static_cast<unsigned char>(s[i]))) {
            return false;
        }
    }
    return true;
}

bool isValidPhone(const char* s) {
    if (s == nullptr) return false;
    if (strlen(s) != 10) return false;
    if (s[0] != '0') return false;
    for (int i = 0; i < 10; ++i) {
        if (!isdigit(static_cast<unsigned char>(s[i]))) {
            return false;
        }
    }
    return true;
}

bool parseAndValidateDate(const char* s, Date& outDate) {
    if (s == nullptr || strlen(s) != 10) return false;
    if (s[2] != '.' || s[5] != '.') return false;

    for (int i = 0; i < 10; ++i) {
        if (i == 2 || i == 5) continue;
        if (!isdigit(static_cast<unsigned char>(s[i]))) {
            return false;
        }
    }

    int d = 0, m = 0, y = 0;
    if (sscanf(s, "%2d.%2d.%4d", &d, &m, &y) != 3) {
        return false;
    }

    if (y < 2000 || y > 2099) return false;
    if (m < 1 || m > 12) return false;
    int maxD = daysInMonth(m, y);
    if (d < 1 || d > maxD) return false;

    outDate.day = d;
    outDate.month = m;
    outDate.year = y;
    return true;
}

bool parseIntStrict(const char* s, int& outVal) {
    if (s == nullptr || s[0] == '\0') return false;

    int i = 0;
    bool neg = false;
    if (s[0] == '-') {
        neg = true;
        i = 1;
        if (s[i] == '\0') return false;
    }

    long long acc = 0;
    for (; s[i] != '\0'; ++i) {
        if (!isdigit(static_cast<unsigned char>(s[i]))) {
            return false;
        }
        acc = acc * 10 + (s[i] - '0');
        if (!neg && acc > 2147483647LL) return false;
        if (neg && -acc < -2147483648LL) return false;
    }

    outVal = static_cast<int>(neg ? -acc : acc);
    return true;
}

bool parseAndValidateDeviceInfo(DeviceType type, const char* raw, DeviceInfo& outInfo) {
    if (raw == nullptr) return false;
    int len = static_cast<int>(strlen(raw));

    if (type == DeviceType::PHONE) {
        if (len != 6) return false;
        int val = 0;
        for (int i = 0; i < 6; ++i) {
            if (!isdigit(static_cast<unsigned char>(raw[i]))) return false;
            val = val * 10 + (raw[i] - '0');
        }
        outInfo.imei = val;
        return true;
    }

    if (type == DeviceType::LAPTOP) {
        if (len < 1 || len > 11) return false;
        for (int i = 0; i < len; ++i) {
            unsigned char ch = static_cast<unsigned char>(raw[i]);
            bool isUpperLatin = (ch >= 'A' && ch <= 'Z');
            if (!isUpperLatin && !isdigit(ch)) {
                return false;
            }
        }
        strcpy(outInfo.serial, raw);
        return true;
    }

    if (type == DeviceType::TV) {
        int inches = 0;
        if (!parseIntStrict(raw, inches)) return false;
        if (inches < 19 || inches > 100) return false;
        outInfo.inches = inches;
        return true;
    }

    return false;
}

bool isValidProblem(const char* s) {
    if (s == nullptr) return false;
    size_t len = strlen(s);
    return len >= 1 && len <= 80;
}

bool parseRpnMoneyToken(const char* tok, Money& outMoney) {
    if (tok == nullptr || tok[0] == '\0') return false;

    const char* dot = strchr(tok, '.');
    int intLen = 0;
    int fracLen = 0;

    if (dot == nullptr) {
        intLen = static_cast<int>(strlen(tok));
        if (intLen < 1 || intLen > 6) return false;
        for (int i = 0; i < intLen; ++i) {
            if (!isdigit(static_cast<unsigned char>(tok[i]))) return false;
        }
    } else {
        intLen = static_cast<int>(dot - tok);
        fracLen = static_cast<int>(strlen(dot + 1));
        if (intLen < 1 || intLen > 6) return false;
        if (fracLen < 1 || fracLen > 2) return false;

        for (int i = 0; i < intLen; ++i) {
            if (!isdigit(static_cast<unsigned char>(tok[i]))) return false;
        }
        for (int i = 0; i < fracLen; ++i) {
            if (!isdigit(static_cast<unsigned char>(dot[1 + i]))) return false;
        }
    }

    long long hrnPart = 0;
    for (int i = 0; i < intLen; ++i) {
        hrnPart = hrnPart * 10 + (tok[i] - '0');
    }

    long long kopPart = 0;
    if (fracLen == 1) {
        kopPart = (dot[1] - '0') * 10;
    } else if (fracLen == 2) {
        kopPart = (dot[1] - '0') * 10 + (dot[2] - '0');
    }

    long long totalKop = hrnPart * 100 + kopPart;
    const long long MAX_KOP = 10000000LL; 
    if (totalKop < 0 || totalKop > MAX_KOP) return false;

    outMoney = normalizeMoney(totalKop);
    return true;
}

bool parseRpnFactorInt(const char* tok, int& outFactor) {
    if (tok == nullptr || tok[0] == '\0') return false;
    int len = static_cast<int>(strlen(tok));
    if (len < 1 || len > 3) return false;
    for (int i = 0; i < len; ++i) {
        if (!isdigit(static_cast<unsigned char>(tok[i]))) return false;
    }
    int val = 0;
    for (int i = 0; i < len; ++i) {
        val = val * 10 + (tok[i] - '0');
    }
    if (val < 1 || val > 100) return false;
    outFactor = val;
    return true;
}

// ==========================================
//                 RPN СТЕК
// ==========================================

void rpnPush(RpnNode*& top, Money val) {
    RpnNode* node = new RpnNode{val, top};
    top = node;
}

bool rpnPop(RpnNode*& top, Money& outVal) {
    if (top == nullptr) return false;
    RpnNode* oldTop = top;
    outVal = oldTop->val;
    top = oldTop->next;
    delete oldTop;
    return true;
}

void rpnClear(RpnNode*& top) {
    Money dummy{0, 0};
    while (rpnPop(top, dummy)) {
    }
}

bool evalRPN(const char* expr, Money& res) {
    if (expr == nullptr || expr[0] == '\0') return false;

    const long long MAX_KOP = 10000000LL;
    RpnNode* stack = nullptr;

    char buf[256];
    if (strlen(expr) >= sizeof(buf)) return false;
    strcpy(buf, expr);

    bool sawAnyToken = false;
    char* savePtr = nullptr;
    char* tok = strtok_r(buf, " ", &savePtr);

    while (tok != nullptr) {
        sawAnyToken = true;

        if (strcmp(tok, "+") == 0) {
            Money b{0, 0}, a{0, 0};
            if (!rpnPop(stack, b) || !rpnPop(stack, a)) {
                rpnClear(stack);
                return false;
            }
            long long sumKop = toKop(a) + toKop(b);
            if (sumKop < 0 || sumKop > MAX_KOP) {
                rpnClear(stack);
                return false;
            }
            rpnPush(stack, normalizeMoney(sumKop));
        } else if (strcmp(tok, "-") == 0) {
            Money b{0, 0}, a{0, 0};
            if (!rpnPop(stack, b) || !rpnPop(stack, a)) {
                rpnClear(stack);
                return false;
            }
            long long diffKop = toKop(a) - toKop(b);
            if (diffKop < 0 || diffKop > MAX_KOP) {
                rpnClear(stack);
                return false;
            }
            rpnPush(stack, normalizeMoney(diffKop));
        } else if (strcmp(tok, "*") == 0) {
            Money factorMoney{0, 0}, a{0, 0};
            if (!rpnPop(stack, factorMoney) || !rpnPop(stack, a)) {
                rpnClear(stack);
                return false;
            }
            if (factorMoney.kop != 0) {
                rpnClear(stack);
                return false;
            }
            char factorStr[16];
            snprintf(factorStr, sizeof(factorStr), "%d", factorMoney.hrn);
            int factor = 0;
            if (!parseRpnFactorInt(factorStr, factor)) {
                rpnClear(stack);
                return false;
            }
            long long prodKop = toKop(a) * static_cast<long long>(factor);
            if (prodKop < 0 || prodKop > MAX_KOP) {
                rpnClear(stack);
                return false;
            }
            rpnPush(stack, normalizeMoney(prodKop));
        } else {
            Money num{0, 0};
            if (!parseRpnMoneyToken(tok, num)) {
                rpnClear(stack);
                return false;
            }
            rpnPush(stack, num);
        }

        tok = strtok_r(nullptr, " ", &savePtr);
    }

    if (!sawAnyToken || stack == nullptr || stack->next != nullptr) {
        rpnClear(stack);
        return false;
    }

    Money finalVal{0, 0};
    rpnPop(stack, finalVal);
    if (toKop(finalVal) <= 0) {
        rpnClear(stack);
        return false;
    }

    res = finalVal;
    return true;
}

// ==========================================
//            ДВОЗВ'ЯЗНИЙ СПИСОК
// ==========================================

void initOrderList(OrderList& list) {
    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
}

void appendOrder(OrderList& list, const Order& order) {
    OrderNode* newNode = new OrderNode{order, nullptr, nullptr};
    if (list.head == nullptr || list.tail == nullptr) {
        list.head = newNode;
        list.tail = newNode;
        list.size = 1;
        return;
    }
    newNode->prev = list.tail;
    list.tail->next = newNode;
    list.tail = newNode;
    list.size++;
}

OrderNode* findById(const OrderList& list, int id) {
    OrderNode* current = list.head;
    while (current != nullptr) {
        if (current->order.id == id) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

bool removeOrderNode(OrderList& list, OrderNode* target) {
    if (list.size == 0 || list.head == nullptr || target == nullptr) {
        return false;
    }

    if (list.size == 1) {
        if (list.head != target) {
            return false;
        }
        delete list.head;
        list.head = nullptr;
        list.tail = nullptr;
        list.size = 0;
        return true;
    }

    if (list.head == target) {
        list.head = target->next;
        if (list.head != nullptr) {
            list.head->prev = nullptr;
        }
        delete target;
        list.size--;
        return true;
    }

    if (list.tail == target) {
        list.tail = target->prev;
        if (list.tail != nullptr) {
            list.tail->next = nullptr;
        }
        delete target;
        list.size--;
        return true;
    }

    target->prev->next = target->next;
    target->next->prev = target->prev;
    delete target;
    list.size--;
    return true;
}

void reverseOrderList(OrderList& list) {
    if (list.size <= 1 || list.head == nullptr) {
        return;
    }

    OrderNode* current = list.head;
    while (current != nullptr) {
        OrderNode* temp = current->next;
        current->next = current->prev;
        current->prev = temp;
        current = temp;
    }

    OrderNode* tempHead = list.head;
    list.head = list.tail;
    list.tail = tempHead;
}

void clearOrderList(OrderList& list) {
    OrderNode* current = list.head;
    while (current != nullptr) {
        OrderNode* next = current->next;
        delete current;
        current = next;
    }
    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
}

ostream& operator<<(ostream& os, const Order& o) {
    char priceBuf[32];
    int absHrn = o.price.hrn >= 0 ? o.price.hrn : -o.price.hrn;
    int absKop = o.price.kop >= 0 ? o.price.kop : -o.price.kop;
    if (o.price.hrn < 0 || o.price.kop < 0) {
        snprintf(priceBuf, sizeof(priceBuf), "-%d.%02d", absHrn, absKop);
    } else {
        snprintf(priceBuf, sizeof(priceBuf), "%d.%02d", absHrn, absKop);
    }

    char detailsBuf[48];
    if (o.type == DeviceType::PHONE) {
        snprintf(detailsBuf, sizeof(detailsBuf), "IMEI %06d", o.info.imei);
    } else if (o.type == DeviceType::LAPTOP) {
        snprintf(detailsBuf, sizeof(detailsBuf), "SN %s", o.info.serial);
    } else {
        snprintf(detailsBuf, sizeof(detailsBuf), "%d inch", o.info.inches);
    }

    os << "|" << setw(4) << o.id << " | "
       << setw(15) << o.client.name << " | "
       << setw(10) << o.client.phone << " | "
       << setw(2) << setfill('0') << o.date.day << '.'
       << setw(2) << setfill('0') << o.date.month << '.'
       << setw(4) << setfill('0') << o.date.year << setfill(' ') << " | "
       << setw(6) << deviceTypeToStr(o.type) << " | "
       << setw(14) << detailsBuf << " | "
       << setw(2) << o.priority << " | "
       << setw(7) << statusToStr(o.status) << " | "
       << setw(9) << priceBuf << " | ";
    return os;
}

// ==========================================
//            ПРІОРИТЕТНА ЧЕРГА
// ==========================================

void initQueue(PriorityQueue& q) {
    q.head = nullptr;
    q.size = 0;
}

void enqueueOrder(PriorityQueue& q, Order* orderPtr) {
    if (orderPtr == nullptr) return;
    QNode* newNode = new QNode{orderPtr, nullptr};

    if (q.head == nullptr || q.head->order->priority < orderPtr->priority) {
        newNode->next = q.head;
        q.head = newNode;
        q.size++;
        return;
    }

    QNode* current = q.head;
    while (current->next != nullptr && current->next->order->priority >= orderPtr->priority) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
    q.size++;
}

Order* dequeueOrder(PriorityQueue& q) {
    if (q.size == 0 || q.head == nullptr) return nullptr;
    QNode* head = q.head;
    Order* mainOrder = head->order;
    q.head = head->next;
    delete head;
    q.size--;
    return mainOrder;
}

bool removeFromQueue(PriorityQueue& q, const Order* targetPtr) {
    if (q.head == nullptr || targetPtr == nullptr) return false;

    QNode* current = q.head;
    if (current->order == targetPtr) {
        q.head = current->next;
        delete current;
        q.size--;
        return true;
    }

    while (current->next != nullptr) {
        if (current->next->order == targetPtr) {
            QNode* temp = current->next;
            current->next = current->next->next;
            delete temp;
            q.size--;
            return true;
        }
        current = current->next;
    }
    return false;
}

void clearQueue(PriorityQueue& q) {
    QNode* current = q.head;
    while (current != nullptr) {
        QNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    q.head = nullptr;
    q.size = 0;
}

// ==========================================
//             КІЛЬЦЕВИЙ СПИСОК
// ==========================================

Master* createMasterNode(const char* name) {
    Master* node = new Master{"", 0, Money{0, 0}, nullptr};
    strncpy(node->name, name, sizeof(node->name) - 1);
    node->name[sizeof(node->name) - 1] = '\0';
    return node;
}

bool initMastersRing(Master*& current, int n, char names[][24]) {
    if (n < 1 || n > 5 || names == nullptr) {
        current = nullptr;
        return false;
    }
    Master* head = createMasterNode(names[0]);
    Master* last = head;
    for (int i = 1; i < n; ++i) {
        last->next = createMasterNode(names[i]);
        last = last->next;
    }
    last->next = head;
    current = head;
    return true;
}

void printMastersRing(const Master* current) {
    if (current == nullptr) return;
    const Master* p = current;
    do {
        cout << p->name << " | Ремонтів: " << p->completedCount
             << " | Виручка: " << p->revenue << "\n";
        p = p->next;
    } while (p != current);
}

void clearMastersRing(Master*& current) {
    if (current == nullptr) return;
    Master* head = current;
    Master* p = head->next;
    head->next = nullptr;

    while (p != nullptr) {
        Master* nextNode = p->next;
        delete p;
        p = nextNode;
    }
    current = nullptr;
}

// ==========================================
//               СТЕК ДІЙ
// ==========================================

void initActionStack(ActionStack& s) {
    s.top = nullptr;
}

void pushAction(ActionStack& s, ActionType type, const Order& orderCopy) {
    Action* newAction = new Action{type, orderCopy, s.top};
    s.top = newAction;
}

bool popAction(ActionStack& s, Action& outAction) {
    if (s.top == nullptr) return false;
    Action* temp = s.top;
    outAction.type = temp->type;
    outAction.orderCopy = temp->orderCopy;
    outAction.next = nullptr;
    s.top = temp->next;
    delete temp;
    return true;
}

void clearActionStack(ActionStack& s) {
    Action dummy{};
    while (popAction(s, dummy)) {
    }
}

// ==========================================
//                   ЗВІТ
// ==========================================

Money revenue(const OrderNode* p) {
    if (p == nullptr) {
        return Money{0, 0};
    }
    Money currentVal = (p->order.status == Status::DONE) ? p->order.price : Money{0, 0};
    return currentVal + revenue(p->next);
}

void printReport(const OrderList& list, const Master* currentMaster) {
    if (list.size == 0 || list.head == nullptr) {
        cout << "Журнал замовлень порожній.\n";
        printMastersRing(currentMaster);
        return;
    }

    Order** array = new Order*[list.size];
    OrderNode* current = list.head;
    for (int i = 0; i < list.size; ++i) {
        array[i] = &current->order;
        current = current->next;
    }

    for (int i = 0; i < list.size; ++i) {
        bool swapped = false;
        for (int j = 0; j < list.size - i - 1; ++j) {
            bool needSwap = false;
            if (array[j]->price < array[j + 1]->price) {
                needSwap = true;
            } else if (!(array[j + 1]->price < array[j]->price)) {
                if (array[j]->id > array[j + 1]->id) {
                    needSwap = true;
                }
            }
            if (needSwap) {
                Order* temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }

    for (int i = 0; i < list.size; ++i) {
        cout << *array[i] << "\n";
    }

    Money maxPrice = array[0]->price;
    Money minPrice = array[list.size - 1]->price;
    cout << "Різниця між найдорожчим і найдешевшим: " << (maxPrice - minPrice) << "\n";
    cout << "Виручка за завершеними ремонтами: " << revenue(list.head) << "\n";
    printMastersRing(currentMaster);

    delete[] array;
}

// ==========================================
//               ФУНКЦІЇ МЕНЮ
// ==========================================

void menuAddOrder(OrderList& list, PriorityQueue& q, ActionStack& actions, int& nextId) {
    char buf[256];
    Order newOrder{};

    cout << "Ім'я клієнта: ";
    if (!cin.getline(buf, sizeof(buf)) || !isValidLatinWord(buf, 15)) {
        cout << "Помилка вводу даних замовлення\n";
        return;
    }
    strcpy(newOrder.client.name, buf);

    cout << "Телефон (10 цифр): ";
    if (!cin.getline(buf, sizeof(buf)) || !isValidPhone(buf)) {
        cout << "Помилка вводу даних замовлення\n";
        return;
    }
    strcpy(newOrder.client.phone, buf);

    cout << "Дата прийому (ДД.ММ.РРРР): ";
    if (!cin.getline(buf, sizeof(buf)) || !parseAndValidateDate(buf, newOrder.date)) {
        cout << "Помилка вводу даних замовлення\n";
        return;
    }

    cout << "Тип пристрою (1 телефон, 2 ноутбук, 3 телевізор): ";
    int typeNum = 0;
    if (!cin.getline(buf, sizeof(buf)) || !parseIntStrict(buf, typeNum) || (typeNum < 1 || typeNum > 3)) {
        cout << "Помилка вводу даних замовлення\n";
        return;
    }
    newOrder.type = static_cast<DeviceType>(typeNum);

    if (newOrder.type == DeviceType::PHONE) {
        cout << "Останні 6 цифр IMEI: ";
    } else if (newOrder.type == DeviceType::LAPTOP) {
        cout << "Серійний номер: ";
    } else {
        cout << "Діагональ (дюймів): ";
    }

    if (!cin.getline(buf, sizeof(buf)) || !parseAndValidateDeviceInfo(newOrder.type, buf, newOrder.info)) {
        cout << "Помилка вводу даних замовлення\n";
        return;
    }

    cout << "Опис несправності: ";
    if (!cin.getline(buf, sizeof(buf)) || !isValidProblem(buf)) {
        cout << "Помилка вводу даних замовлення\n";
        return;
    }
    strcpy(newOrder.problem, buf);

    cout << "Пріоритет (1 звичайний, 2 підвищений, 3 терміновий): ";
    int prio = 0;
    if (!cin.getline(buf, sizeof(buf)) || !parseIntStrict(buf, prio) || (prio < 1 || prio > 3)) {
        cout << "Помилка вводу даних замовлення\n";
        return;
    }
    newOrder.priority = prio;

    cout << "Вартість (обернений польський запис): ";
    if (!cin.getline(buf, sizeof(buf)) || !evalRPN(buf, newOrder.price)) {
        cout << "Помилка вводу даних замовлення\n";
        return;
    }

    newOrder.id = nextId++;
    newOrder.status = Status::WAITING;
    newOrder.masterName[0] = '\0';

    appendOrder(list, newOrder);
    Order* storedPtr = &list.tail->order;
    enqueueOrder(q, storedPtr);
    pushAction(actions, ActionType::ADD, *storedPtr);

    cout << "Замовлення №" << storedPtr->id
         << " додано: вартість " << storedPtr->price
         << ", у черзі на ремонт: " << q.size << ".\n";
}

void menuShowJournal(const OrderList& list, const PriorityQueue& q) {
    if (list.size == 0 || list.head == nullptr) {
        cout << "Журнал замовлень порожній.\n";
    } else {
        cout << "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+\n";
        cout << "| №   |          Клієнт | Телефон    | Дата       | Тип    |         Деталі | Пр |  Статус |  Вартість |\n";
        cout << "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+\n";
        OrderNode* cur = list.head;
        while (cur != nullptr) {
            cout << cur->order << "\n";
            cur = cur->next;
        }
        cout << "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+\n";
    }
    cout << "Замовлень у журналі: " << list.size
         << ", у черзі: " << q.size << ".\n";
}

void menuAssignToMaster(PriorityQueue& q, Master*& currentMaster) {
    if (q.size == 0 || q.head == nullptr) {
        cout << "Черга порожня.\n";
        return;
    }
    if (currentMaster == nullptr) {
        cout << "Немає доступних майстрів.\n";
        return;
    }

    Order* orderPtr = dequeueOrder(q);
    if (orderPtr == nullptr) {
        cout << "Черга порожня.\n";
        return;
    }

    orderPtr->status = Status::REPAIR;
    strcpy(orderPtr->masterName, currentMaster->name);

    cout << "Замовлення №" << orderPtr->id
         << " (пріоритет " << orderPtr->priority << ") видано майстру "
         << currentMaster->name << ". Опис: " << orderPtr->problem
         << ". Залишилось у черзі: " << q.size << ".\n";

    currentMaster = currentMaster->next;
}

Master* findMasterByName(Master* anyNode, const char* name) {
    if (anyNode == nullptr || name == nullptr || name[0] == '\0') return nullptr;
    Master* p = anyNode;
    do {
        if (strcmp(p->name, name) == 0) {
            return p;
        }
        p = p->next;
    } while (p != anyNode);
    return nullptr;
}

void menuCompleteRepair(OrderList& list, Master* ringAnyNode) {
    char buf[64];
    cout << "Номер замовлення: ";
    if (!cin.getline(buf, sizeof(buf))) return;

    int id = 0;
    if (!parseIntStrict(buf, id)) {
        cout << "Некоректний номер замовлення.\n";
        return;
    }

    OrderNode* node = findById(list, id);
    if (node == nullptr) {
        cout << "Замовлення не знайдено.\n";
        return;
    }

    if (node->order.status == Status::WAITING) {
        cout << "Замовлення ще не передано майстру.\n";
        return;
    }
    if (node->order.status == Status::DONE) {
        cout << "Ремонт замовлення вже завершено.\n";
        return;
    }

    node->order.status = Status::DONE;
    Master* m = findMasterByName(ringAnyNode, node->order.masterName);
    if (m != nullptr) {
        m->completedCount += 1;
        m->revenue = m->revenue + node->order.price;
    }

    cout << "Ремонт замовлення №" << node->order.id
         << " завершено. Вартість: " << node->order.price << ".\n";
}

void menuDeleteOrder(OrderList& list, PriorityQueue& q, ActionStack& actions) {
    char buf[64];
    cout << "Номер замовлення: ";
    if (!cin.getline(buf, sizeof(buf))) return;

    int id = 0;
    if (!parseIntStrict(buf, id)) {
        cout << "Некоректний номер замовлення.\n";
        return;
    }

    OrderNode* node = findById(list, id);
    if (node == nullptr) {
        cout << "Замовлення не знайдено.\n";
        return;
    }

    if (node->order.status != Status::WAITING) {
        cout << "Видалити можна лише замовлення зі статусом WAITING.\n";
        return;
    }

    Order copy = node->order;
    removeFromQueue(q, &node->order);
    removeOrderNode(list, node);
    pushAction(actions, ActionType::REMOVE, copy);

    cout << "Замовлення №" << copy.id << " видалено.\n";
}

void menuUndoAction(OrderList& list, PriorityQueue& q, ActionStack& actions) {
    Action act{};
    if (!popAction(actions, act)) {
        cout << "Немає дій для скасування.\n";
        return;
    }

    if (act.type == ActionType::ADD) {
        OrderNode* node = findById(list, act.orderCopy.id);
        if (node != nullptr && node->order.status == Status::WAITING) {
            removeFromQueue(q, &node->order);
            removeOrderNode(list, node);
            cout << "Скасовано додавання замовлення №" << act.orderCopy.id << ".\n";
        } else {
            cout << "Неможливо вилучити замовлення №" << act.orderCopy.id
                 << " (воно вже не в статусі WAITING або відсутнє). Дію знято зі стеку.\n";
        }
    } else if (act.type == ActionType::REMOVE) {
        Order restored = act.orderCopy;
        restored.status = Status::WAITING;
        restored.masterName[0] = '\0';
        appendOrder(list, restored);
        enqueueOrder(q, &list.tail->order);
        cout << "Відновлено видалене замовлення №" << restored.id << ".\n";
    }
}

void menuReverseJournal(OrderList& list) {
    reverseOrderList(list);
    if (list.head == nullptr || list.tail == nullptr) {
        cout << "Журнал порожній.\n";
        return;
    }
    cout << "Журнал розвернуто. Перше замовлення №" << list.head->order.id
         << ", останнє замовлення №" << list.tail->order.id << ".\n";
}

void printMenu() {
    cout << "1. Додати замовлення\n"
         << "2. Журнал замовлень\n"
         << "3. Видати замовлення майстру\n"
         << "4. Завершити ремонт\n"
         << "5. Видалити замовлення\n"
         << "6. Скасувати останню дію\n"
         << "7. Звіт\n"
         << "8. Розвернути журнал\n"
         << "0. Вийти\n";
}

// ==========================================
//                    MAIN
// ==========================================

int main() {
    cout << "Кількість майстрів (від 1 до 5): ";
    char countLine[128];
    if (!cin.getline(countLine, sizeof(countLine))) {
        cout << "Некоректна кількість майстрів\n";
        return 0;
    }

    int n = 0;
    if (!parseIntStrict(countLine, n) || n < 1 || n > 5) {
        cout << "Некоректна кількість майстрів\n";
        return 0;
    }

    cout << "Імена майстрів через пробіл: ";
    char namesLine[256];
    if (!cin.getline(namesLine, sizeof(namesLine))) {
        cout << "Некоректні імена майстрів\n";
        return 0;
    }

    char names[5][24];
    int nameCount = 0;
    char* savePtr = nullptr;
    char* tok = strtok_r(namesLine, " ", &savePtr);
    while (tok != nullptr) {
        if (nameCount >= n || !isValidLatinWord(tok, 23)) {
            cout << "Некоректні імена майстрів\n";
            return 0;
        }
        for (int i = 0; i < nameCount; ++i) {
            if (strcmp(names[i], tok) == 0) {
                cout << "Некоректні імена майстрів\n";
                return 0;
            }
        }
        strcpy(names[nameCount], tok);
        nameCount++;
        tok = strtok_r(nullptr, " ", &savePtr);
    }

    if (nameCount != n) {
        cout << "Некоректні імена майстрів\n";
        return 0;
    }

    OrderList journal;
    PriorityQueue queue;
    ActionStack actions;
    Master* currentMaster = nullptr;
    int nextId = 101;

    initOrderList(journal);
    initQueue(queue);
    initActionStack(actions);

    if (!initMastersRing(currentMaster, n, names)) {
        cout << "Некоректні дані майстрів\n";
        return 0;
    }

    char line[256];
    while (true) {
        printMenu();
        if (!cin.getline(line, sizeof(line))) {
            break;
        }

        int choice = -1;
        if (!parseIntStrict(line, choice)) {
            cout << "Некоректний пункт меню\n";
            continue;
        }

        if (choice == 0) {
            break;
        }

        switch (choice) {
            case 1:
                menuAddOrder(journal, queue, actions, nextId);
                break;
            case 2:
                menuShowJournal(journal, queue);
                break;
            case 3:
                menuAssignToMaster(queue, currentMaster);
                break;
            case 4:
                menuCompleteRepair(journal, currentMaster);
                break;
            case 5:
                menuDeleteOrder(journal, queue, actions);
                break;
            case 6:
                menuUndoAction(journal, queue, actions);
                break;
            case 7:
                printReport(journal, currentMaster);
                break;
            case 8:
                menuReverseJournal(journal);
                break;
            default:
                cout << "Некоректний пункт меню\n";
                break;
        }
    }

    clearQueue(queue);
    clearOrderList(journal);
    clearActionStack(actions);
    clearMastersRing(currentMaster);

    return 0;
}