# TODO 速记
'''
def unzip_string(records):
    curr,temp,stack = '','',[]
    for i,char in enumerate(records):
        if char == '(':
            stack.append(curr)
            curr =''
        elif char == ')':
            repeat_num = records[i+2]
            curr = stack.pop() + curr*int(repeat_num)
        elif char == '<' or char == '>' or char.isdigit():
            continue
        else:
            curr += char
    return curr

print(unzip_string('a(b(cd)<3>e)<2>f'))
'''

# def isValid(s): 
#     parentheses_table = {'(':')','[':']','{':'}'}
#     temp_stack = []

#     if len(s) % 2 == 1 or len(s) == 0:
#         return False
#     for char in s:
#         if char in parentheses_table.keys():
#             temp_stack.append(char)
#         else:
#             if not temp_stack:
#                 return False
#             if parentheses_table[temp_stack.pop()] != char:
#                 return False

#     return bool(temp_stack == [])

# print(isValid("(]"))

# from typing import List
# from collections import defaultdict
# class Solution:
#     def singleNumber(self, nums: List[int]) -> int:
#         hash_table = defaultdict(int)
#         for i in nums:
#             hash_table[i] += 1
        
#         for i in hash_table:
#             if hash_table[i] == 1:
#                 return i

# s =Solution()
# print(s.singleNumber([4,1,2,1,2]))


# -*- coding: utf-8 -*-
# import hashlib, random

# def get_md5(s):
#     return hashlib.md5(s.encode('utf-8')).hexdigest()

# class User(object):
#     def __init__(self, username, password):
#         self.username = username
#         self.salt = ''.join([chr(random.randint(48, 122)) for i in range(20)])
#         self.password = get_md5(password + self.salt)

# db = {
#     'michael': User('michael', '123456'),
#     'bob': User('bob', 'abc999'),
#     'alice': User('alice', 'alice2008')
# }

# def login(username, password):
#     user = db[username]
#     return user.password == get_md5(password+user.salt)

# # 测试:
# assert login('michael', '123456')
# assert login('bob', 'abc999')
# assert login('alice', 'alice2008')
# assert not login('michael', '1234567')
# assert not login('bob', '123456')
# assert not login('alice', 'Alice2008')
# print('ok')

# import os, sqlite3

# db_file = os.path.join(os.path.dirname(__file__), 'test.db')
# if os.path.isfile(db_file):
#     os.remove(db_file)

# # 初始数据:
# conn = sqlite3.connect(db_file)
# cursor = conn.cursor()
# cursor.execute('create table user(id varchar(20) primary key, name varchar(20), score int)')
# cursor.execute(r"insert into user values ('A-001', 'Adam', 95)")
# cursor.execute(r"insert into user values ('A-002', 'Bart', 62)")
# cursor.execute(r"insert into user values ('A-003', 'Lisa', 78)")
# cursor.close()
# conn.commit()
# conn.close()

# def get_score_in(low, high):
#     ' 返回指定分数区间的名字，按分数从低到高排序 '
#     conn = sqlite3.connect(db_file)
#     cursor = conn.cursor()
#     cursor.execute('select * from user where score between ? and ?', (low,high))
#     values = cursor.fetchall()
#     ret = []
#     for info in values:
#         ret.append(info[1])
#     return ret

# print(get_score_in(60, 95))

# # 测试:
# assert get_score_in(80, 95) == ['Adam'], get_score_in(80, 95)
# assert get_score_in(60, 80) == ['Bart', 'Lisa'], get_score_in(60, 80)
# assert get_score_in(60, 100) == ['Bart', 'Lisa', 'Adam'], get_score_in(60, 100)

# print('Pass')

# from selenium import webdriver
# browser = webdriver.Firefox()
# browser.get('https://www.baidu.com')


# import collections
# Card = collections.namedtuple('Card', ['rank', 'suit'])

# class FrenchDeck:
#     ranks = [str(n) for n in range(2, 11)] + list('JQKA')
#     suits = 'spades diamonds clubs hearts'.split()

