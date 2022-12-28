#include <iostream>

template<typename Key, typename Info>
class Sllist {
private:
    
    template<typename NKey, typename NInfo>
    struct Node {
        NKey key;
        NInfo info;
        Node<NKey,NInfo> *next;
        
        Node(): key(), info(), next(nullptr) {};
        Node(const NKey &k, const NInfo &i): key(k), info(i), next(nullptr) {};
    };
    
    Node<Key,Info> *head, *tail;
    
    void printNode(const Node<Key,Info> *node, std::ostream &os) const;
    
public:
    
    //***** Default Constructor, Copy Constructor, Assignment Operator, Destructor *****
    Sllist(): head(nullptr), tail(nullptr) {};
    Sllist(const Sllist<Key,Info> &sll): head(nullptr) { *this = sll; }
    Sllist<Key,Info>& operator=(const Sllist<Key,Info> &rhs);
    ~Sllist();
    
    //***** Adding, removing and peeking from head and tail *****
    void pushFront(const Key &key, const Info &info);
    void pushBack(const Key &key, const Info &info);
    Info popFront(); // Deleting from head and then it will return the info that is deleted
    Info popBack(); // Deleting from tail and then it will return the info that is deleted
    Info front() const;
    Info back() const;
    
    //***** Adding, removing, searching and getting info by key *****
    bool insertAfter(const Key &location, const Key &newKey, const Info &newInfo, int occur = 1);
    bool deleteByKey(const Key &location, int occur = 1);
    Info getInfo(const Key& location, int occur = 1);
    bool search(const Key& location) const;
    
    //***** Display methods *****
    void print(std::ostream &os = std::cout) const;
    
    //***** Operator Overloading *****
    bool operator==(const Sllist<Key,Info> &rhs) const;
    bool operator!=(const Sllist<Key,Info> &rhs) const;
    
    //***** Other methods *****
    void clear();
    bool isEmpty() const;
    int length() const;

};

template<typename Key, typename Info>
void Sllist<Key,Info>::printNode(const Node<Key,Info> *node, std::ostream &os) const {
    os << "Key: " << node -> key << " Info: " << node -> info << std::endl;
}

//***** Default Constructor, Copy Constructor, Assignment Operator, Destructor *****

template<typename Key, typename Info>
Sllist<Key,Info>& Sllist<Key,Info>::operator=(const Sllist<Key,Info> &rhs) {
    
    if(this == &rhs) {return *this;}
    
    this -> clear();
    
    Node<Key,Info> *temp;
    temp = rhs.head;
    while(temp != nullptr) {
        this -> pushBack(temp -> key, temp -> info);
        temp = temp -> next;
    }
    return *this;
}

template<typename Key, typename Info>
Sllist<Key,Info>::~Sllist() {
    clear();
} 

//************************************************************************************

//***** Adding, removing and peeking from head and tail ******************************

template<typename Key, typename Info>
void Sllist<Key,Info>::pushFront(const Key &key, const Info &info) {
    Node<Key,Info> *newnode;
    newnode = new Node<Key,Info>(key, info);
    newnode -> next = head;
    head = newnode;
    if(tail == nullptr) {tail = newnode;}
}

template<typename Key, typename Info>
void Sllist<Key,Info>::pushBack(const Key &key, const Info &info) {
    
    if(head == nullptr) {
        pushFront(key, info);
        return;
    }
    
    Node<Key,Info> *newnode;
    newnode = new Node<Key,Info>(key, info);
    newnode -> next = nullptr;
    tail -> next = newnode;
    tail = newnode;
}

template<typename Key, typename Info>
Info Sllist<Key,Info>::popFront() {
   if(head == nullptr) {std::cout<<"List is empty"<<std::endl; return Info();}
    
    Info out;
    out = head -> info;
    Node<Key,Info> *temp = head;
    if(head -> next == nullptr) {tail = nullptr;}
    head = head -> next;
    delete temp;

    
    return out;
}

template<typename Key, typename Info>
Info Sllist<Key,Info>::popBack() {
    if(head == nullptr) {std::cout<<"List is empty"<<std::endl; return Info();}
    if(head -> next == nullptr) {return popFront();}
    
    auto out = tail -> info;
    auto temp = head;
    while(temp -> next -> next != nullptr) {
        temp = temp -> next;
    }
    delete tail;
    tail = temp;
    temp -> next = nullptr;
    
    return out;
}

template<typename Key, typename Info>
Info Sllist<Key,Info>::front() const {
    if(head == nullptr) {return Info();}
    return head -> info;
}

template<typename Key, typename Info>
Info Sllist<Key,Info>::back() const {
    if(head == nullptr) {return Info();}
    return tail -> info;
}

//************************************************************************************

//***** Adding, removing, searching and getting info by key **************************

