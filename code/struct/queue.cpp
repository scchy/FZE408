
#include <iostream>


template <class elemType>
class queue{
    public: 
        virtual bool isEmpty() = 0;                  //判队空
        virtual void enQueue(const elemType &x) = 0; //进队
        virtual elemType  deQueue() = 0;             //出队
        virtual elemType getHead() = 0;              //读队头元素
        virtual ~queue() {}                          //虚析构函数
};


// ***********************************************************************
// 循环队列
template <class elemType>
class seqQueue: public queue<elemType> {
    private:
        elemType *elem;
        int maxSize;
        // 队头和队尾
        int front, rear;
        void doubleSpace();
    public:
        seqQueue(int size = 10)；
        // 析构函数：收回动态数组
        ~seqQueue() { delete [] elem ; }
        // 判队列是否为空：队头是否等于队尾
        bool isEmpty() { return front == rear; }
        void enQueue(const elemType &x);
        elemType deQueue();
        // 访问队头元素
        elemType getHead() { return elem[(front + 1) % maxSize]; }
};


template <class elemType>
seqQueue<elemType>::seqQueue(int size) { 
    elem = new elemType[size];
    maxSize = size; 
    front = rear = 0;
} 

// 出队
template <class elemType>
elemType seqQueue<elemType>::deQueue() {
    front = (front + 1) % maxSize;
    return elem[front];
}

// 入队
template <class elemType>
void seqQueue<elemType>::enQueue(const elemType &x) { 
    if ((rear + 1) % maxSize == front)
        doubleSpace();
    rear = (rear + 1) % maxSize;
    elem[rear] = x;
}

// doubleSpace
template <class elemType>
void seqQueue<elemType>::doubleSpace() {  
    elemType *tmp =elem;

    elem = new elemType[2 * maxSize];
    for (int i = 1; i < maxSize; ++i)
        elem[i] = tmp[(front + i) % maxSize];
    front = 0; 
    rear = maxSize - 1;
    maxSize *= 2;
    delete  [] tmp;
} 

// ***********************************************************************
// 链队列
template <class eleT>
class linkQueue: public queue<eleT> {
    private:
        struct node {
            eleT  data;
            node *next;
            node(const eleT &x, node *N = NULL){data = x; next = N;}
            node():next(NULL) {}
            ~node() {}
        };
        node *front, *rear; 
    public:
        linkQueue() { front = rear = NULL; }
        // 析构函数，和链表的析构函数类似
        ~linkQueue();      
        bool isEmpty() { return front ==  NULL; }
        void enQueue(const eleT &x);
        eleT deQueue();	  
        eleT getHead() { return front->data; }  
};  

// enQueue函数 尾插入
template <class eleT>
void linkQueue<eleT>::enQueue(const eleT &x){
    if(rear == NULL){
        front = rear = new node(x);
    }
    else {
        rear = rear->next = new node(x);
    }
}

// deQueue 头输出
template <class eleT>
void linkQueue<eleT>::deQueue(){
    node *tmp = front;
    eleT value = front->data;
    // 删除
    front = front->next;
    delete tmp;
    // 判断是否为空
    if(front == NULL) rear = NULL;
    return value;
}