#     def __init__(self):
#         self._cards = [Card(rank, suit) for suit in self.suits for rank in self.ranks]

#     def __len__(self):
#         return len(self._cards)

#     def __getitem__(self, position):
#         return self._cards[position]

# f = FrenchDeck()
# print(len(f))
# print(f[1])

import re
# # 将匹配的数字乘以 2
# def double(matched):
#     value = int(matched.group())
#     print(value)
#     return str(value * 2)
# s = 'A23G4HFD567'
# res = re.sub(r'(\d+)', double, s)
# print(res)


# def dashrepl(matchobj):
#     if matchobj.group(0) == '-': 
#         return ' '
#     else: 
#         return '-'
# print(re.sub('-{3,4}', dashrepl, 'pro----gram-files'))

# s = re.match(r'^\d{3}-\d{3,8}', '010-12345qwe')
# print(s.group(0))


# def pemute(n,my_list,cur):
#     if cur == n:
#         print(my_list[0:n])
    
#     for i in range(1,n+1):
#         ok = True
#         for j in range(cur):
#             if my_list[j] == i:
#                 ok = False
#         if ok:
#             my_list[cur] = i
#             pemute(n,my_list,cur+1)

# list1 = [0]*10
# pemute(3,list1,0)


class Node:
    def __init__(self,key,value,prev=None,Next=None):
        self.key = key
        self.value = value
        self.prev = prev
        self.next = next
    
    def __repr__(self):
        return self.value


class LinkedList:
    def __init__(self):
        self.head = Node(None,'Head')
        self.tail = Node(None,'Tail')
        self.head.next =self.tail
        self.tail.prev = self.head
    
    # 添加至tail前
    def append(self,node):
        node.prev = self.tail.prev
        node.next = self.tail
        node.prev.next = node
        self.tail.prev = node

    def delete(self,node):
        node.prev.next = node.next
        node.next.prev = node.prev

    
    def get_head(self):
        return self.head.next

class LRU:
    def __init__(self,capity=100):
        self.capity =capity
        self.map = {}
        self.linked_list = LinkedList()

    def get(self,key):
        if key not in self.map:
            return None
        self.linked_list.delete(self.map[key])
        self.linked_list.append(self.map[key])
        return self.map[key]

    def put(self,key,value):
        # key已在map中则删除已存在的value并更新，添加到最后
        if key in self.map:
            self.linked_list.delete(self.map[key])
            self.linked_list.append(Node(key,value))
            return
        if len(self.map) >= self.capity:
            first_node = self.linked_list.get_head()
            self.linked_list.delete(first_node)
            del self.map[first_node.key]
        
        new_node = Node(key,value)
        self.linked_list.append(new_node)
        self.map[key] = new_node


# lru = LRU(4)
# lru.put('zhangsan','he likes food')
# lru.put('lisi','he likes mobile')
# lru.put('wangwu','he likes game')
# lru.get('lisi')
# lru.put('zhaoliu','he likes basketball')
# lru.put('huangqi','he likes football')
# lru.put('wangwu','he also likes shopping')


# from collections import OrderedDict
# class LRU2(OrderedDict):
#     def __init__(self,cap=128,/,*args,**kwds):
#         self.cap = cap
#         super().__init__(*args,**kwds)
    
#     def __setitem__(self,key):
#         value = super().__getitem__(key)
#         self.move_to_end(key,last=True)
#         return value

#     def __getitem__(self,key,value):
#         super().__setitem__(key,value)
#         if len(self) > self.cap
#             oldest = next(iter(self))
#             del self[oldest]



# import logging
# import sys
# import os


# logger = logging.getLogger('lance')
# logger.setLevel(logging.DEBUG)
# fmt = logging.Formatter('[%(asctime)s] [%(levelname)s] %(message)s','%Y-%m-%D %H:%M:%S')



