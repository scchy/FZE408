#include <iostream>
#include <queue> 


using namespace std;


bool putBuffer(queue<int> *buffer, int size, int in);
void checkBuffer(queue<int> *buffer, int size, int &last);
void arrange(int in[], int n, int k);




int main(){
    int k = 3;
    int n = 9;
    int in[9] = {3, 6, 9, 2, 4, 7, 1, 8, 5};
    cout << "============== Start ==============" << endl;
    arrange(in, n, k);
    return 0;
}


bool putBuffer(queue<int> *buffer, int size, int in){
    int avail = -1, max = 0;
    // 插入到最大的后面
    for(int j = 0; j < size; j++){
        if (buffer[j].empty()) { if (avail == -1) avail = j; }  
        else if(buffer[j].back() < in && buffer[j].back() > max){
            avail = j;
            max = buffer[j].back();
        }
    }


    if(avail != -1){
        buffer[avail].push(in);
        cout << in << "移入缓冲区 " << avail << endl;
        return true;
    }
    else {
        cout << "无可行的方案" << endl;
        return false;
    }
}


void checkBuffer(queue<int> *buffer, int size, int &last){
    bool flag = true;
    while(flag){
        flag = false;
        for(int j=0; j < size; j++){
            if(!buffer[j].empty() && buffer[j].front() == last + 1){
                cout << "将" << buffer[j].front() << "从缓冲区" << j << "移到出轨" << endl;
                buffer[j].pop();
                ++last;
                flag = true;
                break;
            }
        }
    }
}




void arrange(int in[], int n, int k){
    queue<int> *buffer = new queue<int>[k];
    for(int i=0; i< k; i++){
        cout << "queue " << i << " Empty = " << buffer[0].empty() << endl;
    }
    
    int last = 0;
    for(int i = 0; i < n; i++){
            if ( ! putBuffer(buffer, k, in[i]) ) return;          
            checkBuffer(buffer, k, last);
    }
}
