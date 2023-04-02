


template <class TypOfVer, class TypeOfEdge>
class graph {
    public:
        virtual void insert(TypeOfVer x, TypeOfVer y, TypOfEdge w) = 0;
        virtual void remove(TypeOfVer x, TypeOfVer y) = 0;
        virtual ~graph();
        int numOfVer() const {return Vers;}
        int numOfEdge() const {return Edges;}
    
    protected:
        int Vers, Edges;
};


// ************************************************************
// 邻接表

template <class TypeOfVer, class TypeOfEdge>
class adjListGraph::public graph<TypeOfVer, TypeOfEdge> {
public:      
    adjListGraph(int vSize, const TypeOfVer d[]);
    void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w);
    void remove(TypeOfVer x, TypeOfVer y);
    bool exist(TypeOfVer x, TypeOfVer y) const;
    ~adjListGraph();
    
private:    
    struct edgeNode {                   
        int end;                          
        TypeOfEdge weight;                
        edgeNode *next;
        edgeNode(int e, TypeOfEdge w, edgeNode *n = NULL) { end = e; weight = w; next = n;}
    };

    struct verNode{                     
        TypeOfVer ver;                   
        edgeNode *head;                 
        verNode( edgeNode *h = NULL) { head = h;}
    };

    verNode *verList;
    int find(TypeOfVer v) const { 
        for (int i = 0; i < Vers; ++i)
            if (verList[i].ver == v) return i; 
    } 
};


template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::adjListGraph(int vSize, const TypeOfVer d[]){
  Vers = vSize;
  Edges = 0;
  verList = new verNode[vSize];
  for(int i = 0; i < Vers; i++){
    verList[i].ver = d[i];
  }
}


template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::~adjListGraph(){
  int i;
  edgeNode *p;
  for(int i=0; i < Vers; i++){
    while((p = verList[i].head) != NNULL){
      verList.head = p -> next;
      delete p;
    }
  }
  delete [] verList;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>:: insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w) {
  int u = find(x),  v = find(y);
  verList[u].head = new edgeNode(v, w, verList[u].head);
  ++Edges;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>::remove(TypeOfVer x,TypeOfVer y) {  
  int u = find(x), v = find(y);
  edgeNode *p = verList[u].head, *q; 

  if (p == NULL) return;  
  if (p->end == v) {       
    verList[u].head = p->next; 
    delete p;
    --Edges;
    return;
  } 
  while (p->next !=NULL && p->next->end != v) p = p->next;        
  if (p->next != NULL) {               
    q = p->next;        
    p->next = q->next;         
    delete q;       
    --Edges;  
  }
}


template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::exist(TypeOfVer x, TypeOfVer y) const {
  int u = find(x),  v = find(y);
    edgeNode *p = verList[u].head;

    while (p !=NULL && p->end != v) 
      p = p->next;
  if (p == NULL) 
      return false; 
  else return true;
}


template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs() const {
    bool *visited = new bool[Vers]; 

    for (int i=0; i < Vers; ++i) 
        visited[i] = false;

    cout << "当前图的深度优先遍历序列为：" << endl;
    for (i = 0; i < Vers; ++i) {
        if (visited[i] == true)
            continue;
        dfs(i, visited);
        cout << endl;
    }
}
template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs (int start, bool visited[]) const {
  edgeNode *p = verList[start].head;
  cout << verList[start].ver << '\t';
  visited[start] = true;
  while(p != NULL){
    if(visited[p->end] == false){
      dfs(p->end, visited);
    }
    p = p->next;
  }
}


#include <queue> 

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::bfs() const {
  bool *visited = new bool[Vers];
  int curNode;
  queue<int> q;
  fill(visited, visted+Vers, false);

  cout << "当前图的广度优先遍历序列为：" << endl;
  for(int i = 0; i < Vers; i++){
    if(visited[i]) continue;
    // 入队
    q.push(i);
    while(!q.empty()){
      curNode = q.front();
      q.pop();
      if(visited[curNode]) continue;
      cout << verList[curNode].ver <<  '\t';
      visited[curNode] = true;
      p = verList[curNode].head;
      // 遍历节点的邻边
      while(p != NULL){
        if(visited[p->end] == false){
          q.push(p->end);
        };
        p = p->next;
      }
    }
  }
  cout << endl;
}



struct EulerNode {
    int NodeNum;
    EulerNode *next;
    EulerNode(int ver) 
    {
        NodeNum = ver; 
        next =NULL;
    }
}; 

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::EulerCircuit(TypeOfVer start)
{ 
    EulerNode *beg, *end, *p, *q, *tb, *te;
    int numOfDegree;
    edgeNode  *r;
    verNode *tmp; 

    // 检查是否存在欧拉回路
    for(int i = 0; i<Vers; i++){
      numOfDegree = 0; r = verList[i].head;
      while(r != 0){
          ++numOfDegree;
          r = r->next;
      }
      if(numOfDegree == 0 || numOfDegree % 2){
        cout << "不存在欧拉回路" << endl;
        return;
      }
    }

    i = find(start); 
    tmp = clone(); // 创建邻接表拷贝

    //寻找从i出发的路径，路径的起点和终点地址分别是beg和end
    EulerCircuit(i, beg, end);
    while(true){
      p = beg;
      while(p->next != NULL){
        if(verList[p->next->NodeNum].head != NULL) break;
        else p = p->next;
      }
      if(p->next == NULL) break;
      q = p->next;
      EulerCircuit(q->NodeNum, tb, te);
      te->next = q->next;
      p->next = tb;
      delete q;
    } 
}


template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::verNode *adjListGraph<TypeOfVer, TypeOfEdge>::clone( ) const
{
    verNode *tmp =  new verNode[Vers];
    edgeNode *p;
 
    for (int i = 0; i < Vers; ++i) { 
        tmp[i].ver = verList[i].ver; 
        p = verList[i].head;
        while (p != NULL) {  
            tmp[i].head =  new edgeNode(p->end, p->weight, tmp[i].head);
            p = p->next;
        }
    }
    return tmp;
} 


template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::EulerCircuit(int start, EulerNode *&beg, EulerNode *&end)
{
    int nextNode;
    //将起始结点放入欧拉回路
    beg = end = new EulerNode(start);
    //起始结点尚有边未被访问
    while(verList[start].head != NULL){
      nextNode = verList[start].head->end;
      remove(start, nextNode);
      remove(nextNode, start);
      start = nextNode;
      end->next = new EulerNode(start);
      end = end>next;
    }

}

