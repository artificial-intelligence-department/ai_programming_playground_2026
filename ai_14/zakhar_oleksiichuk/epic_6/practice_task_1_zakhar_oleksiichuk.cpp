#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cctype>

using namespace std;

const long long MAX_KOP = 10000000LL;

// TYPES ================================
enum class DeviceType {
    PHONE = 1,
    LAPTOP,
    TV
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

struct Money {
    int hrn;
    int kop;

    long long toKop() const {
        return (long long)hrn * 100LL + (long long)kop;
    }

    static Money fromKop(long long total) {
        if (total <= 0) {
            return Money{0, 0};
        }
        return Money{
            (int)(total / 100LL),
            (int)(total % 100LL)
        };
    }

    Money operator+(const Money &other) const {
        return fromKop(toKop() + other.toKop());
    }

    Money operator-(const Money &other) const {
        return fromKop(toKop() - other.toKop());
    }

    Money operator*(int multiplier) const {
        return fromKop(toKop() * (long long)multiplier);
    }

    bool operator<(const Money &other) const {
        return toKop() < other.toKop();
    }

    bool operator==(const Money& other) const {
        return toKop() == other.toKop();
    }
};

ostream &operator<<(ostream &os, const Money &m) {
    os << m.hrn << '.' << setfill('0') << setw(2) << m.kop;
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

// STACK ================================
struct NumNode {
    long long kop;
    NumNode* next;
};

void pushNum(NumNode*& top, long long kop) {
    NumNode* newNode = new NumNode {kop, nullptr};
    newNode->next = top;
    top = newNode;
}

void popNum(NumNode*& top) {
    if (top == nullptr) return;
    NumNode* temp = top;
    top = top->next;
    delete temp;
}

long long getTop(NumNode*& top) {
    if (top == nullptr) return 0;
    return top->kop;
}

void clearNumStack(NumNode *&top) {
    NumNode* curr = top;
    while (curr != nullptr) {
        curr = curr->next;
        popNum(top);
    }
}

// PARSING ================================

bool parsePriceToken(const char* tok, long long& outKop) {
    if (tok == nullptr || tok[0] == '\0') return false;

    int i = 0;
    int intDigits = 0;
    long long hrnPart = 0;

    while (tok[i] != '\0' && tok[i] != '.') {
        if (!isdigit(tok[i])) return false;
        intDigits++;
        if (intDigits > 6) return false;
        hrnPart = hrnPart * 10LL + (tok[i] - '0');
        i++;
    }

    if (intDigits == 0) return false;

    long long kopPart = 0;
    int fracDigits = 0;

    if (tok[i] == '.') {
        i++;
        if (tok[i] == '\0') return false; 
        while (tok[i] != '\0') {
            if (!isdigit(tok[i])) return false;
            fracDigits++;
            if (fracDigits > 2) return false;
            kopPart = kopPart * 10LL + (tok[i] - '0');
            i++;
        }
        if (fracDigits == 1) kopPart *= 10LL;
    }

    long long total = hrnPart * 100LL + kopPart;
    if (total > MAX_KOP) return false;

    outKop = total;
    return true;
}

bool parseMultiplier(const char* tok, int& mult) {
    if (tok == nullptr || tok[0] == '\0') return false;

    for (int i = 0; tok[i] != '\0'; i++) {
        if (!isdigit(tok[i])) return false;
    }

    long long val = 0;
    for (int i = 0; tok[i] != '\0'; i++) {
        val = val * 10LL + (tok[i] - '0');
        if (val > 100) return false;
    }

    if (val < 1 || val > 100) return false;
    mult = (int)val;
    return true;
}

bool parseId(const char* s, int& outId) {
    if (s == nullptr || s[0] == '\0') return false;
    
    long long val = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (!isdigit(s[i])) return false;
        val = val * 10LL + (s[i] - '0'); 
        if (val > 2000000000LL) return false;
    }
    outId = (int)val;
    return true;
}

// RPN ================================

bool evalRPN(const char* expr, Money& res) {
    if (expr == nullptr) {
        cout << "Помилка у виразі: порожній вираз.\n";
        return false;
    }

    NumNode* stackTop = nullptr;
    int len = strlen(expr);
    int pos = 0;
    bool hasToken = false;
    char tok[128];

    while (pos < len) {
        while (pos < len && expr[pos] == ' ') pos++;
        if (pos >= len) break;

        int tLen = 0;
        while (pos < len && expr[pos] != ' ') {
            if (tLen < 127) tok[tLen++] = expr[pos];
            pos++;
        }
        tok[tLen] = '\0';
        hasToken = true;

        if (strcmp(tok, "+") == 0 || strcmp(tok, "-") == 0 || strcmp(tok, "*") == 0) {
            if (stackTop == nullptr || stackTop->next == nullptr) {
                cout << "Помилка у виразі: для операції «" << tok << "» бракує чисел.\n";
                clearNumStack(stackTop);
                return false;
            }

            long long rhs = getTop(stackTop);
            popNum(stackTop);
            long long lhs = getTop(stackTop);
            popNum(stackTop);

            long long resultKop = 0;

            if (strcmp(tok, "+") == 0) {
                if (lhs > MAX_KOP - rhs) {
                    cout << "Помилка у виразі: сума перевищує 100000.00 грн.\n";
                    clearNumStack(stackTop);
                    return false;
                }
                resultKop = lhs + rhs;
            } else if (strcmp(tok, "-") == 0) {
                resultKop = lhs - rhs;
                if (resultKop < 0) {
                    cout << "Помилка у виразі: проміжний результат від'ємний.\n";
                    clearNumStack(stackTop);
                    return false;
                }
            } else { 
                if (rhs < 100LL || rhs > 10000LL || (rhs % 100LL) != 0) {
                    cout << "Помилка у виразі: множник має бути цілим числом від 1 до 100.\n";
                    clearNumStack(stackTop);
                    return false;
                }
                long long mult = rhs / 100LL;
                if (mult > 0 && lhs > MAX_KOP / mult) {
                    cout << "Помилка у виразі: сума перевищує 100000.00 грн.\n";
                    clearNumStack(stackTop);
                    return false;
                }
                resultKop = lhs * mult;
            }

            pushNum(stackTop, resultKop);
        } else {
            long long valKop = 0;
            if (!parsePriceToken(tok, valKop)) {
                cout << "Помилка у виразі: «" << tok << "» не є числом або операцією.\n";
                clearNumStack(stackTop);
                return false;
            }
            pushNum(stackTop, valKop);
        }
    }

    if (!hasToken) {
        cout << "Помилка у виразі: порожній вираз.\n";
        clearNumStack(stackTop);
        return false;
    }

    if (stackTop == nullptr || stackTop->next != nullptr) {
        int cnt = 0;
        for (NumNode* p = stackTop; p != nullptr; p = p->next) cnt++;
        cout << "Помилка у виразі: у стеку залишилось чисел: " << cnt << ", а має бути одне.\n";
        clearNumStack(stackTop);
        return false;
    }

    long long finalKop = getTop(stackTop);
    clearNumStack(stackTop);

    if (finalKop <= 0) {
        cout << "Помилка у виразі: кінцевий результат має бути більшим за 0.00 грн.\n";
        return false;
    }

    res = Money::fromKop(finalKop);
    return true;
}

//VALIDATION ================================

bool isValidName(const char* s) {
    int len = strlen(s);
    if (len < 1 || len > 15) return false;
    for (int i = 0; i < len; i++) {
        if (!isalpha(s[i])) return false;
    }
    return true;
}

bool isValidPhone(const char* s) {
    if (strlen(s) != 10) return false;
    if (s[0] != '0') return false;
    for (int i = 0; i < 10; i++) {
        if (!isdigit(s[i])) return false;
    }
    return true;
}

bool isLeapYear(int y) {
    return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
}

bool parseAndValidateDate(const char* s, Date& d) {
    if (strlen(s) != 10) return false;
    if (s[2] != '.' || s[5] != '.') return false;

    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit(s[i])) return false;
    }

    int day = (s[0] - '0') * 10 + (s[1] - '0');
    int month = (s[3] - '0') * 10 + (s[4] - '0');
    int year = (s[6] - '0') * 1000 + (s[7] - '0') * 100 + (s[8] - '0') * 10 + (s[9] - '0');

    if (year < 2000 || year > 2099) return false;
    if (month < 1 || month > 12) return false;

    int daysInMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year)) daysInMonth[2] = 29;

    if (day < 1 || day > daysInMonth[month]) return false;

    d.day = day;
    d.month = month;
    d.year = year;
    return true;
}

