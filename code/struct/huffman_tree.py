
import heapq 
from collections  import deque


class Node: 
    def __init__(self, idx, freq, char, left, right):
        self.idx = idx
        self.freq = freq
        self.char = char
        self.left = left
        self.right = right
        self.code = []
        self.path = []
        
    def __lt__(self, other): 
        return self.freq < other.freq 
    
    def __str__(self):
        return f'Node([{self.idx}]({self.char}/{self.freq}), left={self.left}, right={self.right})'
    
    def __repr__(self):
        return str(self)




def build_huffman_tree(data=None, freq_map=None): 
    if freq_map is None:
        freq_map = dict() 
        for char in data: 
            freq_map[char] = freq_map.get(char, 0) + 1 
    print(freq_map)
    word_map = [Node(idx, freq, char, None, None) for idx, (char, freq) in enumerate(freq_map.items())] 
    min_node = min(word_map)
    print(min_node)
    print('len(word_map)=', len(word_map))
    # 初始化 因为heappop 会先输出第一个元素
    node_heap = [min_node] + [i for i in word_map if i.char != min_node.char] 
    # 构建哈夫曼树
    while len(node_heap) > 1: 
        # 优先队列， 弹出最小的2个
        left_node = heapq.heappop(node_heap) 
        right_node = heapq.heappop(node_heap) 
        freq_sum = left_node.freq + right_node.freq 
        idx = len(word_map)
        # 左大右小
        combined_node = Node(idx, freq_sum, None, right_node, left_node) 
        heapq.heappush(node_heap, combined_node) 
        word_map.append(combined_node)
    # 哈夫曼树最后
    print('len(word_map)=', len(word_map))
    h_tree = complete_code_path(node_heap[0])
    return h_tree, word_map




def complete_code_path(h_tree):
    help_list = deque()
    h_tree.path = [h_tree.idx]
    h_tree.code = [-1]
    help_list.append(h_tree)
    while len(help_list):
        n = help_list.popleft()
        while n.left:
            l = n.left
            r = n.right
            l.code = n.code + [1]
            r.code = n.code + [0]
            l.path = n.path + [l.idx]
            r.path = n.path + [r.idx]
            help_list.append(r)
            n = l
    return h_tree


if __name__ == '__main__':
    test_dict = {
        'a': 6, 'b': 3,
        'c': 4, 'd': 2
    }
    h_tree, total_word_map = build_huffman_tree(freq_map=test_dict) 
    for i in total_word_map:
        print('--'*25)
        print(i)
        print('code=', i.code)
        print('path=', i.path)