class Bunch(dict):
    def __init__(self, kwargs=None):
        if kwargs is None:
            kwargs = {}
        for key, value in kwargs.items():
            kwargs[key] = self.bunchify(value)
        super(Bunch, self).__init__(kwargs)
        self.__dict__ = self

    @classmethod
    def bunchify(cls, obj):
        print(obj)
        if isinstance(obj, (list, tuple)):
            return [cls.bunchify(item) for item in obj]
        if isinstance(obj, dict):
            return cls(obj)
        return obj

# data = Bunch.bunchify(str)
# data['status_code'] = '200'

# print(data)

# class AttrDict(dict):
#     def __init__(self, *args, **kwargs):
#         super(AttrDict, self).__init__(*args, **kwargs)
#         self.__dict__ = self

#     @staticmethod
#     def fromDict(d):
#         return AttrDict.recursion(d)

#     @staticmethod
#     def recursion(x):
#         if isinstance(x, dict):
#             return AttrDict((k, bunchify(v)) for k, v in x.items())
#         else:
#             return x



# N = [1]
# for i in range(10):
#     print(N)
#     N.append(0)
#     tmp = []
#     for j in range(i + 2):
#         tmp.append(N[j - 1] + N[j])
#     N = tmp

# from urlparse import urljoin
# print(urljoin('https://170.34.5.120/redfish/v1/', '/redfish/v1/Systems'))

# import logging
# import sys
# import os
# # 初始化logger
# logger = logging.getLogger("yyx")
# logger.setLevel(logging.DEBUG)
# # 设置日志格式
# fmt = logging.Formatter('[%(asctime)s] [%(levelname)s] %(message)s', '%Y-%m-%d %H:%M:%S')
# # 添加cmd handler
# cmd_handler = logging.StreamHandler(sys.stdout)
# cmd_handler.setLevel(logging.DEBUG)
# cmd_handler.setFormatter(fmt)
# # 添加文件的handler
# logpath = os.path.join(os.getcwd(), 'debug.log')
# file_handler = logging.FileHandler(logpath)
# file_handler.setLevel(logging.DEBUG)
# file_handler.setFormatter(fmt)
# # 将cmd和file handler添加到logger中
# logger.addHandler(cmd_handler)
# logger.addHandler(file_handler)
# logger.debug("今天天气不错")

# from typing import List
# def get_sum(row:int,col:int,noise:List[List[int]]) ->int:
#     result = 0
#     grid = [[0] * col for i in range(row)]
#     for i in range(row):
#         for j in range(col):
#             for k in range(len(noise)):
#                 max_interval = max(abs(noise[k][0]-i),abs(noise[k][1]-j))
#                 grid[i][j] = max(grid[i][j],max(noise[k][2]-max_interval,0))
#             result += grid[i][j]
#         print(grid[i])
#     print(result)

# def get_sum2(row:int,col:int,noise:List[List[int]]) ->int:
#     result = 0
#     grid = [[0] * col for i in range(row)]

#     def dfs(n,m,value):
#         if n < 0 or n > row-1 or m <0 or m > col-1 or grid[n][m] >= value or value == 0:
#             return 
#         grid[n][m] = value
#         for i in [-1,0,1]:
#             for j in [-1,0,1]:
#                 if i == 0 and j ==0:
#                     continue
#                 dfs(n+i,m+j,value-1) 

#     for k in range(len(noise)):
#         dfs(noise[k][0],noise[k][1],noise[k][2])

#     for i in range(row):
#         for j in range(col):
#             if grid[i][j]:
#                 result += grid[i][j]
#         print(grid[i])
#     print(result)
# # get_sum(6,6,[[3,4,3],[1,1,4]])
# # get_sum2(5,6,[[3,4,3],[1,1,4]])

# import collections
# def get_sum3(n: int, m: int, noise: List[List[int]]) -> int:
#     directions = [[-1, 1], [-1, 0], [-1, -1], [0, -1], [1, -1], [1, 0], [1, 1], [0, 1]]
#     trange = [[0] * m for i in range(n)]

