#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cctype>
using namespace std;
template <typename T>
struct Stack{
    struct Node{
        T key;
        Node* under;
    };
    Node* top=nullptr;
    int count = 0;
    void push( T new_val){
        top = new Node{new_val, top};
        count++;
    }
    T pop(){
        Node *t = top;
        T x = t->key;
        top = t->under;
        delete t;
        count --;
        return x;
    }
    bool empty(){
        return(top==nullptr);
    }
};

enum class DeviceType { PHONE = 1, LAPTOP, TV };
union DeviceInfo { int imei; char serial[12]; int inches; };
enum class Status { WAITING, REPAIR, DONE };
struct Client{
    char name[16]={};
    char phone[11]={};
};
struct Date{
    int day;
    int month;
    int year;
};
struct Money { 
    int hrn; 
    int kop; 
};
long long toKop(Money money){
    long long in_kop = money.hrn*100+money.kop;
    return in_kop;
}
int toHrn(int kop){
    int in_hrn = kop/(float)100;
    return in_hrn;
}
Money toMoney(int amount_in_kop){
    Money money ={};
    money.hrn=amount_in_kop/100;
    money.kop=amount_in_kop%100;
    return money;

}
Money operator+(const Money &money1,const Money &money2){
    return toMoney(toKop(money1)+toKop(money2));
}

Money operator-(const Money &money1,const Money &money2){
    return toMoney(toKop(money1)-toKop(money2));
}
bool operator>(const Money &money1,const Money &money2){
    return toKop(money1)>toKop(money2);
}
bool operator<(const Money &money1,const Money &money2){
    return toKop(money1)<toKop(money2);
}
bool operator==(const Money &money1,const Money &money2){
    return toKop(money1)==toKop(money2);
}
ostream& operator<<(ostream& os, Money money){
    char result[11]={};
    sprintf(result, "%d.%02d",money.hrn, money.kop);
    return os<<result;
}
struct Order{
    int id =100;
    Client client;
    Date date;
    Money cost={0,0};
    DeviceType type;
    DeviceInfo info;
    char problem[81]={};
    int priority=0;
    Status status = Status::WAITING;
    char masterName[24] = {};
    
};
struct OrderNode{
    Order order;
    OrderNode *prev=nullptr;
    OrderNode *next= nullptr;
    OrderNode(Order &curr_order, OrderNode *prevNode, OrderNode* nextNode){
        order=curr_order;
        prev=prevNode;
        next=nextNode;
    }
};

struct OrderList {
    OrderNode *head = nullptr;
    OrderNode *tail = nullptr;
    int size =0;

    Order* addOrder(Order &curr_order){
        OrderNode *newOrder = new OrderNode(curr_order,tail, nullptr);
        if (head==nullptr){
            head=newOrder;
            tail=newOrder;
        }else{
            tail->next = newOrder;
            tail=newOrder;
        }
        size++;
        return &newOrder->order;
    }
    OrderNode* findOrder(int id){
        OrderNode *now= head;
        while(now !=nullptr){
            if(now->order.id==id) return now;
            now=now->next;
        }
        return nullptr;
    }
    void removeOrder(OrderNode* ord_to_remove){
        if(ord_to_remove==nullptr){
            return;
        }
        if(ord_to_remove->prev != nullptr) {
            ord_to_remove->prev->next = ord_to_remove->next;
        }else {
            head = ord_to_remove->next;
        }
        if (ord_to_remove->next != nullptr) {
            ord_to_remove->next->prev = ord_to_remove->prev;
        } else {
            tail = ord_to_remove->prev;
        }
        delete ord_to_remove;
        size--;
    }
    void reverseOrderList(){
        if(head==nullptr || head==tail) return;
        OrderNode* oldHead = head;
        OrderNode* now = head;
        
        while(now!=nullptr){
            OrderNode* nextOrder = now->next;
            now->next=now->prev;
            now->prev=nextOrder;
            now=nextOrder;
        }
        head=tail;
        tail= oldHead;
    }
    void deleteOrderList(){
        OrderNode *now = head;
        while(now!=nullptr){
            OrderNode *nextNode = now->next;
            delete now;
            now=nextNode;
        }
        head=nullptr;
        tail = nullptr;
        size =0;
    }
};


