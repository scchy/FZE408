template <class Type>
class priorityQueue:public queue<Type> {
    private:
        // 队列长度
        int currentSize;  
        // 指向数组起始地址的指针
        Type *array; 
        // 数组大小
        int maxSize;
        void doubleSpace();
        void buildHeap();
        void percolateDown(int hole);  
    public:
        priorityQueue(int capacity = 100);
        priorityQueue(const Type data[], int size);
        ~priorityQueue() { delete [] array; }
        bool isEmpty() const { return currentSize == 0; }
        void enQueue(const Type & x);
        Type deQueue();
        Type getHead() { return array[1]; }
};

// 构造函数 - 构造空的优先级队列
priorityQueue(int capacity = 100) { 
    array = new Type[capacity];
    maxSize = capacity;   
    currentSize = 0;
}


template <class Type>
void priorityQueue<Type>::enQueue( const Type & x ) {
    if(currentSize == maxSize - 1) 
        doubleSpace();

    int hole = ++currentSize;
    for(; hole > 1 && x < array[hole / 2]; hole /= 2)
        array[hole] = array[hole / 2];
    array[hole] = x;
} 


template <class Type>
Type priorityQueue<Type>::deQueue() { 
    Type minItem;
    minItem = array[1];
    array[1] = array[currentSize--];
    // 从1号下标开始向下过滤
    percolateDown(1);
    return minItem;
} 

template <class Type>
void priorityQueue<Type>::percolateDown(int hole) { 
    int child;
    Type tmp = array[hole];

    for(; hole * 2 <= currentSize; hole = child) { 
        child = hole * 2;
        if (child != currentSize && array[child + 1] < array[child])
            child++;
        if( array[child] < tmp )   
            array[hole] = array[child];
        else break;
    }
    array[hole] = tmp;
}