#     def bfs(i, j, value):
#         deque = collections.deque()
#         deque.append((i, j, value))
#         while len(deque) != 0:
#             size = len(deque)
#             while size > 0:
#                 point = deque.pop()
#                 for value in directions:
#                     x_c = point[0] + value[0]
#                     y_c = point[1] + value[1]
#                     value = point[2]
#                     if x_c < 0 or x_c >= n or y_c < 0 or y_c >= m or value <= trange[x_c][y_c]:
#                         continue
#                     if value > trange[x_c][y_c]:
#                         trange[x_c][y_c] = value
#                         if value != 1:
#                             deque.appendleft((x_c, y_c, value - 1))
#                 size = size - 1

#     for value in noise:
#         if value[2] <= trange[value[0]][value[1]]:
#             continue

#         trange[value[0]][value[1]] = value[2]

#         if value[2] != 1:
#             bfs(value[0], value[1], value[2] - 1)

#     res = 0
#     for i in range(n):
#         for j in range(m):
#             res += trange[i][j]
#         print(trange[i])
#     print(res)


def threeSum(nums):
    nums.sort()
    ret = []
    for i in range(len(nums)):
        if nums[i] > 0:
            continue
        if i != 0 and nums[i] == nums[i-1]:
            continue
        two_sum = 0 - nums[i]
        map = {}
        tmp_set =()
        for j in range(i+1,len(nums)):
            if j > i + 2 and nums[j] == nums[j-1] and nums[j-1] == nums[j-2]:
                continue
            if two_sum - nums[j] in map:
                ret.append([nums[i],two_sum - nums[j],nums[j]])
                map.pop(two_sum - nums[j])
            map[nums[j]] = j
    print((ret))

threeSum([-2,0,0,2,2])

from collections import Counter
def countCharacters(words, chars):
    count = Counter(chars) 
    res = 0
    for w in words:
        In = True
        for c in w:
            if w.count(c) > count[c]:
                # print('%s:%d' %(c,count[c]))
                In = False
                break
        if In:
            res += len(w)
    print(res)

countCharacters(["bt","cat","hat","tree"],"atach")


def partitionLabels(S):
    lindex = {c: i for i, c in enumerate(S)}
    j = anchor = 0
    ans = []
    for i, c in enumerate(S):
        j = max(j, lindex[c])
        if i == j:
            ans.append(j - anchor + 1)
            anchor = j + 1
    print(ans)

partitionLabels('ababcbacadefegdehijhklij')


def generateParenthesis(n):
    def backtrack(s='',left = 0,right = 0):
        if len(s) == 2*n:
            res.append(s)
        if left < n:
            backtrack(s+'(',left+1,right)
        if right < left:
            backtrack(s+')',left,right+1)
    res = []
    backtrack()
    print(res)

generateParenthesis(3)


def generateParenthesis2(n):
    def generate(A):
        if len(A) == 2*n:
            if(valid(A)):
                res.append(''.join(A))
        else:
            A.append('(')
            generate(A)
            A.pop()
            A.append(')')
            generate(A)
            A.pop()
    def valid(A):
        balanced = 0
        for c in A:
            if c=='(':
                balanced += 1
            else:
                balanced -= 1
            # if balanced < 0:
            #     return False    # 如果右括号比左括号多，那么无论再怎么增加左括号也不会合法有效，直接return False
        return balanced == 0

    res = []
    A = []
    generate(A)
    print(res)

generateParenthesis2(2)


from copy import deepcopy
def findSubstring(s, words):
    if not len(s):
        return []

    words_dict =dict(Counter(words))
    step = len(words[0])
    length = sum(map(len,words))
    end = len(s) - length
    index_sub = step * (len(words)-1)
    res = []
    tmp_list = list(s)

    for index,char in enumerate(s):
        if index > end:
            break
        begin = i = index
        words_dict2 = deepcopy(words_dict)
        for i in range(begin,begin+length,step):
            tmp = ''.join(tmp_list[i:i+step])
            if tmp not in words_dict2:
                break
            if words_dict2[tmp] <= 0:
                break
            if i-begin == index_sub:
                res.append(begin)
                break
            words_dict2[tmp] -= 1
    print(res)
            