struct QNode{
    Order *orderPtr;
    QNode *next=nullptr;
};
void enqueuePriority(QNode* &head_of_q, Order *oPtr){
    if (oPtr== nullptr)return;
    int ordPriority = oPtr->priority;
    if (head_of_q==nullptr || head_of_q->orderPtr->priority<ordPriority){
        QNode *newQNode = new QNode{oPtr, head_of_q};
        head_of_q=newQNode;
        return;
    }else{
        QNode *now = head_of_q;
        while(now->next!=nullptr && now->next->orderPtr->priority>=ordPriority){
            now=now->next;
        }
        now->next=new QNode{oPtr,now->next};
    }
}
Order *dequePriority(QNode* &head_of_q){
    if(head_of_q==nullptr) return nullptr;
    QNode *temp = head_of_q;
    Order*result = temp->orderPtr;
    head_of_q=head_of_q->next;
    delete temp;
    return result;
}
bool removeFromQ(QNode *&head_of_q, Order *ord_to_remove){
    if(head_of_q==nullptr || ord_to_remove==nullptr) return false;
    QNode *prev = nullptr;
    QNode *now = head_of_q;
    while(now!=nullptr){
        if (now->orderPtr==ord_to_remove){
            if(prev==nullptr){
                head_of_q=now->next;
            }else{
                prev->next=now->next;
            }
            delete now;
            return true;
        }
        prev=now;
        now=now->next;
    }
    return false;
}
int countQueue(QNode *head_of_q){
    int count =0;
    QNode *now = head_of_q;
    while(now!=nullptr){
        count++;
        now=now->next;
    }
    return count;
}
void clearQueue(QNode *&head_of_q){
    while(head_of_q!=nullptr){
        QNode *temp = head_of_q;
        head_of_q=head_of_q->next;
        delete temp;
    }
}


struct Master{
    char name [24]={};
    int total_done =0;
    Money total_money={0,0};
    Master* next = nullptr;

    Master(const char *masterName,Master* nextMaster=nullptr){
        strcpy(name, masterName);
        next = nextMaster;
    }
    
    Master* whoNextMaster(Master *&nextMaster){
        if (nextMaster == nullptr) return nullptr;
        Master *now = nextMaster;
        nextMaster = nextMaster->next;
        return now;
    }
    void printMasters(Master* nextMaster){
        if (nextMaster==nullptr) return;
        Master *now = nextMaster;
        do{
            cout<<"  "<<now->name<<setw(5)<<""<<"виконано: "<<now->total_done<<", виручка: "<<now->total_money<<" грн\n";
            now=now->next;
        }while(now!=nextMaster);

    }
};
Master* addMaster(Master *&head,const char *masterName ){
    Master *newNode= new Master(masterName);
    if(head==nullptr){
        head = newNode;
        newNode->next=head;
     }else{
        Master *temp = head;
        while(temp->next!=head){
            temp=temp->next;
        }
         temp->next=newNode;
         newNode->next=head;
    }  
    return newNode;    
}
Master* findMasterByName(Master *head, const char *masterName) {
    if (head == nullptr) return nullptr;
    Master *now = head;
    do {
        if (strcmp(now->name, masterName) == 0) return now;
        now = now->next;
    } while (now != head);
    return nullptr;
}





enum class ActionType{ADD, DELETE};
struct Action{
    struct ActionNode{
    ActionType type;
    Order order;
    ActionNode *under = nullptr;
    };

    ActionNode* actionTop = nullptr;

    ~Action(){
        while(actionTop!=nullptr){
            ActionType temp_type;
            Order temp_ord;
            pop(temp_ord, temp_type);
        }
    }

    void push(ActionType new_type, Order &ord){
        actionTop = new ActionNode{new_type, ord,actionTop };
    }
    bool pop(Order &popOrder, ActionType &popActionType){
        if(actionTop==nullptr) return false;
        ActionNode *t = actionTop;
        popActionType=t->type;
        popOrder=t->order;
        actionTop = actionTop->under;
        delete t;
        return true;
    }
    bool empty(){
        return(actionTop==nullptr);
    }

};