template<typename Key, typename Info>
bool Sllist<Key,Info>::insertAfter(const Key &location, const Key &newKey, const Info &newInfo, int occur) {
    if(occur < 1) {return false;}
    if(head == nullptr) {return false;}
    
    auto temp = head;
    int repeat{0};
    while(temp != nullptr) {
        if(temp -> key == location && ++repeat == occur) {
            auto newnode = new Node<Key, Info>(newKey,newInfo);
            newnode -> next = temp -> next;
            temp -> next = newnode;
            if(temp == tail) {tail = newnode;}
            return true;
        }
        temp = temp -> next;
    }
    return false;
}

template<typename Key, typename Info>
bool Sllist<Key,Info>::deleteByKey(const Key &location, int occur) {
    if(occur < 1) {return false;}
    if(head == nullptr) {return false;}
    
    Node<Key,Info>* temp = head;
    Node<Key,Info>* prev = nullptr;
    int repeat{0};
    while(temp != nullptr) {
        if(temp -> key == location && ++repeat == occur) {
            
            if(temp == head) {
                head = temp -> next;
                delete temp;
                return true;
            }
            
            prev -> next = temp -> next;
            if(temp == tail) {tail = prev;}
            delete temp;
            return true;
        }
        prev = temp;
        temp = temp -> next;
    }
    return false;
}

template<typename Key, typename Info>
Info Sllist<Key,Info>::getInfo(const Key& location, int occur) {
    if(occur < 1) {return Info();}
    if(head == nullptr) {std::cout << "List is empty" << std::endl; return Info();}
    
    auto temp = head;
    int repeat{0};
    
    while(temp != nullptr) {
        if(temp -> key == location && ++repeat == occur) {
            return temp -> info;
        }
        temp = temp -> next;
    }
    return Info();
}

template<typename Key, typename Info>
bool Sllist<Key,Info>::search(const Key& location) const {
    auto temp = head;
    while(temp != nullptr) {
        if(temp -> key == location) {
            return true;
        }
        temp = temp -> next;
    }
    return false;
}
//************************************************************************************    

//***** Operator Overloading *********************************************************

template<typename Key, typename Info>
bool Sllist<Key,Info>::operator==(const Sllist<Key,Info> &rhs) const {
    
    if(head == nullptr && rhs.head == nullptr) {return true;}
    if(length() != rhs.length()) {return false;}
    
    Node<Key,Info> *left = head;
    Node<Key,Info> *right = rhs.head;
    
    while(left != 0) {
        if(left -> key != right -> key || left -> info != right -> info) {return false;}
        
        left = left -> next;
        right = right -> next;
    }
    
    return true;
}

template<typename Key, typename Info>
bool Sllist<Key,Info>::operator!=(const Sllist<Key,Info> &rhs) const {
    return !(*this == rhs);
}

//************************************************************************************

//***** Display methods **************************************************************
template<typename Key, typename Info>
void Sllist<Key,Info>::print(std::ostream &os) const {
    os << "Data in the list: " << std::endl;
    auto temp = head;
    while(temp != nullptr) {
        printNode(temp, os);
        temp = temp -> next;
    }
    os << "===========================" <<  std::endl;
}

//************************************************************************************    

//***** Other methods ****************************************************************
template<typename Key, typename Info>
void Sllist<Key,Info>::clear() {
    
    while(head != nullptr) {
        tail = head;
        head = head -> next;
        delete tail;
    }
    tail = nullptr;
}

template<typename Key, typename Info>
bool Sllist<Key,Info>::isEmpty() const {
    if(head == nullptr) {return true;}
    return false;
}

template<typename Key, typename Info>
int Sllist<Key,Info>::length() const {
    
    int count {0};
    Node<Key,Info> *temp = head;
    while(temp != nullptr) {
        count++;
        temp = temp -> next;
    }
    return count;
}

//************************************************************************************

int main() {
    
    Sllist<int,int>a;
    a.pushFront(3,5);
    a.pushBack(7,4);
    a.pushBack(6,4);
    a.pushFront(1,1);
    a.pushFront(1,2);
    a.pushFront(3,2);
    a.pushBack(8,8);
    a.pushBack(3,8);
    a.print();
    
    // a.popBack();
    // a.popFront();
    // a.print();
    
    // std::cout<< a.front() <<std::endl;
    // std::cout<< a.back() <<std::endl; 
    
    // a.insertAfter(3,9,9,1);
    // a.print();
    
    // a.deleteByKey(3,2);
    // a.print();
    
    //std::cout<< a.getInfo(3,2) <<std::endl;
    
    // std::cout<< std::boolalpha;
    // std::cout<< a.search(3) <<std::endl;
    
    // std::cout<< std::boolalpha;    
    // Sllist<int,int>b1;
    // b1.pushFront(3,5);
    // b1.pushBack(7,4);
    // b1.pushBack(6,4);   
    // Sllist<int,int>b2;
    // b2.pushFront(3,5);
    // b2.pushBack(7,4);
    // b2.pushBack(6,4);
    // bool c;
    // c = b1==b2;
    // std::cout << c <<std::endl;
}
