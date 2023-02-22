// 线性表抽象类
#include <iostream>


template < class elemType>
class list {
    public:
    // 清除
    virtual void clear() = 0;
    // 长度
    virtual int length() const = 0;
    // 插入
    virtual void insert(int i,  const elemType &x) = 0;
    // 删除
    virtual void remove(int i) = 0;
    // 搜索
    virtual int search(const elemType &x) const = 0;
    // 访问
    virtual elemType visit(int i) const = 0;
    // 遍历 
    virtual void traverse() const = 0;
    // 析构
    virtual ~list() {};
};


// ************************************************************************************************

template < class elemType>
class seqList : public list<elemType> {
private:
    elemType *data;
    int currentLength;
    int maxSize;
    // 为截距插入元素时，数组容量不够的问题
    void doubleSpace();

public:
    seqList(int initSize=10);
    // 析构函数，还掉动态空间
    ~seqList() { delete [] data};
    // 清空数组元素：只把表长设置为0
    void clear() { currentLength = 0;}

    // 数组长度：只需返回这个私有成员变量
    int length() { return currentLength;}
    void insert(int i, const eleType &x);
    void remove( int i);
    int search(const elemType &x) const;
    // 访问数组元素：返回下标为i的数组元素
    elemType visit(int i) const { return data[i]; }
    void traverse() const;

}

// 初始化
template < class elemType>
class seqList<elemType> :: seqList(int initSize){
    data = new elemType[initSize];
    maxSize = initSize;
    currentLength = 0;
}

// 搜索函数
template < class elemType>
int seqList<elemType> :: search(const elementType & x) const {
    int i;
    // 空循环，不满足条件跳出
    for(i=0; i < currentLength && data[i] != x; ++i);
    if(i == currentLength)
        return -1;
    return i;
}

// 遍历函数
template < class elemType>
void seqList<elemType> :: traverse() const {
    cout << endl;
    for(int i=0; i < currentLength; ++i){
        cout << data[i] << ' ';
    }
}

// 插入函数
template < class elemType>
void seqList<elemType> :: insert(int i, const elemType &x){
    // 如果数组放满了，先扩大空间
    if (currentLength == maxSize){
        doubleSpace();
    }
    // 从后往前，元素后移
    for (int j = currentLength ; j > i; j-- ){
        data[j] = data[j-1];
    }
    // 空出空间，插入元素，表长加一
    data[i] = x;
    ++currentLength;
}


// 扩大数组空间
template <class elemType>
void seqList<elemType>:: doubleSpace(){
    // 保证指向原来空间的指针
    elemType *tmp = data;
    // 重新申请空间
    maxSize *= 2;
    data = new elemType[maxSize];
    // 拷贝原数据
    for(int i = 0; i < currentLength; i++){
        data[i] = tmp[i];
    }
    // 清除原来申请的空间
    delete [] tmp;
}


// 删除函数
template <class elemType>
void seqList<elemType>::remove(int i){
    // 从后所有元素往前推
    for(int j=i; j< currentLength; j++){
        data[j] = data[j+1];
    }
    --currentLength;
}


// ************************************************************************************************

template <class elemType>
class sLinkList: public list<elemType> {
private:
    // 定义一个节点的结构体，里面的所有成员都是公有的
    struct node {
        elemType data;
        node *next;
        node(const elemType &x, node *n=NULL){
            data = x;
            next = n;
        }
        node(): next(NULL) {}
        ~node() {};
    };
    node *head;
    int currentLength;
    node *move(int i) const;


public:
    sLinkList(){
        head = new node;
        currentLength = 0;
    }
    // 折构函数
    ~sLinkList() { clear(); delete head;}
    void clear();
    int length() const { return currentLength; }
    void remove(int i);
    int search(const elemType &x) const;
    elemType visit(int i) const;
    void traverse() const ;
};


template <class elemType>
void sLinkList<elemtype> :: clear(){
    node *p = head -> next, *q;
    while (p != NULL ){
        q = p -> next;
        delete p;
        p = q;
    }
}


template <class elemType>
void sLinkList<elemtype> :: insert(int i, const elemtType &x){
    node *pos;
    // 找打 i - 1个元素地址
    pos = move(i - 1);
    pos->next = new node(x, pos->next);
    ++currentLength;
}


template <class elemType>
sLinkList<elemtype>::node * void sLinkList<elemtype> ::move(int i) const {
    node *p = head;
    while(i-- >= 0) p = p->next;
    return p;
}


template <class elemType>
void sLinkList<elemtype>::remove(int i){
    node *pos, *delp;
    pos = move(i - 1);
    delp = pos->next;
    pos->next = delp->next;
    delete delp;
    --currentLength;
}


template <class elemType>
int sLinkList<elemtype>::search(const elemType &x) const {
    node *p = head->next;
    int i = 0;
    while ( p != NULL && p->data != x ){
        p = p->next;
        ++i;
    }
    if(p == NULL)
        return -1;
    else
        return i;
}


template <class elemType>
elemtype sLinkList<elemtype>::visit(int i) const {
    return move(i)->data;
}


template <class elemType>
elemtype sLinkList<elemtype>::traverse() const {
    node *p = head->next;
    cout << endl;
    while (p != NULL){
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}   



// ************************************************************************************************


template <class elemType>
class dLinkList: public list<elemType> {
private:
    struct node {
        elemType data;
        node *prev, *next;
        node(
            const elemType &x,
            node *p=NULL,
            node *n=NULL
        ){
            data = x; next = n; prev = p;
        }
        node(): next(NULL), prev(NULL){}
        ~node();
    };


    node *head, *tail;                 
    int currentLength;  
    node *move(int i) const;
public:
    dLinkList();
    ~dLinkList(){
        clear();
        delete head;
        delete tail;
    }
    void clear();
    int length() const { return currentLengh; }
    void remove(int i);
    int search(const elemType &x) const;
    elemType visit(int i) const;
    void traverse() const;
}




template <class elemType>
dLinkList<elemTyoe>::dLinkList() {
    head = new node;
    head->next = tail = new node;
    tail0->prev = head;
    currentLength = 0;
}




// 数据插入
template <class elemType>
void dLinkList<elemType>::insert(int i, const elemType &x) {
    node *pos, *tmp;
    pos = move(i);
    tmp = new node(x, pos->prev, pos);
    pos->prev->next = tmp;
    pos->prev = tmp;
    ++currentLength;
}


// 删除
template <class elemType>
void dLinkList<elemType>::remove(int i) {
    node *pos;
    pos = move(i);
    pos->prev->next = pos->next;
    pos->next->prev = pos->prev;
    delete pos;
    --currentLength;
}