bool rpnMoneyToKop(const char *token, long long &inKop){
    if (token == nullptr) return false;
    int len = (int)strlen(token);
    if (len == 0) return false;

    int i = 0;
    int intDigits =0;
    long long hrn = 0;

    while (i<len && isdigit(token[i])) {
        intDigits++;
        if (intDigits > 6) return false;
        hrn = hrn*10 + (token[i]-'0');
        i++;
    }
    long long kop = 0;
    if (i < len) {
        if (token[i] != '.') return false;
        i++;

        int floatDigits = 0;
        while (i < len && isdigit(token[i])) {
            floatDigits++;
            if (floatDigits > 2) return false;
            kop = kop * 10 + (token[i] - '0');
            i++;
        }
        if (floatDigits == 0) return false;
        if (floatDigits == 1) kop *= 10;
    }
    if (i != len) return false;
    if (intDigits == 0 && kop == 0) return false;
    inKop = hrn * 100 + kop;
    return true;    
}


bool evalRPN(const char *expr, Money &res){
    if (expr == nullptr) {
        cout << "Помилка у виразі: порожній вираз.\n";
        return false;
    }

    bool hasNonSpace = false;
    int len = (int)strlen(expr);
    for (int i = 0; i < len; i++) {
        if (!isspace(expr[i])) {
            hasNonSpace = true;
            break;
        }
    }
    if (!hasNonSpace) {
        cout << "Помилка у виразі: порожній вираз.\n";
        return false;
    }

    Stack<long long int> stack;
    int i =0;

    while(i<len){
        while(i<len){
            if (!isspace(expr[i])) break;
            i++;
        }
        if (i==len) break;

        char token[64] = {};
        int tLen = 0;
        while(i<len && !isspace(expr[i])){
            token[tLen++] =expr[i];
            i++;
        }
        token[tLen] = '\0';
        bool isInt = true;
        for (int k = 0; k < tLen; k++){
            if (!isdigit(token[k])){
                isInt = false;
                break;
            }
        }
        long long inKop = 0;
        if (rpnMoneyToKop(token, inKop)) {
            if (inKop > (float)100000000) {
                cout<<"Помилка у виразі: число або проміжний результат понад 100000.00 грн.\n";
                while (!stack.empty()) stack.pop();
                return false;
            }
            stack.push(inKop);
        }else if (tLen == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*')) {
            char sign = token[0];
            if (stack.count < 2) {
                cout<<"Помилка у виразі: для операції «" <<sign<< "» бракує чисел.\n";
                while (!stack.empty()) stack.pop();
                return false;
            }
            long long b = stack.pop();
            long long a = stack.pop();
            long long r = 0;
            if (sign == '+') {
                r = a + b;
            } else if (sign == '-') {
                r = a - b;
                if (r < 0) {
                    cout<<"Помилка у виразі: проміжний результат від'ємний.\n";
                    while (!stack.empty()) stack.pop();
                    return false;
                }
            }else if (sign == '*') {
                if (b % 100 != 0) {
                    cout << "Помилка у виразі: множник має бути цілим числом від 1 до 100.\n";
                    while (!stack.empty()) stack.pop();
                    return false;
                }
                long long mult = b / 100;
                if (mult < 1 || mult > 100) {
                    cout << "Помилка у виразі: множник має бути цілим числом від 1 до 100.\n";
                    while (!stack.empty()) stack.pop();
                    return false;
                }
                r = a * mult;
                if (r>100000000){
                    cout << "Помилка у виразі: число або проміжний результат понад 100000.00 грн.\n\n";
                    while (!stack.empty()) stack.pop();
                    return false;
                }
            }
            stack.push(r);
        }else {
            cout <<"Помилка у виразі: «" << token << "» не є числом або операцією.\n";
            while (!stack.empty()) stack.pop();
            return false;
        }
    }
    if (stack.count != 1) {
        cout<< "Помилка у виразі: у стеку залишилось чисел: " << stack.count << ", а має бути одне.\n";
        while (!stack.empty()) stack.pop();
        return false;
    }

    long long totalKop = stack.pop();
    if (totalKop == 0) {
        cout << "Помилка у виразі: кінцевий результат 0.00.\n";
        return false;
    }

    res = toMoney((int)totalKop);
    return true;        
}