findSubstring("barfoofoobarthefoobarman",["bar","foo","the"])



# def DFS(sum,last,result):
#     if sum > target:
#         return
#     elif sum == target:
#         print(result)
#         return
#     else:
#         for value in range(last,target):
#             DFS(sum+value,value,result + "+" + str(value))




# def dfs(sum, last,target,res):
#     if sum > target:
#         return
#     elif sum == target:
#         res[0] += 1
#         return
#     else:
#         for value in range(last, target):
#             dfs(sum + value, value,target,res)

# target = 20
# res = 0
# for s in range(1, target + 1):
#     dfs(s, s)
# print(res)

# from copy import deepcopy
# def combinationSum(candidates, target):
    # res = []
    # tmp_list = []
    # def my_combinationSum(candidates,target):
    #     if target == 0:
    #         res.append(deepcopy(tmp_list))
    #         return
    #     if target < 0:
    #         return 
    #     for i in candidates:
    #         tmp_list.append(i)
    #         my_combinationSum(candidates,target-i)
    #         tmp_list.pop()
    
    # my_combinationSum(candidates,target)
    # res2 = list(map(lambda x: sorted(x,key = lambda y: y),res))
    # res3 = (set(tuple(v) for v in res2))
    # print([list(v) for v in res3])

#     candidates.sort()
#     res = []
    
#     def backtrack(acc, start, sum):
#         if sum == target:
#             res.append(list(acc))
#             return
        
#         for i in range(start, len(candidates)):
#             total = candidates[i] + sum
#             if total > target: break
#             acc.append(candidates[i])
#             backtrack(acc, i, total)
#             acc.pop()
#     backtrack([], 0, 0)
#     print(res)

# combinationSum([2,3,6,7],7)

import collections

def findRepeatedDnaSequences(s):
    # res = []
    # if len(s) <= 10 :
    #     return res
    # for i in range(len(s)-10):
    #     tmp = s[i:i+10]
    #     for j in range(i+1,len(s)-9):
    #         if tmp == s[j:j+10] and tmp not in res:
    #             res.append(tmp)
    #             break
    # return list(res)

    # res, mem = set(), set()
    # for i in range(len(s)-9):
    #     cur = s[i:i+10]
    #     if cur in mem:
    #         res.add(cur)
    #     else:
    #         mem.add(cur)
            
    # return list(res)

    sequences = collections.defaultdict(int) 
    for i in range(len(s)-9):
        sequences[s[i:i+10]] += 1
    return [key for key, value in sequences.items() if value > 1]

print(findRepeatedDnaSequences("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"))



import typing
class Solution:
    def permuteUnique(self, nums):
        res = []
        visited = [False] * len(nums)
        nums.sort() #先排序，必须保证相邻的元素在一块

        def combine(path):
            if len(path) == len(nums):
                res.append(path)
                return
            for i in range(len(nums)):
                # 主要是如何判断重复，方法就是对与重复的元素循环时跳过递归的调用只对第一个未被使用的进行递归，
                # 那么这一次的结果将会唯一出现在结果集中，而后重复的元素将会被略过；
                # 如果第一个重复元素还没在当前结果中，那么我们就不需要进行递归
                if visited[i] or (i > 0 and visited[i-1] and nums[i] == nums[i - 1]):
                    continue
                visited[i] = True
                combine(path + [nums[i]])
                visited[i] = False

        combine([])
        return res

res = Solution()
print(res.permuteUnique([1,1,2]))


# from copy import deepcopy
# def permute(str):
#     result =[None] * len(str)
#     visit = [False] * len(str)
#     temp_list = []

#     def dfs(level):
#         if level == len(str) and result not in temp_list:
#             temp_list.append(deepcopy(result))  # 注意深拷贝
#             print(result)
#             return 
#         for i in range(len(str)):
#             if visit[i] == False:
#                 visit[i] = True
#                 result[level] = str[i]
#                 dfs(level+1)
#                 # result[level] = None
#                 visit[i] = False
    
#     dfs(0)
        
# permute(list([1,2,1,2]))


