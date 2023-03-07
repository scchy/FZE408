
from ortools.graph import pywrapgraph


def ortoolsMCMF(from_list, to_list, caps, costs, start_node_idx, end_node_idx):
    # 1- 初始化最大流优化器
    max_flow = pywrapgraph.SimpleMaxFlow()
    # 2- 最大流-图构建
    for i in range(len(from_list)):
        _ = max_flow.AddArcWithCapacity(
            from_list[i], to_list[i], caps[i]
        )
    # 3- 最大流-求解
    if max_flow.Solve(start_node_idx, end_node_idx) == max_flow.OPTIMAL:
        max_flow_res = max_flow.OptimalFlow()
        print('Max flow:', max_flow_res)
    else:
        return None
    
    # 4- 初始化最小费用优化器
    min_cost = pywrapgraph.SimpleMinCostFlow()
    # 5- 最小费用图构建
    for i in range(len(fList)):
        _ = min_cost.AddArcWithCapacityAndUnitCost(
            from_list[i], to_list[i], caps[i], costs[i]
        )

    supplies = [0] * len(from_list)
    supplies[start_node_idx] = max_flow_res
    supplies[end_node_idx] = -max_flow_res
    for i in range(len(supplies)):
        _ = min_cost.SetNodeSupply(i, supplies[i])
    
    res_path = []
    # 6- 求解
    if min_cost.Solve() == min_cost.OPTIMAL:
        min_cost_res = min_cost.OptimalCost()
        print('Minimum cost:', min_cost_res)
        print('')
        print('  Arc    Flow / Capacity  Cost')
        for i in range(min_cost.NumArcs()):
            cost = min_cost.Flow(i) * min_cost.UnitCost(i)
            if min_cost.Flow(i) > 0 and cost > 0:
                res_path.append("%s->%s" % (min_cost.Tail(i), min_cost.Head(i)) )
            print('%1s -> %1s   %3s  / %3s       %3s' % (
                min_cost.Tail(i),
                min_cost.Head(i),
                min_cost.Flow(i),
                min_cost.Capacity(i),
                cost))
    else:
        return
    
    return {"flowPath": res_path, 'maxFlow': max_flow_res, "minCost": min_cost_res}


fList = [0, 0, 1, 1, 1, 2, 2, 3, 4]
toList = [1, 2, 2, 3, 4, 3, 4, 4, 2]
cost = [4, 4,  2, 2,  6,  1, 3,  2, 3]
cap = [15, 8, 20, 4, 10, 15, 4, 20, 5]
ortoolsMCMF(fList, toList, cap, cost, 0, 4)