bool isvalidMasterName(const char* name){
    if (name[0] == '\0') {
        return false;
    }  
    int len = (int) strlen(name);
    if(len>23) return false;
    for (int i = 0; i<len; i++){
        if(!(isalpha(name[i]))) return false;
    }
    return true;
}
bool isValidClientName(const char *s) {
    if (s==nullptr) return false;
    int len = (int)strlen(s);
    if (len < 1 || len > 15) return false;
    for (int i = 0; i < len; i++) {
        char c = s[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) return false;
    }
    return true;
}

bool isValidPhone(const char *s) {
    if (s==nullptr) return false;
    if (strlen(s) != 10 || s[0] != '0') return false;
    for (int i = 0; i < 10; i++) {
        if (!isdigit((int)s[i])) return false;
    }
    return true;
}

bool isValidDate(const char *s, Date &date) {
    if (!s || strlen(s) != 10) return false;
    if (s[2] != '.' || s[5] != '.') return false;

    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit((int)s[i])) return false;
    }

    int d = (s[0] - '0') * 10 + (s[1] - '0');
    int m = (s[3] - '0') * 10 + (s[4] - '0');
    int y = (s[6] - '0') * 1000 + (s[7] - '0') * 100 + (s[8] - '0') * 10 + (s[9] - '0');

    if (y < 2000 || y > 2099 || m < 1 || m > 12) return false;

    int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (m == 2 && (y%4==0)) daysInMonth[2] = 29;

    if (d < 1 || d > daysInMonth[m]) return false;

    date.day = d;
    date.month = m;
    date.year = y;
    return true;
}
bool isValidDeviceType(const char *s, DeviceType &outType) {
    if (s==nullptr || (strlen(s)!=1)) return false;
    if (s[0] != '1' && s[0] != '2' && s[0] != '3') return false;
    outType = (DeviceType)(s[0] - '0');
    return true;
}
bool isValidImei(const char *s, int &outImei) {
    if (s==nullptr || strlen(s) != 6) return false;
    int val = 0;
    for (int i = 0; i < 6; i++) {
        if (!isdigit((int)s[i])) return false;
        val = val * 10 + (s[i] - '0');
    }
    outImei = val;
    return true;
}
bool isValidSerial(const char *s) {
    if (s==nullptr) return false;
    int len = (int)strlen(s);
    if (len < 1 || len > 11) return false;
    for (int i = 0; i < len; i++) {
        if (!isdigit(s[i]) && !isupper(s[i])) return false;
    }
    return true;
}
bool isValidInches(const char *s, int &outInches) {
    if (s==nullptr) return false;
    int len = (int) strlen(s);
    if (len < 2 || len > 3) return false;
    int val = 0;
    for (int i = 0; i < len; i++) {
        if (!isdigit((int)(s[i]))) return false;
        val = val * 10 + (s[i] - '0');
    }
    if (val < 19 || val > 100) return false;
    outInches = val;
    return true;
}
bool isValidProblem(const char *s) {
    if (s==nullptr) return false;
    int len = (int)strlen(s);
    return len >= 1 && len <= 80;
}
bool isValidPriority(const char *s, int &outPriority) {
    if (s==nullptr || strlen(s)!=1) return false;
    if (s[0] != '1' && s[0] != '2' && s[0] != '3') return false;
    outPriority = s[0] - '0';
    return true;
}

bool firstAddMasters(char*names, int n, Master*&head){
    int foundCount = 0;
    char *token = strtok(names, " \n");

    while (token != nullptr) {
        if (!isvalidMasterName(token)) {
            return false;
        }
        if (findMasterByName(head, token) != nullptr) {
            cout << "Помилка: імена майстрів не повинні повторюватися.\n";
            return false;
        }
        addMaster(head, token);
        foundCount++;
        token = strtok(nullptr, " \n");
    }

    return foundCount == n;
}