# def permute2(seq):
#     result = []
#     if len(seq) <= 1:                        # Shuffle any sequence: generator
#         return seq                      # Empty sequence
#     else:
#         for i in range(len(seq)):
#             rest = seq[:i] + seq[i+1:] # Delete current node
#             if i > 0 and seq[i] in seq[:i]:
#                 continue
#             for x in permute2(rest):    # Permute the others
#                 result.append(seq[i] + x)  
#     return result

# for value in permute2('1122'):
#     print(value)


# def permute3(seq):
#     if not seq:                        # Shuffle any sequence: generator
#         yield seq                      # Empty sequence
#     else:
#         for i in range(len(seq)):
#             rest = seq[:i] + seq[i+1:] # Delete current node
#             for x in permute3(rest):    # Permute the others
#                 yield seq[i:i+1] + x   # Add node at front

# for value in permute3('xy'):
#     print(value)



# class Solution {
#     public int[] corpFlightBookings(int[][] bookings, int n) {
#         int[] res = new int[n];
#         for(int i = 0; i< bookings.length; i++){
#             for(int j = bookings[i][0] - 1; j < bookings[i][1]; j++){
#                 res[j] += bookings[i][2];
#             }
#         }
#         return res;
#     }
# }


# import json

# def _parse_json(s):
#     ' parse str into JsonDict '

#     def _obj_hook(pairs):
#         ' convert json object to python object '
#         o = JsonDict()
#         for k, v in pairs.items():
#             o[str(k)] = v
#         return o
#     return json.loads(s, object_hook=_obj_hook)


# class JsonDict(dict):
#     ' general json object that allows attributes to be bound to and also behaves like a dict '

#     def __getattr__(self, attr):
#         try:
#             return self[attr]
#         except KeyError:
#             raise AttributeError(r"'JsonDict' object has no attribute '%s'" % attr)

#     def __setattr__(self, attr, value):
#         self[attr] = value

# print(_parse_json('{"a":1,"b":2,"c":3,"d":4,"e":5}'))


# def permute2(seq):
#     result = []
#     if len(seq) <= 1:                        # Shuffle any sequence: generator
#         return seq                      # Empty sequence
#     else:
#         for i in range(len(seq)):
#             rest = seq[:i] + seq[i+1:] # Delete current node
#             if i > 0 and seq[i] in seq[:i]:
#                 continue
#             for x in permute2(rest):    # Permute the others
#                 result.append(seq[i] + x)  
#     return result

# for index,value in enumerate(permute2('abba')):
#     print(f'{index+1}:{value}')



# class Solution:
#     def is_valid_str(self, s: str) ->bool:
#         if s is None:
#             return True
#         if len(s) % 2 == 1:
#             return False

#         stack = []
#         symbol_map = {'(':')','[':']','{':'}'}
#         for alphabet in s:
#             if alphabet in symbol_map.keys():
#                stack.append(alphabet)
#                continue
#             if not stack:
#                 return False

#             tmp = stack.pop()
#             if symbol_map.get(tmp) != alphabet:
#                 return False

#         return len(stack) == 0

# a = Solution()
# print(a.is_valid_str("{[]}"))


# def minMeetingRooms(intervals):
#     if not intervals:
#         return 0
#     tmp = sorted(x for i, j in intervals for x in [[i, 1], [j, -1]])
#     res, n = 0, 0
#     for _, v in tmp:
#         n += v
#         res = max(res, n)
#     return res


class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:   
    def addTwoNumbers(self,l1,l2):
        if l1 is None:
            return l2
        elif l2 is None:
            return l1

        value = l1.val + l2.val
        result = ListNode(value % 10)
        result.next = self.addTwoNumbers(l1.next, l2.next)
        if (value >= 10):
            result.next = self.addTwoNumbers(ListNode(value / 10), result.next)
        return result


def myPrintList(l):
    while(True):
        print(l.val)
        if l.next is not None:
            l = l.next
        else:
            print()
            break