// UNION GET ================================

bool readDeviceInfo(DeviceType type, DeviceInfo& info) {
    char buf[128];

    if (type == DeviceType::PHONE) {
        cout << "Останні 6 цифр IMEI: ";
        if (!cin.getline(buf, sizeof(buf))) return false;
        if (strlen(buf) != 6) {
            cout << "Помилка: потрібно рівно 6 цифр.\n";
            return false;
        }
        for (int i = 0; i < 6; i++) {
            if (!isdigit(buf[i])) {
                cout << "Помилка: потрібно рівно 6 цифр.\n";
                return false;
            }
        }
        info.imei = atoi(buf);
        return true;
    }

    if (type == DeviceType::LAPTOP) {
        cout << "Серійний номер: ";
        if (!cin.getline(buf, sizeof(buf))) return false;
        int len = strlen(buf);
        if (len < 1 || len > 11) {
            cout << "Помилка: серійний номер має бути від 1 до 11 символів (A-Z, 0-9).\n";
            return false;
        }
        for (int i = 0; i < len; i++) {
            char c = buf[i];
            if (!((c >= 'A' && c <= 'Z') || isdigit(c))) {
                cout << "Помилка: серійний номер має бути від 1 до 11 символів (A-Z, 0-9).\n";
                return false;
            }
        }
        strcpy(info.serial, buf);
        return true;
    }

    if (type == DeviceType::TV) {
        cout << "Діагональ (19-100): ";
        if (!cin.getline(buf, sizeof(buf))) return false;
        if (strlen(buf) == 0) {
            cout << "Помилка: діагональ має бути від 19 до 100 дюймів.\n";
            return false;
        }
        for (int i = 0; buf[i] != '\0'; i++) {
            if (!isdigit(buf[i])) {
                cout << "Помилка: діагональ має бути від 19 до 100 дюймів.\n";
                return false;
            }
        }
        int inches = atoi(buf);
        if (inches < 19 || inches > 100) {
            cout << "Помилка: діагональ має бути від 19 до 100 дюймів.\n";
            return false;
        }
        info.inches = inches;
        return true;
    }

    return false;
}