void addOrderMenu(OrderList &orders, QNode *&pqHead, Action &actions, int &nextId) {
    char buf[256] = {};

    cout << "Ім'я клієнта: ";
    cin.getline(buf, sizeof(buf));
    if (!isValidClientName(buf)) {
        cout << "Помилка: ім'я має містити від 1 до 15 латинських літер.\n";
        return;
    }
    Client client{};
    strcpy(client.name, buf);

    cout << "Телефон (10 цифр): ";
    cin.getline(buf, sizeof(buf));
    if (!isValidPhone(buf)) {
        cout << "Помилка: телефон має складатися з 10 цифр і починатися з 0.\n";
        return;
    }
    strcpy(client.phone, buf);

    cout << "Дата прийому (ДД.ММ.РРРР): ";
    cin.getline(buf, sizeof(buf));
    Date date{};
    if (!isValidDate(buf, date)) {
        cout << "Помилка: некоректна дата.\n";
        return;
    }

    cout << "Тип пристрою (1 телефон, 2 ноутбук, 3 телевізор): ";
    cin.getline(buf, sizeof(buf));
    DeviceType type{};
    if (!isValidDeviceType(buf, type)) {
        cout << "Помилка: тип пристрою має бути 1, 2 або 3.\n";
        return;
    }
    DeviceInfo info{};
    if (type == DeviceType::PHONE) {
        cout << "Останні 6 цифр IMEI: ";
        cin.getline(buf, sizeof(buf));
        if (!isValidImei(buf, info.imei)) {
            cout << "Помилка: потрібно рівно 6 цифр.\n";
            return;
        }
    } else if (type == DeviceType::LAPTOP) {
        cout << "Серійний номер: ";
        cin.getline(buf, sizeof(buf));
        if (!isValidSerial(buf)) {
            cout << "Помилка: серійний номер має містити від 1 до 11 великих літер і цифр.\n";
            return;
        }
        strcpy(info.serial, buf);
    } else {
        cout << "Діагональ (дюймів): ";
        cin.getline(buf, sizeof(buf));
        if (!isValidInches(buf, info.inches)) {
            cout << "Помилка: діагональ має бути від 19 до 100 дюймів.\n";
            return;
        }
    }
    char problemBuf[128] = {};
    cout << "Опис несправності: ";
    cin.getline(problemBuf, sizeof(problemBuf));
    if (!isValidProblem(problemBuf)) {
        cout << "Помилка: опис несправності має містити від 1 до 80 байтів.\n";
        return;
    }

    cout << "Пріоритет (1 звичайний, 2 підвищений, 3 терміновий): ";
    cin.getline(buf, sizeof(buf));
    int priority = 0;
    if (!isValidPriority(buf, priority)) {
        cout << "Помилка: пріоритет має бути 1, 2 або 3.\n";
        return;
    }

    char exprBuf[256] = {};
    cout << "Вартість (обернений польський запис): ";
    cin.getline(exprBuf, sizeof(exprBuf));
    Money price{};
    if (!evalRPN(exprBuf, price)) {
        return;
    }
    Order ord{};
    ord.id = nextId++;
    ord.client = client;
    ord.date = date;
    ord.type = type;
    ord.info = info;
    strcpy(ord.problem, problemBuf);
    ord.priority = priority;
    ord.cost = price;
    ord.status = Status::WAITING;
    ord.masterName[0] = '\0';
    Order *storedPtr = orders.addOrder(ord);
    enqueuePriority(pqHead, storedPtr);
    actions.push(ActionType::ADD, ord); 
    cout<<"Замовлення №"<<ord.id<<" додано: вартість " << ord.cost<< " грн, у черзі на ремонт: " <<countQueue(pqHead) << ".\n";   
}
ostream &operator<<(ostream &os, const Order &o) {
    char dateStr[11];
    sprintf(dateStr, "%02d.%02d.%04d", o.date.day, o.date.month, o.date.year);

    char typeStr[7] = {};
    char detailsStr[15] = {};
    if (o.type == DeviceType::PHONE) {
        strcpy(typeStr,"PHONE");
        sprintf(detailsStr, "IMEI %06d", o.info.imei);
    } else if (o.type == DeviceType::LAPTOP) {
        strcpy(typeStr, "LAPTOP");
        sprintf(detailsStr, "SN %s", o.info.serial);
    } else {
        strcpy(typeStr,"TV");
        sprintf(detailsStr, "%d inch", o.info.inches);
    }
    char statusStr[8] = {};
    if (o.status == Status::WAITING) strcpy(statusStr , "WAITING");
    else if (o.status == Status::REPAIR) strcpy(statusStr,"REPAIR");
    else strcpy(statusStr,"DONE");
    char costStr[10];
    sprintf(costStr, "%d.%02d", o.cost.hrn, o.cost.kop);
    char output[200]={};
    sprintf(output, "| %3d | %-15s | %-10s | %-10s | %-6s | %-14s | %2d | %-7s | %9s |",o.id, o.client.name, o.client.phone, dateStr,typeStr, detailsStr, o.priority, statusStr, costStr);
    os<<output;
    return os;
}
void printOrderJournal(const OrderList &orders, QNode *pqHead) {
    if (orders.head == nullptr) {
        cout << "Журнал порожній.\n";
        return;
    }

    char line[] = "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+";
    cout << line << "\n"<< "|   № | Клієнт          | Телефон    | Дата       | Тип    | Деталі         | Пр | Статус  |  Вартість |\n"<< line << "\n";

    OrderNode *now = orders.head;
    while (now != nullptr) {
        cout << now->order << "\n";
        now = now->next;
    }
    cout << line << "\n";
    cout << "Усього замовлень: " << orders.size<< ", у черзі на ремонт: " << countQueue(pqHead) << "\n";
}
void assignOrderToMaster(QNode *&pqHead, Master *&currentMaster) {
    if (pqHead == nullptr) {
        cout << "Черга на ремонт порожня.\n";
        return;
    }

    Order *ord = dequePriority(pqHead);
    Master *m = currentMaster;
    currentMaster = currentMaster->next;

    ord->status = Status::REPAIR;
    strcpy(ord->masterName, m->name);

    cout<< "Замовлення №" << ord->id << " (пріоритет " << ord->priority<< ") передано майстру " << m->name << ".\n";
    cout<< "Несправність: " << ord->problem << "\n";
    cout<< "У черзі залишилось: " << countQueue(pqHead) << "\n";
}
void finishRepair(OrderList &orders, Master *masterHead) {
    int id = 0;
    cout << "Номер замовлення: ";
    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Помилка: номер замовлення має бути цілим числом.\n";
        return;
    }
    cin.ignore(10000, '\n');
    OrderNode *node = orders.findOrder(id);
    if (node == nullptr) {
        cout << "Замовлення №"<<id << " не знайдено.\n";
        return;
    }
    
    Order &ord = node->order;

    if (ord.status == Status::WAITING) {
        cout << "Замовлення №" << id << " ще не передано майстру.\n";
        return;
    }
    if (ord.status == Status::DONE) {
        cout << "Замовлення №" << id << " уже завершено.\n";
        return;
    }

    Money cost = ord.cost;
    ord.status = Status::DONE;

    Master *m = findMasterByName(masterHead, ord.masterName);
    if (m != nullptr) {
        m->total_done++;
        m->total_money = m->total_money + cost;
        cout<<"Ремонт замовлення №"<< ord.id << " завершено. Майстер " << m->name<< ": виконано " << m->total_done<< ", виручка "<< m->total_money<< " грн.\n";
    }
}