l1_1 = ListNode(8)
l1_2 = ListNode(9)
l1_3 = ListNode(7)
l1_1.next = l1_2
l1_2.next = l1_3

l2_1 = ListNode(9)
l2_2 = ListNode(8)
l2_3 = ListNode(8)
l2_1.next = l2_2
l2_2.next = l2_3

l3 = Solution().addTwoNumbers(l1_1, l2_1)
myPrintList(l3)


# str1 = '6789'
# str2 = '5432'

# def add(str1,str2):
#     str1_list = list(str1.revese())
#     str2_list = list(str2.revese())
#     for s in str1_list:

# add(str1,str2)

def lengthOfLIS(nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    if not nums:
        return 0

    len_nums = len(nums)
    dp = [1]*len_nums
    result = 1
    
    for i in range(1, len_nums):
        for j in range(i):
            if nums[j] < nums[i]:
                dp[i] = max(dp[i], 1 + dp[j])
        result = max(result, dp[i])
    return result


print(lengthOfLIS([1, 7, 3, 5, 9, 4, 8]))


def longestPalindrome(s):
    if len(s) == 0:
            return ''
    max_str = s[0]
    
    for i in range(len(s)):
        for j in range(i+1,len(s)):
            tmp = s[i:j+1]
            if tmp == tmp[::-1] and len(tmp) > len(max_str):
                max_str = tmp
    return max_str

print(longestPalindrome("abbbac"))




import urllib
import json
import os.path
import time
import threading
from Queue import Queue
from common import download_url
import sys
sys.path.append('..')
from utils.perf_counter import  perf_counter

class NullLock(object):
    """docstring for NullLock"""
    def __init__(self):
        super(NullLock, self).__init__()
    
    def acquire(self):
        pass    

    def release(self):
        pass  

    def __enter__(self):
        self.acquire()

    def __exit__(self, *unused):
        self.release()          
        

class DownPicMgr(object):
    """docstring for DownPicMgr"""
    def __init__(self, sync = False):
        super(DownPicMgr, self).__init__()
        self.serial_path = 'downloaded.txt'
        if not os.path.exists(self.serial_path):
            self.down_pics = set()
        else:            
            with open(self.serial_path) as fp:
                self.down_pics = set(x.strip() for x in fp)

        if sync:                
            self.lock = threading.Lock()
        else:
            self.lock = NullLock()            


    def has_down(self, url):
        with self.lock:
            return url in self.down_pics

    def add(self, url):
        with self.lock:
            self.down_pics.add(url)    

    def serialize(self):
        with self.lock:
            with open(self.serial_path, 'w') as fp:
                for v in self.down_pics:
                    fp.write("%s\n" % v)        
              

class PicGather_base(object):
    """docstring for PicGather_base"""
    def __init__(self, key_word, **kwargs):
        super(PicGather_base, self).__init__()
        self.key_word = key_word        
        self.down_pic_mgr = DownPicMgr()

        self.rn = 50
        if 'rn' in kwargs:
            self.rn = kwargs['rn']
        
        self.pic_dir = 'pics/%s' % self.key_word
        if not os.path.exists(self.pic_dir):
            os.makedirs(self.pic_dir)
    
    # @perf_counter
    # def __call__(self):
    #     url = 'http://image.baidu.com/i?tn=baiduimagejson&width=&height=&ie=utf8&oe=utf-8&ic=0&rn=%d&pn=0&word=%s' % (self.rn, self.key_word)
    #     page = urllib.urlopen(url)
    #     image_urls = self.getImageUrls(json.load(page))
    #     self.download(image_urls)

    def getImageUrls(self, image_infos):
        ret = {}
        if 'data' in image_infos:
            for one_info in image_infos['data']:
                if 'objURL' in one_info:
                    one_url = one_info['objURL']
                    # avoid download again
                    if self.down_pic_mgr.has_down(one_url): 
                        print '%s has already been downloaded' % one_url
                    else:    
                        ret[one_url] = one_info['type']
        return ret
                    
    def download(self, image_urls):
        succ_num = 0
        for one_url in image_urls:                        
            if download_url(one_url, '%s/%s' % (self.pic_dir, self.__get_filename(one_url, image_urls[one_url]))):
                self.down_pic_mgr.add(one_url)
                succ_num += 1

        self.down_pic_mgr.serialize()    
        print 'download total:%d pictures successfully' % succ_num 

    def __get_filename(self, one_url, type):
        head, tail = os.path.split(one_url)
        pos = tail.rfind('.%s' % type)
        if pos == -1:
            return '%s.%s' % (urllib.quote(tail), type)
        else:            
            return '%s_%d.%s' % (tail[0:pos], time.time(), type)

class ImageUrlProducer(object):
    """docstring for ImageUrlProducer"""
    def __init__(self, key_word, rn, max_num, customer_num):
        super(ImageUrlProducer, self).__init__()
        
        self.pic_processed = set()

        self.key_word = key_word
        self.rn = rn
        self.max_num = max_num
        self.customer_num = customer_num
        
    def __call__(self, q):
        pn = 0
        while True:
            url = 'http://image.baidu.com/i?tn=baiduimagejson&width=&height=&ie=utf8&oe=utf-8&ic=0&rn=%d&pn=%d&word=%s' % (self.rn, pn, self.key_word)
            # print url
            page = urllib.urlopen(url)
            if not self.produceImageUrls(json.load(page), q):
                break  

            pn += self.rn
            if self.max_num > 0:  ## 0表示全部下载               
                if pn >= self.max_num:
                    break

        # notify customer to exit
        for i in range(self.customer_num):
            q.put('complete')            

    def produceImageUrls(self, image_infos, q):   
        # with open('images.json', 'w') as fp:
        #     json.dump(image_infos, fp, indent=4)     

        if 'data' in image_infos:

            if len(image_infos['data']) == 1: #data的最后一个info始终是空{}
                return False

            for one_info in image_infos['data']:
                if 'objURL' in one_info:
                    one_url = one_info['objURL']
                    # avoid download again
                    if one_url not in self.pic_processed: 
                        q.put((one_url, one_info['type'], ))
                        self.pic_processed.add(one_url)
                    else:
                        print 'url:%s already processed, skip' % one_url    
            return True
                        
        else:
            return False                
        
class ImageUrlCustomer(object):
    """docstring for ImageUrlCustomer"""
    def __init__(self, pic_dir):
       super(ImageUrlCustomer, self).__init__()
       self.pic_dir = pic_dir       
    
    def __call__(self, q):
        while True:            
            item = q.get()
            if isinstance(item, tuple):
                one_url = item[0]
                file_type = item[1]
                download_url(one_url,  self.calc_local_path(one_url, file_type))
            else:
                break 

    def calc_local_path(self, one_url, type):
        head, tail = os.path.split(one_url)
        pos = tail.rfind('.%s' % type)
        if pos == -1:
            return '%s/%s_%d.%s' % (self.pic_dir, urllib.quote(tail), time.time(), type)
        else:            
            return '%s/%s_%d.%s' % (self.pic_dir, tail[0:pos], time.time(), type)                   
                              

class PicGather_mt(PicGather_base):
    """docstring for PicGather_mt"""
    def __init__(self, key_word, **kwargs):
        super(PicGather_mt, self).__init__(key_word, **kwargs)

        self.max_num = 0
        if 'max_num' in kwargs:
            self.max_num = kwargs['max_num']


    @perf_counter
    def __call__(self):        
        # 1个image-url producer
        # 2个 image-url customer
        thrs = []
        q = Queue(self.rn)
        customer_num = 10

        producer = threading.Thread(target=ImageUrlProducer(self.key_word, self.rn, self.max_num, customer_num), args=(q,))
        thrs.append(producer)        
        
        for i in range(customer_num):
            customer = threading.Thread(target=ImageUrlCustomer(self.pic_dir), args=(q,))
            thrs.append(customer)

        for one_thr in thrs:
            one_thr.start()

        for one_thr in thrs:
            one_thr.join() 
  

pg = PicGather_mt('tiger')
pg()








