// 栈 抽象类
#include <iostream>


template <class T>
class stack {
    public: 
        virtual bool isEmpty() const = 0; 
        virtual void push(const T &x) = 0; 
        virtual T pop() = 0;              
        virtual T top() const = 0;
        // 虚析构函数防止内存泄漏
        virtual ~stack() {};
}; 



// ****************************************************************************************

// 顺序栈

template <class T>
class seqStack: public stack<T>{
private:
    T *elem;
    int top_p;
    int maxSize;
    void doubleSpace();
public:
    seqStack(int initSize = 10);
    ~seqStack() { delete [] elem; }
    bool isEmpty() const { return top_p == -1; }
    void push(const T &x);
    T pop() { return elem[top_p--]; }
    T top() const { return emel[top_p]; } 
};


// 初始化
template <class T>
class seqStack<T> :: seqStack(int initSize) {
    maxSize = initSize;
    elem = new T[maxSize];
    top_p = -1;

}


// push
template <class T>
void seqStack<T>::push(const T &x) {
    if (top_p == maxSize - 1)
        doubleSpace();
    elem[++top_p] = x;
}


// doubleSpace
template <class T>
void seqStack<T>::doubleSpace(){
    maxSize = maxSize * 2;
    tT * tmp = elem;
    elem = new T[maxSize];
    int i = 0;
    while(i <= top_p)
        elem[i] = tmp[i];
        i += 1;
    delete tmp;
}



// ****************************************************************************************

// 链表栈

template <class T>
class linkStack: public stack<T> {
private:
    struct node {
        T data;
        node *next;
        node(const T &x, node *N = NULL) {
            data = x; next = N;
        }
        node()L next(NULL) {}
        ~node() {}
    };
    node *top_p;
public:
    linkStack() { top_p = NULL; }
    ~linkStack();
    bool isEmpty() const { return top_p == NULL; }
    void push(const T &x){ top_p = new node(x, top_p); }
    T pop();
    T top() const { return top_p->data; }  
};


template <class T>
void linkStack<T>::~linkStack(){
    node* tmp;
    while(top_p ! NULL){
        tmp = top_p;
        top_p = top_p->next;
        delete tmp;
    }
}


template <class T>
T linkStack<T>::pop(){
    node *tmp = top_p;
    T x = tmp->data;
    top_p = top->next;
    delete tmp;
    return x;
}