// ORDERS ================================

void appendOrderToList(OrderList& list, const Order& ord) {
    OrderNode* node = new OrderNode{ord, nullptr, nullptr};

    if (list.head == nullptr) {
        list.head = list.tail = node;
    }
    else {
        node->prev = list.tail;
        list.tail->next = node;
        list.tail = node;
    }
    list.size++;
}

void enqueuePriority(QNode*& pqHead, Order* target) {
    QNode* node = new QNode{target, nullptr};

    if (pqHead == nullptr || target->priority > pqHead->order->priority) {
        node->next = pqHead;
        pqHead = node;
        return;
    }

    QNode* curr = pqHead;
    while(curr->next != nullptr && curr->next->order->priority >= target->priority) curr = curr->next;

    node->next = curr->next;
    curr->next = node;
}

void pushAction(Action*& actTop, ActionType type, const Order& ord) {
    Action* act = new Action{type, ord, actTop};
    actTop = act;
}

int countQueue(const QNode* pqHead) {
    int count = 0;
    const QNode* curr = pqHead;
    while(curr != nullptr) {
        count++;
        curr = curr->next;
    }
    return count;
}

void addOrder(OrderList& list, QNode*& pqHead, Action*& actTop, int& nextId) {
    char buf[256];
    Order newOrder;
    memset(&newOrder, 0, sizeof(Order));

    cout << "Ім'я клієнта: ";
    if (!cin.getline(buf, sizeof(buf)) || !isValidName(buf)) {
        cout << "Помилка: ім'я має містити від 1 до 15 латинських літер.\n";
        return;
    }
    strcpy(newOrder.client.name, buf);

    cout << "Телефон (10 цифр): ";
    if (!cin.getline(buf, sizeof(buf)) || !isValidPhone(buf)) {
        cout << "Помилка: телефон має складатися з 10 цифр і починатися з 0.\n";
        return;
    }
    strcpy(newOrder.client.phone, buf);

    cout << "Дата прийому (ДД.ММ.РРРР): ";
    if (!cin.getline(buf, sizeof(buf)) || !parseAndValidateDate(buf, newOrder.date)) {
        cout << "Помилка: некоректна дата.\n";
        return;
    }

    cout << "Тип пристрою (1 телефон, 2 ноутбук, 3 телевізор): ";
    if (!cin.getline(buf, sizeof(buf)) || strlen(buf) != 1 || (buf[0] != '1' && buf[0] != '2' && buf[0] != '3')) {
        cout << "Помилка: тип пристрою має бути 1, 2 або 3.\n";
        return;
    }
    if (buf[0] == '1') newOrder.type = DeviceType::PHONE;
    else if (buf[0] == '2') newOrder.type = DeviceType::LAPTOP;
    else newOrder.type = DeviceType::TV;

    if (!readDeviceInfo(newOrder.type, newOrder.info)) {
        return;
    }

    cout << "Опис несправності: ";
    if (!cin.getline(buf, sizeof(buf))) return;
    int probLen = (int)strlen(buf);
    if (probLen < 1 || probLen > 80) {
        cout << "Помилка: опис несправності має містити від 1 до 80 байтів.\n";
        return;
    }
    strcpy(newOrder.problem, buf);

    cout << "Пріоритет (1 звичайний, 2 підвищений, 3 терміновий): ";
    if (!cin.getline(buf, sizeof(buf)) || strlen(buf) != 1 || (buf[0] != '1' && buf[0] != '2' && buf[0] != '3')) {
        cout << "Помилка: пріоритет має бути 1, 2 або 3.\n";
        return;
    }
    newOrder.priority = buf[0] - '0';

    cout << "Вартість (обернений польський запис): ";
    if (!cin.getline(buf, sizeof(buf))) return;
    Money price{0, 0};
    if (!evalRPN(buf, price)) {
        return;
    }

    newOrder.id = nextId++;
    newOrder.price = price;
    newOrder.status = Status::WAITING;
    newOrder.masterName[0] = '\0';

    appendOrderToList(list, newOrder);
    Order* storedPtr = &list.tail->order;
    enqueuePriority(pqHead, storedPtr);
    pushAction(actTop, ActionType::ADD, newOrder);

    cout << "Замовлення №" << newOrder.id
         << " додано: вартість " << newOrder.price << " грн"
         << ", у черзі на ремонт: " << countQueue(pqHead) << ".\n";
}