void deleteOrder(OrderList &orders, QNode *&pqHead, Action &actions) {
    int id = 0;
    cout << "Номер замовлення: ";
    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Помилка: номер замовлення має бути цілим числом.\n";
        return;
    }
    cin.ignore(10000, '\n');

    OrderNode *node = orders.findOrder(id);
    if (node == nullptr) {
        cout << "Замовлення №" << id << " не знайдено.\n";
        return;
    }

    if (node->order.status != Status::WAITING) {
        cout << "Видалити можна лише замовлення, яке очікує в черзі.\n";
        return;
    }

    Order deletedCopy = node->order;
    actions.push(ActionType::DELETE, deletedCopy);

    removeFromQ(pqHead, &node->order);
    orders.removeOrder(node);
    cout<< "Замовлення №"<< id << " видалено. У журналі: " << orders.size<< ", у черзі: " << countQueue(pqHead) << ".\n";
}

void undoLastAction(OrderList &orders, QNode *&pqHead, Action &actions) {
    Order lastOrder={};
    ActionType lastType={};

    if (!actions.pop(lastOrder, lastType)) {
        cout << "Немає дій для скасування.\n";
        return;
    }
    if (lastType == ActionType::ADD) {
        OrderNode *node = orders.findOrder(lastOrder.id);
        if (node == nullptr) {
            cout << "Скасовано додавання замовлення №" << lastOrder.id << ".\n";
            return;
        }

        if (node->order.status != Status::WAITING) {
            cout << "Неможливо скасувати додавання: замовлення №" << lastOrder.id<< " уже передано в роботу або виконано.\n";
            return;
        }

        removeFromQ(pqHead, &node->order);
        orders.removeOrder(node);
        cout << "Скасовано додавання замовлення №" << lastOrder.id << ".\n";
    } else if (lastType == ActionType::DELETE) {
        Order *restoredPtr = orders.addOrder(lastOrder);
        if (restoredPtr->status == Status::WAITING) {
            enqueuePriority(pqHead, restoredPtr);
        }
        cout << "Скасовано видалення замовлення №" << lastOrder.id << ".\n";
    }
}
bool isPriceGreater(const Order *a, const Order *b) {
    if (!(a->cost == b->cost)) {
        return a->cost > b->cost;
    }
    return a->id < b->id;
}
void sortOrderPrice(Order **arr, int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            if (isPriceGreater(arr[j+1], arr[j])) {
                Order *tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}
Money revenue(const OrderNode *p) {
    if (p == nullptr) {
        return Money{0, 0};
    }

    Money current{0, 0};
    if (p->order.status == Status::DONE) {
        current = p->order.cost;
    }
    return current + revenue(p->next);
}
void printMastersFrom(const Master *start, const OrderList &orders) {
    if (start == nullptr) return;
    const Master *now = start;
    do {
        int doneCount = 0;
        Money masterRevenue{0, 0};
        const OrderNode *node = orders.head;
        while (node != nullptr) {
            if (node->order.status == Status::DONE &&
                strcmp(node->order.masterName, now->name) == 0) {
                doneCount++;
                masterRevenue = masterRevenue + node->order.cost;
            }
            node = node->next;
        }
        cout << "  " << left << setw(12) << now->name << right<< " виконано: " << now->total_done<< ", виручка: " << now->total_money << " грн\n";
        now = now->next;
    } while (now != start);
}
void printReport(const OrderList &orders, const Master *currentMaster) {
    if (orders.head == nullptr || orders.size <= 0) {
        cout << "Журнал порожній. Звіт не сформовано.\n";
        return;
    }

    int n = orders.size;
    Order **arr = new Order*[n];

    int index = 0;
    Money minCost = orders.head->order.cost;
    Money maxCost = orders.head->order.cost;
    OrderNode *now = orders.head;
    while (now != nullptr) {
        Order *temp=&now->order;
        arr[index++] = temp;
        if (toKop(now->order.cost) < toKop(minCost)) {
            minCost = now->order.cost;
        }
        if (toKop(now->order.cost) > toKop(maxCost)) {
            maxCost = now->order.cost;
        }
        now = now->next;
    }
    sortOrderPrice(arr,n);
    cout<<"Замовлення за вартістю:\n";
    for(int i =0; i<n; i++){
        Order *ord = arr[i];
        char str[200]={};
        char st[10]={};
        if (ord->status == Status::WAITING) strcpy(st,"WAITING");
        else if (ord->status == Status::REPAIR) strcpy(st,"REPAIR");
        else strcpy(st,"DONE");
        sprintf(str, "  №%-5d%d.%02d грн  %s\n", ord->id,ord->cost.hrn, ord->cost.kop, st);
        cout<<str;
    }
    Money priceDiff = maxCost - minCost;
    Money totalDoneRevenue = revenue(orders.head);

    cout << "Різниця між найдорожчим і найдешевшим замовленням: " << priceDiff << " грн.\n";
    cout << "Виручка за завершеними ремонтами: " << totalDoneRevenue << " грн.\n";
    printMastersFrom(currentMaster,orders); 
    
    delete[] arr;
}

void freeOrderList(OrderList &orders) {
    OrderNode *curr = orders.head;
    while (curr != nullptr) {
        OrderNode *nextNode = curr->next;
        delete curr;
        curr = nextNode;
    }
    orders.head = nullptr;
    orders.tail = nullptr;
    orders.size = 0;
}

void freePriorityQueue(QNode *&pqHead) {
    QNode *curr = pqHead;
    while (curr != nullptr) {
        QNode *nextNode = curr->next;
        delete curr;
        curr = nextNode;
    }
    pqHead = nullptr;
}
void freeActionStack(Action &actions){
    Order ord={};
    ActionType act={};
    while(!actions.empty()){
        actions.pop(ord, act);
    }
}
void freeMastersList(Master *&startMaster) {
    if (startMaster == nullptr) {
        return;
    }
    Master *now=startMaster->next;
    while(now!=startMaster){
        Master* temp = now;
        now = now->next;
        delete temp;
    }
    delete startMaster;
    startMaster = nullptr;
    now=nullptr;
}
void clearAll(OrderList &orders, QNode *&pqHead, Action &actions, Master *&currentMaster){
    freePriorityQueue(pqHead);
    freeActionStack(actions);
    freeOrderList(orders);
    freeMastersList(currentMaster); 
}
int main(){
    OrderList orders={};
    QNode *pqHead = nullptr;
    Action actions={};
    Master *currentMaster = nullptr;
    int nextId = 101;
    int n;

    while(true){
        cout<<"Кількість майстрів (від 1 до 5):\n";
        cin>>n;
        if (cin.fail() || n<1 || n>5){
            cin.clear();
            cin.ignore(1000, '\n');
            cout<<"Помилка. очікується ціле додатнє число.\n";
        }else break;
    }
    cin.ignore(1000, '\n');
    
    char names[120]={};
    while(true) {
        cout << "Імена майстрів через пробіл: ";
        if (!cin.getline(names, sizeof(names))) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Рядок занадто довгий. Спробуйте ще раз.\n";
        }else break;
    }

    if(!firstAddMasters(names,n,currentMaster)){
        cout<<"Некоректний ввід імен.\n";
        clearAll(orders,pqHead,actions,currentMaster);
        return 1;
    }
    int choice = -1;
    do{
        while(true){
            cout<<"\nМеню\n1 Додати замовлення\n2 Журнал замовлень\n3 Видати замовлення майстру\n4 Завершити ремонт\n5 Видалити замовлення\n6 Скасувати останню дію\n7 Звіт\n8 Розвернути журнал\n0 Вийти \n";
            cout<<"Ваш вибір: ";
            if(!(cin >> choice) || choice<0 || choice>8) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout<<"Помилка. Введіть цифру доступну з меню.\n";
            }else break;
            
        }
        cin.ignore(1000, '\n');
        switch(choice){
            case 1:
                addOrderMenu(orders,pqHead,actions, nextId);
                break;
            case 2:
                printOrderJournal(orders, pqHead);
                break;
            case 3:
                assignOrderToMaster(pqHead,currentMaster);
                break;
            case 4:
                finishRepair(orders, currentMaster);
                break;
            case 5:
                deleteOrder(orders,pqHead,actions);
                break;
            case 6:
                undoLastAction(orders,pqHead,actions);
                break;
            case 7:
                printReport(orders,currentMaster);
                break;
            case 8:
                orders.reverseOrderList();
                break;
            case 0:
                clearAll(orders,pqHead,actions,currentMaster);
                break;
            default:
                cout<<"Непередбачуваний ввід. Оберіть цифру з меню.\n";
                break;
        }
    }while(choice!=0);
}