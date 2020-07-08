###################################################################### 
**                                                                  **
**                                                                  **
######################################################################

```py
#!/usr/bin/python
# -*- coding: utf-8 -*-
import os,time,random


# TODO contextlib 上下文
# class Query(object):
#     def __init__(self, name):
#         self.name = name   
#     def __enter__(self):        
#         print('Begin')        
#         return self    
#     def __exit__(self, exc_type, exc_value, traceback):        
#         if exc_type:            
#             print('Error')        
#         else:            
#             print('End')    
#     def query(self):        
#         print('Query info about %s...' % self.name) 

# with Query('Bob') as q:
#     q.query()


# TODO itertools
# TODO 无线迭代器
# (1)
# count(初值=0, 步长=1):count 迭代器会返回从传入的起始参数开始的均匀间隔的数值。
# count(10): #从10开始无限循环,count 也可以接收指定的步长参数

from itertools import count
# for n in count(start=0, step=1):
#     print (n)
#     if n == 10:
#         break

# (2)
# islice(count(10), 5)：从 10 开始，输出 5 个元素后结束。
# islice 的第二个参数控制何时停止迭代。但其含义并不是”达到数字 5 时停止“，而是”当迭代了 5 次之后停止“

# (3)
# cycle()会把传入的一个序列无限重复下去
# repeat()负责把一个元素无限重复下去，不过如果提供第二个参数就可以限定重复次数

# (4)
# 通过takewhile()等函数根据条件判断来截取出一个有限的序列
from itertools import takewhile
# print(list(takewhile(lambda x:x<=10,count(1))))


# TODO 可终止迭代器

from itertools import accumulate

# (1)
# accumulate(可迭代对象[, 函数])
#  accumulate 迭代器将返回累计求和结果，或者传入两个参数的话，由传入的函数累积计算的结果。默认设定为相加
# print(list(accumulate(range(5))))

# 迭代器将传入数字依次累加，所以第一个是 0 ，第二个是 0+1， 第三个是 1+2，
# 如此下去。现在我们导入 operator 模块，然后添加进去
import operator

# print(list(accumulate(range(1,6),operator.mul)))

# print(list(accumulate([1,2,3,4,5], initial=100)))


# (2)
# chain(*可迭代对象),将多个可迭代对象合并成一个更长的可迭代对象
from itertools import *
# print(list(chain(['p','x','e'], ['scp', 'nmb', 'balenciaga'])))

# (3) 
# 函数返回的迭代器生成元素(key,group)，key是分组的键值，group是迭代器，从而生成组成这个组的所有项目
# a = ['aa', 'ab', 'abc', 'bcd', 'abcde']
# for i, k in groupby(a, len):
#     print (i, list(k))

# TODO collection
from collections import namedtuple
# (1)
Point = namedtuple('point',['x','y'])
p = Point(1,2)
print(p.x)
print(p)

from collections import deque 
q = deque(['a', 'b', 'c']) 
q.append('x') 
q.appendleft('y') 
print(q) 


from collections import defaultdict
dd = defaultdict(lambda: 'N/A') 
dd['key1'] = 'abc' 
print(dd['key1']) # key1存在 'abc' >>> 
print(dd['key2']) # key2不存在，返回默认值 'N/A'


from collections import OrderedDict 
d = dict([('a', 1), ('b', 2), ('c', 3)]) 
print(d) # dict的Key是无序的 {'a': 1, 'c': 3, 'b': 2} 
od = OrderedDict([('a', 1), ('b', 2), ('c', 3)]) 
print(od) # OrderedDict的Key是有序的 OrderedDict([('a', 1), ('b', 2), ('c', 3)]) 
# OrderedDict的Key会按照插入的顺序排列，不是Key本身排序

# OrderedDict可以实现一个FIFO（先进先出）的dict，当容量超出限制时，先删除最早添加的Key
class LastUpdatedOrderedDict(OrderedDict):
    def __init__(self, capacity): 
        super(LastUpdatedOrderedDict, self).__init__()       
        self._capacity = capacity   
    def __setitem__(self, key, value):        
        containsKey = 1 if key in self else 0        
        if len(self) - containsKey >= self._capacity:            
            last = self.popitem(last=False)            
            print('remove:', last)        
        if containsKey:            
            del self[key]            
            print('set:', (key, value))        
        else:            
            print('add:', (key, value))        
        OrderedDict.__setitem__(self, key, value) 
        
###################################################################### 
**                                                                  **
**                                                                  **
######################################################################
import re
import time
from datetime import datetime
from decimal import Decimal
import logging
import argparse
import ast


# TODO 爬虫
# def get_html(url):
#     try:        
#         kv = {"user-agent": "Mozilla/5.0"}#加上这一句话就行了        
#         reponse = requests.get(url,headers = kv)#发送请求并得到回应       
#         reponse.raise_for_status()#查看状态码 如果不是200则执行except        
#         reponse.encoding = reponse.apparent_encoding#编码方式        
#         return reponse.text#返回网页内容    
#     except:        
#         return "爬取失败"

# if __name__ == '__main__':
#     url = 'https://www.vmall.com/huawei'
#     page = get_html(url)
#     print(page)


# TODO 函数参数
# def value(num):
#     if num == '1':
#         return 'IDLE'
#     else:
#         return 'OK'

# def myfunc(func,expect_value,**kwargs):
#     fact_value = func(**kwargs)
#     print(expect_value)
#     print(bool(re.search(expect_value,fact_value)))

# myfunc(func=value,expect_value='OK | IDLE',num='1')



# TODO 二维数组的正确写法
# num_list = [ [0]*5 ]*2  # error
# num_list = [ [0] * 5 for i in range(2)]   # right

# #  获取list特定元素下标
# # 仅仅能获取都第一个匹配的value的下标
# a=[72, 56, 76, 84, 80, 88,76]
# print(a.index(76))

# # 利用enumerate函数
# print(list(enumerate(a)))  # tuple 
# print [i for i,x in enumerate(a) if x == 76]


# TODO 'and or'
# and中含0，返回0； 均为非0时，返回后一个值， 
2 and 0   # 返回0
2 and 1   # 返回1
1 and 2   # 返回2

# or中， 至少有一个非0时，返回第一个非0,
2 or 0   # 返回2
2 or 1   # 返回2
0 or 1   # 返回1 


# TODO "遍历文件夹"
# import os
# path = 'D:\iTest\HuangLiang_Scripts'   #获取当前路径
# count1,count2 = 0,0
# for root,dirs,files in os.walk(path): 
#     fileAndDirTuples = []   #遍历统计
#     for each in files:
#         count1 += 1   #统计文件夹下文件个数
#         fileAndDirTuples.append((each, root))
#     for folder in dirs:
#         count2 += 1
    
# print count1/2,count2,count1/2-count2       


# TODO "datetime"
# mystr4 ='2020-04-08 17:28:49'
# mystr5 ='2020.04.08.18.28.50'
# dt = datetime.strptime(mystr4[:19],"%Y-%m-%d %H:%M:%S")

# t2 = datetime.strptime(mystr5,"%Y.%m.%d.%H.%M.%S")
# t3 = datetime.now()

# print type((dt-t2).total_seconds())

# temp_list = ' '.join('010100010').split(' ')
# online_count = temp_list.count('1')
# print (online_count)




# TODO "staticmethod classmethod"
# class A(object):
#     a = 'a'
#     @staticmethod
#     def foo1(name):
#         print 'hello', name
#         print A.a # 正常
#         # print A.foo2('mamq') # 报错: unbound method foo2() must be called with A instance as first argument (got str instance instead)
#     def foo2(self, name):
#         print 'hello', name
#     @classmethod
#     def foo3(cls, name):
#         print 'hello', name
#         print A.a
#         print cls().foo2(name)



# list_a = [None,None,12]
# ret = filter(None, list_a)[0]
# print(ret)


# TODO "Decorators"
# def dec(func):
#     print "call dec"
#     def in_dec():
#         print "call in_dec"
#         func()
#     return in_dec      

# @dec
# def test_dec():
#     print "call test_dec"

# print type(test_dec)
# test_dec()



# TODO "__iter__"
# class Sentence():
#     def __init__(self,text):
#         self.text = text
#         self.words = re.findall(text,'\w+')
#     def __repr__(self):
#         return "Sentence:%s" % self.text
#     def __iter__(self):
#         return (match.group() for match in re.finditer(self.text,'\w+'))
#         # for i in self.words:
#         #     yield i
#         # return

# t = Sentence('I have a apple')
# print(t)
# for i in t:
#     print (i)


# import reprlib
# import re

# reword=re.compile('\w+')
# #第三版：生成器表达式
# class Sentence:
#     def __init__(self,text):
#         self.text=text
#     def __repr__(self):
#         return "Sentence(%s)" % self.text
#     def __iter__(self):
#         return (match.group() for match in reword.finditer(self.text))
# title=Sentence('We have a dream!')
# print(title)
# for i in title:
#     print(i)


# TODO  "实现switch_case的功能"
# def login():
#     '''登录'''
#     print('登录成功')

# def registry():
#     '''注册'''
#     print('注册成功')

# func = {
#     '0':('退出',None),
#     '1':('登录',login),
#     '2':('注册',registry),
# }
# while True:
#     for i in func:
#         print(i,func[i][0])
#     choice = input('请输入您要执行的操作编号：').strip()
#     if choice == '0':
#         break
#     elif choice not in func:
#         print('尊敬的用户，您好！你需要执行的操作不存在，请重新选择操作编号!')
#         continue
#     else:
#         func[choice][1]()


# TODO "getattr的使用"
# class My_Func():
#     def __init__(self):
#         pass
#     def print_A(self):
#         print('------A')
#     def print_B(self):
#         print('------B')
#     def print_C(self):
#         print('------C')
#     def dispatch(self,value):
#         method_name = 'print_' + str(value)
#         method = getattr(self,method_name)
#         method()

# S = My_Func()
# S.dispatch('A')
# S.dispatch('B')

# class Base():
#     init = False

#     @classmethod
#     def set_init(cls):
#         cls.init = True    # 传入的是Derived类，给Derived添加了成员,Derived的init和Base的init不是同一个属性
 

#     # @staticmethod
#     # def set_init():
#     #     Base.init = True

# class Derived(Base):
#     pass

# print('-------------')

# Derived.set_init()
# print(Derived.init)
# print(Base.init)
# print(id(Derived.init))
# print(id(Base.init))

# class Dept(object):

#       def __init__(self, name):
#           self.name = name

#       # target是拥有此属性的对象
#       def __get__(self, target, type=None):
#         # 默认返回self与obj都可以
#         return 'Hello'

# class Company(object):
#     #   一定要作为类属性，作为实例属性无效
#     dept = Dept('organ')

# # 现在的测试结果
# x = Company()
# #   返回True
# print (x.dept)

# def my_partial(func,*args,**kwargs):
#     def newfunc(*fargs,**fkwargs):
#         newkwargs = {**kwargs,**fkwargs}
#         return func(*args,*fargs,**newkwargs)
#     newfunc.func = func
#     newfunc.args = args
#     newfunc.kwargs = kwargs
#     return newfunc

# from functools import partial
# basetwo = partial(int,base=16)

# print(basetwo('12'))

# def fn(self,name='world'):
#     print('hello,%s' % name)

# Hello = type('hello',(object,),dict(hello=fn))

# h = Hello()
# h.hello()
# print(type(Hello))
# print(type(h))
# print(type(h.hello))

# class ListMetaclass(type):
#     def __new__(cls,name,bases,attrs):
#         attrs['add'] = lambda self,value:self.append(value)
#         return type.__new__(cls,name,bases,attrs)

# class MyList(list, metaclass=ListMetaclass):
#     pass

# L = MyList()
# L.add(1)
# print(L)


# class ModelMetaclass(type):
#     def __new__(cls,name,bases,attrs):
#         if name == 'Model':
#             return type.__new__(cls,name,bases,attrs)
#         print('Found model:%s' % name)
#         mappings = dict()
#         for k,v in attrs.items():
#             if isinstance (v,Field):
#                 print('Found Mapping: %s ==> %s' % (k,v))
#                 mappings[k] = v
#         for k in mappings.keys():
#             attrs.pop(k)
#         attrs['__mappings__'] = mappings
#         attrs['__table__'] = name
#         return type.__new__(cls,name,bases,attrs)

# class Model(dict,metaclass=ModelMetaclass):
#     def __init__(self,**kw):
#         super(Model,self).__init__(**kw)
#     def __getattr__(self,key):
#         try:
#             return self[key]
#         except KeyError:
#             raise AttributeError(r"'Model' object has no attribute '%s'" % key)
#     def __setattr__(self,key,value):
#         self[key] = value
#     def save(self):
#         fields = []
#         params = []        
#         args = []        
#         for k, v in self.__mappings__.items():
#             fields.append(v.name)
#             params.append('?') 
#             args.append(getattr(self, k, None))        
#         sql = 'insert into %s (%s) values (%s)' % (self.__table__, ','.join(fields), ','.join(params))        
#         print('SQL: %s' % sql)        
#         print('ARGS: %s' % str(args)) 

# class Field(object):
#     def __init__(self,name,column_type):
#         self.name = name
#         self.column_type = column_type
#     def __str__(self):
#         return '<%s:%s>' % (self.__class__.__name__,self.name)

# class StringField(Field):
#     def __init__(self,name):
#         super(StringField,self).__init__(name,'varchar(100)')

# class IntegerField(Field):
#     def __init__(self,name):
#         super(IntegerField,self).__init__(name,'bigint')

# class User(Model):
#     # 定义类的属性到列的映射：
#     id = IntegerField('id')
#     name = StringField('username')
#     email = StringField('email')
#     password = StringField('password')

# u = User(id=12345, name='Michael', email='test@orm.org', password='my-pwd') 
# u.save() 



# def normalize(params_info):
#     """
#     字典解析，前端字典解析为后端字典
#     :param params_info:
#     :return:
#     """
#     params_info_filter = {}
#     for info in params_info:
#         key = info.pop('field')
#         params_info_filter[key] = info
#     if "pool_size" not in params_info_filter:
#         params_info_filter["pool_size"] = {"help": "connect pool size", "type": int, "default": 10}
#     parser = argparse.ArgumentParser(description='Process some integers.')
#     if isinstance(params_info_filter, dict):
#         for key, value in params_info_filter.items():
#             item_key = '--' + key
#             if value['type'] == bool or value['type'] == list or value['type'] == dict:
#                 value['type'] = ast.literal_eval
#             parser.add_argument(item_key, **value)
#         task_id = {"help": "任务号，web发起请求任务的编号", "type": str, "default": ''}
#         w3 = {"help": "w3账号", "type": str, "default": ''}
#         parser.add_argument("--task_id", **task_id)
#         parser.add_argument("--w3", **w3)
#     args = parser.parse_args()
#     return args

# params_info = [
#     # 必传参数
#     # ip: 设备ip，username: 设备登录账号，password: 设备登录密码，device_type: 设备是阵列还是主机
#     {"field": "devices", "help": "配置设备的参数", "type": list, "default":
#         [{"ip": "10.183.165.136", "username": "root", "password": "huawei", "device_type": "host"},
#          {"ip": "51.38.57.52", "username": "admin", "password": "Admin@storage", "device_type": "controller"}]},
#     # 自定义参数
#     {"field": "filename", "help": "设置脚本名称（默认为文件名）", "type": str, "default": ''},
#     {"field": "pool_size", "help": "connect pool size", "type": int, "default": 10},
#     {"field": "self_defined", "help": "self_defined", "type": bool, "default": 1, "choices": [True, False]},
# ]
# params = normalize(params_info)
# print(params)


# from collections import namedtuple

# User = namedtuple('User',['name','sex','age'])

# user_1 = User(name= 'Jack',sex='male',age=20)
# print(user_1)
# print(user_1._fields)
# user_2 = User._make(['Mary','female',10])
# print(user_2)
# print(user_1.name)
# user_1._replace(name='new_jack')
# print(user_1.name)
# print(user_1._asdict())

users = {"tom": 1, "jenny": 2, "jack": 3, "andrew": 4}
print(sorted(users.keys(), key=lambda user: users.get(user) or float('inf')))


import  typing
def add_ellipsis_gen(comments: typing.Iterable[str], max_length: int = 12):
    """如果可迭代评论里的内容超过 max_length，剩下的字符用省略号代替
    """
    for comment in comments:
        comment = comment.strip()
        if len(comment) > max_length:
            yield comment[:max_length] + '...'
        else:
            yield comment


comments = ("Implementation note", "Changed", "ABC for generator")
print("\n".join(add_ellipsis_gen(comments)))




###################################################################### 
**                                                                  **
**                                                                  **
######################################################################

# TODO  枚举类
# import re

# from enum import Enum

# class Color(Enum):
#     YELLOW =1
#     RED =2
#     GREEN =3

# print(Color.YELLOW)
# print(Color.YELLOW.value)
# print(Color(1))
# print(type(Color(1)))



# TODO  @property 变方法为属性

# class Student():
#     def __init__(self,name,age=18):
#         self.name =name
#         self.__age =age    #age属性外部不能访问  _Student__age

#     @property              #定义只读属性
#     def age(self):
#         return self.__age

#     @age.setter
#     def age(self,age):
#         if age < 18 :
#             print('age must greater than 18')
#             return 
#         else :
#             self.__age =age
#             return self.__age

#     def __call__(self):
#         print('%s age is %s' %(self.name, self.__age))
    
# stu=Student("Xiaoming",20)
# print(stu.age)
# stu.age = 10
# print(stu.age)
# stu.age = 30
# print(stu.age)
# print(stu())
# print(dir(stu))

# TODO  函数身为一个对象，拥有对象模型的三个通用属性：id、类型、和值。
# def foo():
#     print('from foo')
# foo()

# print(id(foo))
# print(type(foo))
# print(foo)

# fun =foo()
# print(id(fun))
# print(type(fun))
# print(fun)


# TODO  函数嵌套
# def f1():
#     def f2():
#         print('from f2')
#         def f3():
#             print('from f3')
#         print('before f3')    
#         f3()
#         print('after f3')    
#     print('before f2')
#     f2()
#     print('after f2')

# f1()

# # 函数可以作返回值
# def foo(str):
#     print('from foo %s' %str)
# def bar(func):
#     return func     

# f=bar(foo)
# print(f)
# f('test')
# bar(foo('test'))


# TODO 4.1 与None作比较要使用“is”或“is not”，不要使用等号 
# class Bad(object):
#     def __eq__(self, other):        
#         return True 

# print(Bad() == None)   # ==操作会调用左操作数的__eq__函数，而这个函数可以被其任意定义
# print(Bad() is None) 



# TODO  staticmethod classmethod
# 方法不需要访问任何成员，或者只需要显式访问这个类自己的成员。这样的方法不需要额外参数，应当用 @staticmethod装饰。
# 方法不需要访问实例的成员，但需要访问基类或派生类的成员。这时应当用@classmethod装饰。装饰后的方法，其第一个参数不再传入实例，而是传入调用者的底层类 
# 使用@classmethod时需要注意，由于在继承场景下传入的第一个参数并不一定是这个类本身
# 因此并非所有访问类成员的场景都应该用@classmethod

# class Base():
#     init = False
#     # @classmethod
#     # def set_init(cls):
#     #     cls.init = True    # 传入的是Derived类，给Derived添加了成员,Derived的init和Base的init不是同一个属性
 

#     @staticmethod
#     def set_init():
#         Base.init = True

# class Derived(Base):
#     pass

# print('-------------')

# Derived.set_init()
# print(Derived.init)
# print(Base.init)
# print(id(Derived.init))
# print(id(Base.init))




# TODO 继承
# 如果子类(Puple)继承父类(Person)不做初始化，那么会自动继承父类(Person)属性name。
# 如果子类(Puple_Init)继承父类(Person)做了初始化，且不调用super初始化父类构造函数，那么子类(Puple_Init)不会自动继承父类的属性(name)。
# 如果子类(Puple_super)继承父类(Person)做了初始化，且调用了super初始化了父类的构造函数，那么子类(Puple_Super)也会继承父类的(name)属性

# class Father(object):    
#     def __init__(self, age):        
#         self.age=age        
#         print ( "age: %d" %( self.age) )    
#     def getAge(self):        
#         print('Father return ')        
#         return self.age 

# class Son(Father):  
#     def __init__(self,age):
#        # Father.__init__(self,age)
#        # super(子类名，self).__init__(父类属性)， 其中在子类初始化函数中要将父类的__init__函数中的父类属性全部包含进来
#         super(Son,self).__init__(age)
#         print("hello")  
#     def getAge(self):        
#         print('Son return')        
#         return self.age

# son=Son(18)
# print ( son.getAge() )

# python 类的继承
"""
（1）：直接调用父类属性方法；
（2）：重写父类属性方法；
        子类没有重写父类的方法，当调用该方法的时候，会调用父类的方法，当子类重写了父类的方法，默认是调用自身的方法。
        另外，如果子类Son重写了父类Father的方法，如果想调用父类的action方法，可以利用super().func() # func()为父类方法
（3）：强制调用父类私有属性方法； 编译器是把这个方法的名字改成了 _Father__func()
（4）：调用父类的__init__方法
        如果自己也定义了 __init__ 方法,那么父类的属性是不能直接调用的，会报错
        修改方法：可以在 子类的 __init__中调用一下父类的 __init__ 方法,这样就可以调用了
（5）：继承父类初始化过程中的参数
原文链接：https://blog.csdn.net/yilulvxing/article/details/85374142
"""

# TODO  局部变量 
# https://blog.csdn.net/HappyRocking/article/details/80115241
# company = 'ali'  # 全局变量      
# def change_name(name):
#     global company         # company 提升为全局变量 
#     company = 'tengxu'    # 局部变量
#     print("befor change", name, company)
#     name = 'zhangsan'  # 这个函数就是这个变量的作用域
#     print("after change", name)      
# print('company: ', company)   # 执行查看函数调用前打印的情况
# name = 'lisi'
# change_name(name)
# print(name)
# print('company: ', company)   # 执行查看函数调用后打印的情况 company值已改变为tengxun


# company = 'ali'  # 全局变量
# names = ['zhangsan', 'sili', 'wangwu']  
# def change_name():
#     names[0] = 'wwwww'
#     print("inside_func: ", names)          # 运行查看执行结果    
# change_name()
# print('ouside_func：', names)   # 运行查看执行结果



# TODO 类的高级函数

# https://blog.csdn.net/yiifaa/article/details/78068962?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.nonecase&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.nonecase
# python总结(五)：__get__、__getattr__、__getitem__、__getattribute__之间的差异与联系
# https://blog.csdn.net/weixin_38729390/article/details/86755682?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-8.nonecase&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-8.nonecase
# Python中的__get__ __getattr__ __getattribute__

# class Test_A(object):
#     def __init__(self,name):
#         self.name = name
#     def __str__(self):
#         return 'Name:%s' %self.name
#     def __repr__(self):
#         return 'Name:%s' %self.name
# print(Test_A('Jack'))

# 想要被for循环迭代，这个类就要有__iter__(),返回一个迭代对象
# for就会不断调用该调用这个迭代对象的__next__()方法拿到返回的值，然后继续调用next方法继续返回值，直到StopIteration退出循环
# 执行书顺序为： __init__  __iter__ __next__  print __next__ print __next__ ...
# class Fib(object):
#     def __init__(self):
#         self.a,self.b = 0,1
#     def __iter__(self):
#         return self
#     def __next__(self):
#         self.a,self.b =self.b,self.a+self.b
#         if self.a > 20:
#             raise StopIteration
#         return self.a

# for n in Fib():
#     print(n)


# 像list一样切片
# class Slice(object):
#     def __getitem__(self,n):
#         if isinstance(n,int):
#             a,b =0,1
#             for x in range(n):
#                 a,b =b,a+b
#             return a
#         if isinstance(n,slice):
#             start = n.start
#             stop = n.stop
#             if start is None:
#                 start =0
#             a,b =0,1
#             L = []
#             for x in range(stop):
#                 if x >= start:
#                     L.append(a)
#                 a,b =b,a+b
#             return L

# f=Slice()
# print(f[0])
# print(f[0:5])


# TODO 爬虫入门 装饰器 偏函数 生成器
# https://blog.csdn.net/Appleyk/article/details/78070098
# https://blog.csdn.net/Appleyk/article/details/77412961
# https://blog.csdn.net/Appleyk/article/details/77609114
# https://blog.csdn.net/mieleizhi0522/article/details/82142856/
# https://www.cnblogs.com/coder2012/p/4990834.html


def clean():
    print('-----Clean:-----') 

def handler(clean_func):
    def decorator(func):
        print('装饰器内部--------------')
        def warper(*args,**kwargs):
            func(*args,**kwargs)
            print('-----%s exectue finished-----' % func.__name__)
            return clean_func()
        return warper
    return decorator   


# 相当于 handler(clean)(f) 是一个函数
# 装饰器不传入参数时  ,f = handler(函数名)
# 装饰器传入参数时,f = handler(参数)(函数名)

@handler(clean)
def run(info):
    print('-----Run:%s-----' % info)


print('-----before-----')
run('123')
print('-----after-----')


# import operator

# def accumulate(iterable, func=operator.add, *, initial=None):
#     it = iter(iterable)
#     total = initial
#     if initial is None:
#         try:
#             total = next(it)
#         except StopIteration:
#             return 
#     yield total
#     for element in it:
#         total = func(total,element)
#         yield total

# print(list(accumulate(range(1,6),operator.mul)))

# TODO 必需在函数体内部,并且是赋值操作，使用append 方法之类不成立 只是循环语句不是函数也不适用一下情况
# 如果使用global关键字声明变量为全局变量，则直接使用全局变量进行读取和写入，无歧义
# 如果没有global关键字对全局变量的声明，则分2种情况：
# a.如果函数体内没有对全局变量名赋值操作，则直接读取全局变量值使用，没有问题
# b.如果函数体内有对全局变量名的赋值操作，则编译器会认为赋值处定义了局部变量，并且绑定此变量名到此局部变量，并影响整个函数体内的相同变量名。
# 这样一来，如果在赋值操作前进行了全局变量名使用则会报错“UnboundLocalError: local variable 'use_width' referenced before assignment”。
# 解决：此时必须将赋值操作放在函数内此变量使用前，或者在函数开头使用global引入全局变量来进行读取使用，具体操作根据实际业务逻辑需求确定。

# ret = []
# tmp = {}

# for i in range(3):
#     tmp['A'] = 10*i
#     tmp['B'] = 100*i
#     print(id(tmp))
#     ret.append(tmp)
#     print(id(ret))

# print(ret)

# ret = {}
# def func():
#     for i in xrange(3):
#         print(ret)
#         # ret ={'C':5}
#         ret['A'] = i
#         ret['B'] = i*10
#     print(ret)
# func()

# TODO python小特性：is和==、变量的内存管理、小整数对象池、intern机制
# https://blog.csdn.net/weixin_44571270/article/details/105736076?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-4.nonecase&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-4.nonecase
# https://blog.csdn.net/dogpig945/article/details/81363494
# https://www.zhihu.com/question/20114936


# import pprint,json
# info = {'AlarmObj': 'INTF_MODULE', 'AlarmID': '0xf00d10049', 'Num': 'NO.0768', 'AlarmMsg': 'Interface module ([FrameType:1 Controller Enclosure], [PhyType:ETH], [ServiceType:0] interface module [BoardID:0x98]) is not inserted into the recommended slot. The recommended slot number list is ([SlotIDList:0xa000000]).', 'Time': '2020-06-18 16:21:39', 'AlarmType': 'fault'}

# # print(json.dumps(info,indent=4, ensure_ascii=False))
# pprint.pprint(info)









```