ostream& operator<<(ostream& os, const Order& o) {
    const char* typeStr = "";
    if (o.type == DeviceType::PHONE) typeStr = "PHONE";
    else if (o.type == DeviceType::LAPTOP) typeStr = "LAPTOP";
    else typeStr = "TV";

    const char* statusStr = "";
    if (o.status == Status::WAITING) statusStr = "WAITING";
    else if (o.status == Status::REPAIR) statusStr = "REPAIR";
    else statusStr = "DONE";

    printf("| %3d | %-15s | %-10s | %02d.%02d.%04d | %-6s | ",
           o.id,
           o.client.name,
           o.client.phone,
           o.date.day, o.date.month, o.date.year,
           typeStr);

    if (o.type == DeviceType::PHONE) {
        printf("IMEI %06d    ", o.info.imei);
    } else if (o.type == DeviceType::LAPTOP) {
        printf("SN %-11s ", o.info.serial);
    } else {
        printf("%-2d inch        ", o.info.inches);
    }

    printf("| %2d | %-7s | %6d.%02d |\n",
           o.priority,
           statusStr,
           o.price.hrn, o.price.kop);

    return os;
}

void removeFromQueue(QNode*& pqHead, const Order* targetOrder) {
    QNode* curr = pqHead;
    QNode* prev = nullptr;

    while (curr != nullptr) {
        if (curr->order == targetOrder) {
            if (prev == nullptr) {
                pqHead = curr->next;
            } else {
                prev->next = curr->next;
            }
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

OrderNode* findOrderById(const OrderList& list, int id) {
    OrderNode* curr = list.head;
    while(curr != nullptr) {
        if (curr->order.id == id) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

void unlinkOrderNode(OrderList& list, OrderNode* node) {
    if (node == nullptr) return;

    if (node->prev != nullptr) {
        node->prev->next = node->next;
    }
    else {
        list.head = node->next;
    }

    if (node->next != nullptr) {
        node->next->prev = node->prev;
    }
    else {
        list.tail = node->prev;
    }

    list.size--;
}

void deleteOrder(OrderList& list, QNode*& pqHead, Action*& actTop) {
    char buf[128];
    printf("Номер замовлення: ");
    if (!cin.getline(buf, sizeof(buf))) return;

    int id = 0;
    if (!parseId(buf, id)) {
        printf("Помилка: номер замовлення має бути цілим числом.\n");
        return;
    }

    OrderNode* node = findOrderById(list, id);
    if (!node) {
        printf("Замовлення не знайдено\n");
        return;
    }
    if (node->order.status != Status::WAITING) {
        printf("Видалити можна тільки замолення в черзі\n");
        return;
    }

    pushAction(actTop, ActionType::REMOVE, node->order);
    Order* nodeOrder = &node->order;
    removeFromQueue(pqHead, nodeOrder);
    unlinkOrderNode(list, node);
    printf("Замовлення №%d видалено. У журналі: %d, у черзі: %d.\n",
           id, list.size, countQueue(pqHead));
    delete node;
}
// MASTERS

Order* popPriority(QNode*& pqHead) {
    if (pqHead == nullptr) return nullptr;

    QNode* temp = pqHead;
    Order* ord = temp->order;
    pqHead = pqHead->next;
    delete temp;

    return ord;


}

void assignOrderToMaster(QNode*& pqHead, Master*& currentMaster) {
    if (pqHead == nullptr) {
        printf("Черга на ремонт порожня.\n");
        return;
    }

    if (currentMaster == nullptr) {
        printf("Помилка: список майстрів порожній.\n");
        return;
    }

    Order* ord = popPriority(pqHead);
    ord->status = Status::REPAIR;
    strcpy(ord->masterName, currentMaster->name);

    printf("Замовлення №%d (пріоритет %d) передано майстру %s.\n",
           ord->id, ord->priority, currentMaster->name);
    printf("Несправність: %s\n", ord->problem);
    printf("У черзі залишилось: %d\n", countQueue(pqHead));

    currentMaster = currentMaster->next;
}

void appendMaster(Master*& head, Master*& tail, const char* name) {
    Master* node = new Master;
    strcpy(node->name, name);
    node->completedCount = 0;
    node->revenue = Money{0, 0};
    node->next = nullptr;

    if (head == nullptr) {
        head = node;
        tail = node;
    } else {
        tail->next = node;
        tail = node;
    }

    tail->next = head;
}

void printJournal(const OrderList& list, const QNode* pqHead) {
    if (list.head == nullptr) {
        printf("Журнал порожній.\n");
        return;
    }

    const char* border = "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+";
    printf("%s\n", border);
    printf("|   № | Клієнт          | Телефон    | Дата       | Тип    | Деталі         | Пр | Статус  |  Вартість |\n");
    printf("%s\n", border);

    const OrderNode* curr = list.head;
    while (curr != nullptr) {
        cout << curr->order;
        curr = curr->next;
    } 

    printf("%s\n", border);
    printf("Усього замовлень: %d, у черзі на ремонт: %d\n",
           list.size, countQueue(pqHead));
}

Master* findMasterByName(Master* masterHead, const char* name) {
    if (masterHead == nullptr || name[0] == '\0') return nullptr;

    Master* curr = masterHead;
    do {
        if (strcmp(curr->name, name) == 0) return curr;
        curr = curr->next;
    } while(curr != masterHead);
    return nullptr;
}

void completeOrder(OrderList& list, Master* masterHead) {
    char buf[128];
    printf("Номер замовлення: ");
    if (!cin.getline(buf, sizeof(buf))) return;

    int id;
    if (!parseId(buf, id)) {
        printf("Помилка: номер замовлення має бути цілим числом.\n");
        return;
    }

    OrderNode* node = findOrderById(list, id);
    if (node == nullptr) {
        printf("Замовлення №%d не знайдено.\n", id);
        return;
    }

    Order& ord = node->order;
    if (ord.status == Status::WAITING) {
        printf("Замовлення №%d ще не передано майстру.\n", ord.id);
        return;
    }
    if (ord.status == Status::DONE) {
        printf("Замовлення №%d уже завершено.\n", ord.id);
        return;
    }

    ord.status = Status::DONE;

    Master* master = findMasterByName(masterHead, ord.masterName);
    if (master != nullptr) {
        master->completedCount++;
        master->revenue = master->revenue + ord.price;
        printf("Ремонт замовлення №%d завершено. Майстер %s: виконано %d, виручка %d.%02d грн.\n",
               ord.id, master->name, master->completedCount,
               master->revenue.hrn, master->revenue.kop);
    }
    else {
        printf("Ремонт замовлення №%d завершено.\n", ord.id);
    }
}

void popAction(OrderList& list, QNode*& pqHead, Action*& actTop) {
    if (actTop == nullptr) {
        printf("Немає дій для скасування");
        return;
    }

    Action* act = actTop;
    actTop = actTop->next;


    if (act->type == ActionType::ADD) {
        OrderNode* node = findOrderById(list, act->orderCopy.id);
        if (!node) {
                printf("Замовлення не знайдено");
                delete act;
                return;
        }
        if (node->order.status != Status::WAITING) {
            printf("Додавання замовлення №%d скасувати неможливо: його вже передано майстру.\n", node->order.id);
            delete act;
            return;
        }
        removeFromQueue(pqHead, &node->order);
        unlinkOrderNode(list, node);
        printf("Скасовано додавання замовлення №%d: його видалено з журналу і черги.\n", node->order.id);
        delete node;
        delete act;
        return;
    }

    if (act->type == ActionType::REMOVE) {
        Order ord = act->orderCopy;
        ord.status = Status::WAITING;
        ord.masterName[0] = '\0';
        appendOrderToList(list, ord);
        Order* storedPtr = &list.tail->order;
        enqueuePriority(pqHead, storedPtr);
        printf("Скасовано видалення замовлення №%d: його повернуто в кінець журналу і в чергу.\n", ord.id);
        delete act;
        return;
    }
    return;
}

Money revenue(const OrderNode* p) {
    if (p == nullptr) return Money {0,0};

    Money rest = revenue(p->next);

    if (p->order.status == Status::DONE) {
        return p->order.price + rest;
    }
    return rest;
}

void showReport(OrderList& list, Master* currentMaster) {
    if (list.size == 0) {
        printf("Замовлень немає\n");
    }
    else {
        Order** arr = new Order*[list.size];
        OrderNode* curr = list.head;
        int i = 0;
        while(curr != nullptr) {
            arr[i] = &curr->order;
            curr = curr->next;
            i++;
        }

        for (int i = 0; i < list.size; i++) {
            for (int j = 0; j < list.size - i - 1; j++) {
                if ((arr[j]->price < arr[j+1]->price) || (arr[j]->price == arr[j+1]->price && arr[j]->id > arr[j+1]->id)) {
                    Order* temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }      
            }
        }

        printf("Замовлення за вартістю:\n");
        for (int i = 0; i < list.size; i++) {
            const char* st = "WAITING";
            if (arr[i]->status == Status::REPAIR) st = "REPAIR";
            else if (arr[i]->status == Status::DONE) st = "DONE";

            printf("  №%-5d %7d.%02d грн  %s\n",
                   arr[i]->id,
                   arr[i]->price.hrn,
                   arr[i]->price.kop,
                   st);
        }

        Money maxPrice = arr[0]->price;
        Money minPrice = arr[list.size-1]->price;
        Money result = maxPrice - minPrice;

        printf("Різниця між найдорожчим і найдешевшим: %d.%02d грн\n", result.hrn, result.kop);
        delete[] arr;
    }

    Money totalRevenue = revenue(list.head);
    printf("Виручка за завершеними ремонтами: %d.%02d грн\n", totalRevenue.hrn, totalRevenue.kop);

    printf("Майстри, починаючи з наступного в черзі: \n");
    if (currentMaster == nullptr) {
        printf("Майстрів немає\n");
        return;
    }
    Master* currMaster = currentMaster;
    do{
        printf("  %-13s виконано: %d, виручка: %d.%02d грн\n", 
            currMaster->name, currMaster->completedCount, currMaster->revenue.hrn, currMaster->revenue.kop);
        currMaster = currMaster->next;
    } while (currMaster != currentMaster);
}

void reverse(OrderList& list) {
    if (list.size == 0) {
        printf("Журнал порожній\n");
        return;
    }

    OrderNode* curr = list.head;
    while(curr != nullptr) {
        OrderNode* nextNode = curr->next;
        curr->next = curr->prev;
        curr->prev = nextNode;
        curr = nextNode;
    }
    OrderNode* temp = list.head;
    list.head = list.tail;
    list.tail = temp;

    printf("Журнал розвернуто: тепер першим іде замовлення №%d, останнім №%d.\n", list.head->order.id, list.tail->order.id);
}

void clearOrderList(OrderList& list) {
    if (list.head == nullptr) return;
    OrderNode* curr = list.head;
    while(curr != nullptr) {
        OrderNode* temp = curr;
        curr = curr->next;
        delete temp;
    }
    list.head = list.tail = nullptr;
    list.size = 0;
}

void clearQueue(QNode*& pqHead) {
    if (pqHead == nullptr) return;
    QNode* curr = pqHead;
    while(curr != nullptr) {
        QNode* temp = curr;
        curr = curr->next;
        delete temp;
    }
    pqHead = nullptr;
}

void clearActions(Action*& actTop) {
    if (actTop == nullptr) return;
    Action* curr = actTop;
    while(curr != nullptr) {
        Action* temp = curr;
        curr = curr->next;
        delete temp;
    }
    actTop = nullptr;
}

void clearMasters(Master*& masterHead) {
    if (masterHead == nullptr) return;

    Master* tail = masterHead;
    while (tail->next != masterHead) {
        tail = tail->next;
    }
    tail->next = nullptr; 

    Master* curr = masterHead;
    while (curr != nullptr) {
        Master* temp = curr;
        curr = curr->next;
        delete temp;
    }
    masterHead = nullptr;
}

void clearAll(OrderList& list, QNode*& pqHead, Action*& actTop, Master*& masterHead) {
    clearOrderList(list);
    clearQueue(pqHead);
    clearActions(actTop);
    clearMasters(masterHead);
}

int main() {
    OrderList list{nullptr, nullptr, 0};
    QNode* pqHead = nullptr;
    Action* actTop = nullptr;
    int nextId = 101;
    Master* masterHead = nullptr;
    Master* masterTail = nullptr;

    char buf[256];
    printf("Кількість майстрів (від 1 до 5): ");
    if (!cin.getline(buf, sizeof(buf))) return 0;
    int n = atoi(buf);

    printf("Імена майстрів через пробіл: ");
    if (!cin.getline(buf, sizeof(buf))) return 0;

    char* token = strtok(buf, " ");
    while(token != nullptr) {
        appendMaster(masterHead, masterTail, token);
        token = strtok(nullptr, " ");
    }

    Master* currentMaster = masterHead;

    while(true) {
        printf("\nМеню:\n");
        printf("1 - Додати замовлення\n");
        printf("2 - Журнал замовлень\n");
        printf("3 - Видати замовлення майстру\n");
        printf("4 - Завершити ремонт\n");
        printf("5 - Видалити замовлення\n");
        printf("6 - Скасувати останню дію\n");
        printf("7 - Звіт\n");
        printf("8 - Розвернути журнал\n");
        printf("0 - Вийти\n");
        printf("Ваш вибір: ");

        if (!cin.getline(buf, sizeof(buf))) break;

        if (strcmp(buf, "1") == 0) {
            addOrder(list, pqHead, actTop, nextId);
        }
        else if (strcmp(buf, "2") == 0) {
            printJournal(list, pqHead);
        } 
        else if (strcmp(buf, "0") == 0) {
            break;
        } 
        else if (strcmp(buf, "3") == 0) {
            assignOrderToMaster(pqHead, currentMaster);
        }
        else if (strcmp(buf, "4") == 0) {
            completeOrder(list, masterHead);
        }
        else if (strcmp(buf, "5") == 0) {
            deleteOrder(list, pqHead, actTop);
        }
        else if (strcmp(buf, "6") == 0) {
            popAction(list, pqHead, actTop);
        }
        else if (strcmp(buf, "7") == 0) {
            showReport(list, currentMaster);
        }
        else if (strcmp(buf, "8") == 0) {
            reverse(list);
        }
        else {
            printf("Помилка: пункту меню не існує або введено некоректно.\n");
        }
    }
    clearAll(list, pqHead, actTop, masterHead);
    return 0;
}