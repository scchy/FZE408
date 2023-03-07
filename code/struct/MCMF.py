# python3
# Create Date: 2023-03-07
# Author: Scc_hy
# Func: 最小费用最大流
# ====================================================================================================

from collections import defaultdict, deque
from typing import List, Union, Any, AnyStr, Dict
import math
from rich.console import Console
cs = Console()

class MCMF:
    # 边
    class Edge:
        def __init__(self, f: int, to: int, cap: int, cost: Union[int, float], antiIndex: int, tp: AnyStr ='forward'):
            self.f = f
            self.to = to
            self.cap = cap
            self.cost = cost
            self.antiIndex = antiIndex
            self.tp = tp
            self.cap_org = cap
        
        def __str__(self):
            if self.tp  == 'forward':
                return f'F({self.f} -> {self.to})[{self.cap}/{self.cost}]'
            return f'R({self.f} <- {self.to})[{self.cap}/{self.cost}]'

        def __repr__(self):
            return str(self)

    # 结点
    class GVector:
        def __init__(self, name: Any, idx: int=-1 ,tp: AnyStr ='normal', vInfo: Any = None):
            self.name = name
            self.tp = tp
            self.idx = idx
            self.vInfo = vInfo
        
        def __str__(self):
            return f'{self.tp}({self.name}-idx:{self.idx})'
        
        def __repr__(self):
            return str(self)
        
        def __eq__(self, __o):
            return self.name == __o.name
        
    # 结点list
    v_list: List[GVector] = []
    num_nodes = 0
    
    # 图-邻接表
    graph:Dict[int, List[Edge]] = defaultdict(list)
    
    def __init__(self, head: List[Any], tail: List[Any], caps: List[int], costs: List[Union[int, float]], start: Any, end: Any):
        st_idx, ed_idx = self.complete_graph(head, tail, caps, costs, start, end)
        self.st_idx = st_idx
        self.ed_idx = ed_idx
        self.pre_vector = [-1] * self.num_nodes
        self.pre_vector_edge = [-1] * self.num_nodes

    
    def complete_graph(self, head: List[Any], tail: List[Any], caps: List[int], costs: List[Union[int, float]], start: Any, end: Any) -> List[int]:
        len_ = len(head)
        
        for idx in range(len_):
            # 结点list 中插入唯
            head_idx = len(self.v_list)
            if self.GVector(head[idx]) not in self.v_list:
                self.num_nodes += 1
                self.v_list.append(self.GVector(name=head[idx], idx=head_idx))
            
            head_idx = self.v_list.index(self.GVector(head[idx]))
            tail_idx = len(self.v_list)
            if self.GVector(tail[idx]) not in self.v_list:
                self.num_nodes += 1
                self.v_list.append(self.GVector(name=tail[idx], idx=tail_idx))
                
            tail_idx = self.v_list.index(self.GVector(tail[idx]))
            # 在图中 插入边， 生成邻接表
            # 正向边
            head_anti_idx = len(self.graph[tail_idx])
            tail_anti_idx = len(self.graph[head_idx])
            self.graph[head_idx].append(
                self.Edge(head[idx], tail[idx], caps[idx], costs[idx], antiIndex=head_anti_idx)
            )
            # 反向边
            self.graph[tail_idx].append(
                self.Edge(tail[idx], head[idx], 0, -costs[idx], antiIndex=tail_anti_idx, tp='reverse')
            )
        
        print('--'*25)
        cs.print(self.v_list)
        print('--'*25)
        cs.print(self.graph)
        return [self.v_list.index(self.GVector(start)), self.v_list.index(self.GVector(end))] 


    def spfa(self) -> bool:
        st = self.st_idx
        ed = self.ed_idx
        # 记录起点到当前节点路径的累积cost
        cost_list = [math.inf] * self.num_nodes
        # 记录节点是否访问
        visted_list = [False] * self.num_nodes
        # 刷新辅助记录栈
        self.pre_vector = [-1] * self.num_nodes
        self.pre_vector_edge = [-1] * self.num_nodes
        # 辅助queue, 进行fbs
        queue = deque()
        queue.append(st)
        cost_list[st] = 0
        visted_list[st] = True
        while len(queue):
            now = queue.popleft()
            visted_list[now] = False
            for e_idx, edge_i in enumerate(self.graph[now]):
                f = edge_i.f
                t = edge_i.to
                cst = edge_i.cost
                cap = edge_i.cap
                if cap > 0 and  cost_list[t] > cost_list[now] + cst:
                    cost_list[t] = cost_list[now] + cst
                    self.pre_vector[t] = now
                    self.pre_vector_edge[t] = e_idx
                    if ~visted_list[t]:
                        visted_list[t] = True
                        queue.append(t)
    
        return cost_list[ed] < math.inf

    def solve(self):
        out = {
            'flowPath': [],
            'maxFlow': 0,
            'minCost': 0
        }
        
        while self.spfa():
            tmp = self.ed_idx
            min_flow = math.inf
            # 寻找路径流量
            while tmp != self.st_idx:
                # 反向轨迹
                pre_v = self.pre_vector[tmp]
                pre_v_e = self.pre_vector_edge[tmp]
                min_flow = min(min_flow, self.graph[pre_v][pre_v_e].cap)
                tmp = pre_v
            
            tmp = self.ed_idx
            path_min_cost = 0 
            # 更新图
            while tmp != self.st_idx:
                # 反向轨迹
                pre_v = self.pre_vector[tmp]
                pre_v_e = self.pre_vector_edge[tmp]
                # 正向边
                self.graph[pre_v][pre_v_e].cap -= min_flow
                # 反向边
                now_v_e = self.graph[pre_v][pre_v_e].antiIndex
                self.graph[tmp][now_v_e].cap += min_flow
                # 路径的cost
                path_min_cost += self.graph[pre_v][pre_v_e].cost
                tmp = pre_v
                

            out['maxFlow'] += min_flow
            out['minCost'] += path_min_cost * min_flow

        out['flowPath'] = self.find_path()
        return out

    def find_path(self):
        """
        找出最终有cost且有流量的边
        """
        out = []
        for v, e_list in self.graph.items():
            for e in e_list:
                if e.cost > 0 and e.cap != e.cap_org:
                    out.append(f'{e.f}->{e.to}')
        return out


if __name__ == '__main__':
    fList = [0, 0, 1, 1, 1, 2, 2, 3, 4]
    toList = [1, 2, 2, 3, 4, 3, 4, 4, 2]
    cost = [4, 4,  2, 2,  6,  1, 3,  2, 3]
    cap = [15, 8, 20, 4, 10, 15, 4, 20, 5]
    mcmf_opt = MCMF(fList, toList, cap, cost, 0, 4)
    out = mcmf_opt.solve()
    cs.print(out)

