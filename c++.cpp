#!/usr/bin/python
# -*- coding: utf-8 -*-
# TODO 1.可变对象和不可变对象
'''
Python的每个对象都分为可变和不可变，主要的核心类型中，数字、字符串、元组是不可变的，列表、字典是可变的。
对不可变类型的变量重新赋值，实际上是重新创建一个不可变类型的对象，并将原来的变量重新指向新创建的对象
（如果没有其他变量引用原有对象的话（即引用计数为0），原有对象就会被回收）
注意：Python内存管理机制，Python对（int类型）和（较短的字符串）进行了缓存，无论声明多少个值相同的变量，实际上都指向同个内存地址
可变类型的话，以list为例。list在append之后，还是指向同个内存地址，因为list是可变类型，可以在原处修改，但两个值相同的list地址不一定相同
https://www.cnblogs.com/blackmatrix/p/5614086.html

https://www.jianshu.com/p/c5582e23b26c
python规定参数传递都是传递引用，也就是传递给函数的是原变量实际所指向的内存空间，修改的时候就会根据该引用的指向去修改该内存中的内容，
所以按道理说我们在函数内改变了传递过来的参数的值的话，原来外部的变量也应该受到影响。但是上面我们说到了python中有可变类型和不可变类型，
这样的话，当传过来的是可变类型(list,dict)时，我们在函数内部修改就会影响函数外部的变量。
而传入的是不可变类型时在函数内部修改改变量并不会影响函数外部的变量，因为修改的时候会先复制一份再修改

is（比较id）和==(比较值)
#与None作比较要使用“is”或“is not”，不要使用等号,对于类，可以用__eq__重载== 
class Bad(object):
    def __eq__(self, other):        
        return True 

print(Bad() == None)   # ==操作会调用左操作数的__eq__函数，而这个函数可以被其任意定义
print(Bad() is None) 

def add_end(L=[]):    
    L.append('END')    
    return L

add_end() # ['END']
add_end() # ['END','END']

# None是不变对象
def add_end2(L=None):    
    if L is None:        
        L = []    
    L.append('END')    
    return L

add_end2() # ['END']
add_end2() # ['END']
'''
# TODO 局部变量和全局变量
'''
# https://blog.csdn.net/HappyRocking/article/details/80115241
company = 'ali'  # 全局变量      
def change_name(name):
    global company         # company 提升为全局变量 
    company = 'tengxun'    # 为全局变量赋值
    print("befor change", name, company)
    name = 'zhangsan'  # name是局部变量，变量的作用域为仅为该函数
    print("after change", name)      
print('company: ', company)   # 执行查看函数调用前打印的情况
name = 'lisi'
change_name(name)
print(name)
print('company: ', company)   # 执行查看函数调用后打印的情况 company值已改变为tengxun
'''


# TODO tuple
# 只有1个元素的tuple定义时必须加一个逗号,，来消除歧义
# t = (1,)# (定义元组) 
# t=(1) #(定义一个整数值为1)


# TODO set map
# 一个对象能不能作为字典的key，决于其有没有__hash__方法，
# 所以所有python自带类型中，除了list、dict、set和内部至少带有上述三种类型之一的tuple之外，其余的对象都能当key
#  https://blog.csdn.net/lnotime/article/details/81192207  待学习
# 可以使用大括号 { } 或者 set() 函数创建集合，注意：创建一个空集合必须用 set() 而不是 { }，因为 { } 是用来创建一个空字典
#  s = set([1, 2, 3]) 


# TODO 函数
# 函数身为一个对象，拥有对象模型的三个通用属性：id、类型、和值
# 函数执行完毕也没有return语句时，自动return None。 
# 函数可以同时返回多个值，但其实就是一个tuple，而多个变量可以同时接收一个tuple，按位置赋 给对应的值
'''
函数的参数
1.位置参数
2.默认参数(必选参数在前，默认参数在后)定义默认参数要牢记一点：默认参数必须指向不变对象！
Python函数在定义的时候，默认参数L的值就被计算出来了，即[]，因为默认参数L也是一个变量，它指向对象[]，
每次调用该函数，如果改变了L的内容，则下次调用时，默认参数的内容就变了，不再是函数定义时的[]了。
参考 add_end()函数
3.可变参数：*agrs,允许你传入0个或任意个参数，这些可变参数在函数调用时自动组装为一个tuple 
*nums表示把nums这个list的所有元素作为可变参数传进去
4.关键字参数：**kargw,关键字参数允许你传入0 个或任意个含参数名的参数，这些关键字参数在函数内部自动组装为一个dict
**extra表示把extra这个dict的所有key-value用关键字参数传入到函数的**kw参数，kw将获得一个dict，
注意kw获得的 dict是extra的一份拷贝，对kw的改动不会影响到函数外的extra
person('Jack', 24, city=extra['city'], job=extra['job']) 
extra = {'city': 'Beijing', 'job': 'Engineer'} 
person('Jack', 24, **extra)
5.命名关键字参数:如果要限制关键字参数的名字，就可以用命名关键字参数,
和关键字参数**kw不同，命名关键字参数需要一个特殊分隔符*，*后面的参数被视为命名关键字参数
如果函数定义中已经有了一个可变参数，后面跟着的命名关键字参数就不再需要一个特殊分隔符*了
命名关键字参数必须传入参数名，这和位置参数不同
def person(name, age, *, city='Beijing', job):    
    print(name, age, city, job) 
6.对于任意函数，都可以通过类似func(*args, **kw)的形式调用它
7.尾递归优化
8. 匿名函数 lambda
匿名函数有个限制，就是只能有一个表达式，不用写return，返回值就是该表达式的结果。
关键字lambda表示匿名函数，冒号前面的x表示函数参数
list(map(lambda x: x * x, [1, 2, 3, 4, 5, 6, 7, 8, 9])) 
用匿名函数有个好处，因为函数没有名字，不必担心函数名冲突。
此外，匿名函数也是一个函数对象，也可以把匿名 函数赋值给一个变量，再利用变量来调用该函数
f = lambda x: x * x 
f(5) 
也可以把匿名函数作为返回值返回
def build(x, y):    
    return lambda: x * x + y * y 
9.函数可以作返回值
def foo(str):
    print('from foo %s' %str)
def bar(func):
    return func     

f=bar(foo)
print(f)
f('test')
# 注意 bar(foo('test')) 相当于先执行foo('test')，再执行bar(None)
# bar(foo)('test') 等价于 f('test')
'''

# TODO generator
'''

'''


# TODO iterator iterable
'''
凡是可作用于for循环的对象都是Iterable类型； 
凡是可作用于next()函数的对象都是Iterator类型，它们表示一个惰性计算的序列；
生成器是Iterator类型，用yield关键字，不用自己实现
集合数据类型如list、dict、str等是Iterable但不是Iterator，不过可以通过iter()函数获得一个Iterator对象。 
Python的for循环本质上就是通过不断调用next()函数实现的，例如： 
for x in [1, 2, 3, 4, 5]:    
    pass
实际上完全等价于： 
# 首先获得Iterator对象: 
it = iter([1, 2, 3, 4, 5]) 
# 循环: 
while True:    
    try:        
        # 获得下一个值:        
        x = next(it)    
    except StopIteration:        
        # 遇到StopIteration就退出循环        
        break
'''


# TODO 函数式编程
'''
函数名其实就是指向函数的变量
既然变量可以指向函数，函数的参数能接收变量，那么一个函数就可以接收另一个函数作为参数，这种函数就称之为 高阶函数。
# f类似于函数指针
def add(x, y, f):    
    return f(x) + f(y) 

1.map
2.reduce
from functools import reduce 
DIGITS = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9} 
def char2num(s):    
    return DIGITS[s] 
def str2int(s):    
    return reduce(lambda x, y: x * 10 + y, map(char2num, s)) 

3.sorted
# key指定的函数将作用于list的每一个元素上，并根据key函数返回的结果进行排序
users = {"tom": 1, "jenny": 3, "jack": 2, "andrew": 4}
print(sorted(users.keys(), key=lambda user: users.get(user) or float('inf')))
'''


# TODO 闭包
'''
当某个函数被当成对象返回时，夹带了外部变量，就形成了一个闭包
闭包函数相对与普通函数会多出一个__closure__的属性，里面定义了一个元组用于存放所有的cell对象，
每个cell对象一一保存了这个闭包中所有的外部变量
https://segmentfault.com/a/1190000007321972
https://www.cnblogs.com/daodantiantou/p/10373700.html
Python 命名空间的查找规则简写为 LEGB，四个字母分别代表 local、enclosed、global 和 build-in
闭包有个重要的特性：内部函数只能引用而不能修改外部函数中定义的自由变量,而是外部的自由变量被内部的局部变量覆盖了,解决办法：
一种做法是利用可变类型(mutable)的特性，把变量存放在列表(List)之中。对可变的列表的修改并不需要对列表本身赋值
另一种Python 3 引入了 nonlocal 关键字，明确告诉解释器：这不是局部变量，要找上外头找去，在 Python 2 中，用 global 
https://www.jianshu.com/p/5eb8dd264bb9

def count():    
    fs = []    
    for i in range(1, 4):        
        def f(): 
            print("%d,id:%d"%(i,id(i)))            
            return i*i        
        fs.append(f)    
    return fs
f1, f2, f3 = count() 
print(f1(),f2(),f3())


def count():    
    def f(j):        
        def g():            
            return j*j        
        return g    
    fs = []    
    for i in range(1, 4):        
        fs.append(f(i)) # f(i)立刻被执行，因此i的当前值被传入f()    
    return fs

f1, f2, f3 = count() 
print(f1(),f2(),f3())

def count():    
    def f(j):        
        return lambda: j*j    
    fs = []
    [fs.append(f(i)) for i in range(1,4)]
    return fs    

f1, f2, f3 = count() 
print(f1(),f2(),f3())

def outer():
    x = 5
    def inner(): # 上面一行的x相对inner函数来说是函数外的局部变量（非全局变量）
        nonlocal x
        x = x + 1 # 在local里，相当于定义一个x变量，并把x+1赋给它，局部变量x还没赋值就被引用了
        print(x)
        return x
    return inner

print(outer()())



#当我们调用my_sum()时，每次调用都会返回一个新的函数，即使传入相同的参数
def my_sum(*args):
    def test():
        a = 0
        for i in args:  # 注意此处是 agrs，不是 *agrs
            a += i
        return a
    return test


f1 = my_sum(1,2,3)  
f2 = my_sum(1,2,3)  
print(my_sum(1,2,3)) # <function my_sum.<locals>.test at 0x00000234C2364160>
print(my_sum(1,2,3)) # <function my_sum.<locals>.test at 0x00000234C2364160>
print(f1)  # <function my_sum.<locals>.test at 0x00000234C2364040>
print(f2)  # <function my_sum.<locals>.test at 0x00000234C23640D0>

'''

# TODO 装饰器 偏函数
'''
import functools

# now = log(now)
def log(func):
    @functools.wraps(func)
    def wrapper(*args, **kw):
        print('call %s():' % func.__name__)
        return func(*args, **kw)
    return wrapper


# now = log('execute')(now)
# 我们来剖析上面的语句，首先执行log('execute')，返回的是decorator函数，
# 再调用返回的函数，参数是now函数，返回值最终是wrapper函数
# 函数也是对象，它有__name__等属性，但你去看经过decorator装饰之后的函数now
# now.__name__ ='wrapper'
def log(text):
    def decorator(func):
        @functools.wraps(func)
        def wrapper(*args, **kw):
            print('%s %s():' % (text, func.__name__))
            return func(*args, **kw)
        return wrapper
    return decorator
'''

# TODO 偏函数
'''
# 创建偏函数时，实际上可以接收函数对象、*args和**kw这3个参数，
# 当传入：int2 = functools.partial(int, base=2)
# 相当于：kw = { 'base': 2 }  int('10010', **kw)
# 当传入：max2 = functools.partial(max, 10)
# 相当于：args = (10, 5, 6, 7) max(*args)

# 实现偏函数
def my_partial(func,*args,**kwargs):
    def newfunc(*fargs,**fkwargs):
        newkwargs = {**kwargs,**fkwargs}
        return func(*args,*fargs,**newkwargs)
    # newfunc.func = func
    # newfunc.args = args
    # newfunc.kwargs = kwargs
    return newfunc

base_hex = my_partial(int,base=2)

print(base_hex('1010'))
'''


# TODO 类
'''
1.和静态语言不同，Python允许对实例变量绑定任何数据，
也就是说，对于两个实例变量，虽然它们都是同一个类的不 同实例，但拥有的变量名称都可能不同
Class A:
    pass

A.name = 'xiaoming'
print(A.name)

2. 访问限制
在Python中，实例的变量名如果以__开 头，就变成了一个私有变量（private），只有内部可以访问，外部不能访问，对外提供 get/set接口
不能直接访问__name是因为Python解释器对外 把__name变量改成了_Student__name，
所以，仍然可以通过_Student__name来访问__name变量

以一个下划线开头的实例变量名，比如_name，这样的实例变量外部是可以访问的，
但是，按照约定俗成的规定，当你看到这样的变量时，意思就是，“虽然我可以被访问，但是，请把我视为私有变量，不要随意访问

3.继承和多态

Python的“file-like object“就是一种鸭子类型

如果要判断一个对象是否是函数怎么办？可以使用types模块中定义的常量：
import types
def fn():  
    pass
type(fn)==types.FunctionType

总是优先使用isinstance()判断类型，可以将指定类型及其子类“一网打尽”
isinstance([1, 2, 3], (list, tuple)) 

如果要获得一个对象的所有属性和方法，可以使用dir()函数，它返回一个包含字符串的list

getattr()、setattr()以及hasattr()，我们可以直接操作一个对象的状态
fn = getattr(obj, 'power', 404) # 获取属性'power'，如果不存在，返回默认值404 
fn() # 调用fn()与调用obj.power()是一样的, fn指向obj.power 

# python 类的继承
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
class Father(object):    
    def __init__(self, age):        
        self.age=age        
        print ( "age: %d" %( self.age) )    
    def getAge(self):        
        print('Father return ')        
        return self.age 

class Son(Father):  
    def __init__(self,age):
        # Father.__init__(self,age) # python2.2以前
        # super(Son,self).__init__(age) # python2.2以后
        super().__init__(age)  # python3以后
        print("hello")  
    def getAge(self):        
        print('Son return')        
        return self.age
    def getAge2(self): 
        super().getAge()       
        print('Son return')        
        return self.age

son=Son(18)
print (son.getAge())
print (son.getAge2())


4.实例属性和类属性
实例属性属于各个实例所有，互不干扰；
Student a
a.name = 'xiaoming'
类属性属于类所有，所有实例共享一个属性
class Student(object):   
    name = 'Student'
在编写程序的时候，千万不要对实例属性和类属性使用相同的名字，
因为相同名称的实例属 性将屏蔽掉类属性，但是当你删除实例属性后，再使用相同的名称，访问到的将是类属性
'''


# TODO 类的高级特性
'''
1.__slots__
动态绑定允许我们在程序运行的过程中动态给class加上功能，这在静态语言中很难实现
为了达到限制的目的，Python允许在定义class的时候，定义一个特殊的__slots__变量，来限制该class实例能添加的属性：
class Student(object):    
    __slots__ = ('name', 'age') # 用tuple定义允许绑定的属性名称
 s = Student()
 s.name = 'Michael' # ok
 s.score = 99 # 绑定属性'score' ,error
 使用__slots__要注意，__slots__定义的属性仅对当前类实例起作用，对继承的子类是不起作用的

2.@property
@property装饰器就是负责把一个方法变成属性调用的： 

class Student(object): 
    def __init__(self,name,score=18):
        self.name =name
        self.__score =score    #score属性外部不能访问  _Student__score
   
    @property    
    def score(self):        
        return self._score    
    @score.setter    
    def score(self, value):        
        if not isinstance(value, int):            
            raise ValueError('score must be an integer!')        
        if value < 0 or value > 100:            
            raise ValueError('score must between 0 ~ 100!')        
        self._score = value 

s = Student() 
s.score = 60 # OK，实际转化为s.set_score(60) 
s.score # OK，实际转化为s.get_score() 

可以定义只读属性，只定义getter方法，不定义setter方法就是一个只读属性

3.__str__
class Student(object):    
    def __init__(self, name):        
        self.name = name    
    def __str__(self):        
        return 'Student object (name=%s)' % self.name    
    __repr__ = __str__ 

4.__iter__
# 想要被for循环迭代，这个类就要有__iter__(),返回一个迭代对象
# for就会不断调用该调用这个迭代对象的__next__()方法拿到返回的值，然后继续调用next方法继续返回值，直到StopIteration退出循环
# 执行书顺序为： __init__ __iter__  __next__  print __next__ print __next__ ...
class Fib(object):
    def __init__(self):
        self.a,self.b = 0,1
    def __iter__(self):
        return self
    def __next__(self):
        self.a,self.b =self.b,self.a+self.b
        if self.a > 20:
            raise StopIteration
        return self.a

for n in Fib():
    print(n)

import re
class Sentence():
    def __init__(self,text):
        self.text = text
        self.words = re.findall(r'\w+',text)
    def __repr__(self):
        return "Sentence:%s" % self.text
    def __iter__(self):
        # return (match.group() for match in re.finditer(r'\w+',self.text))
        for i in self.words:
            yield i

title=Sentence('We have a dream!')
for i in title:
    print(i)

5.__getitem__
像list一样切片
class Slice(object):
    def __getitem__(self,n):
        if isinstance(n,int):
            a,b =0,1
            for x in range(n):
                a,b =b,a+b
            return a
        if isinstance(n,slice):
            start = n.start
            stop = n.stop
            if start is None:
                start =0
            a,b =0,1
            L = []
            for x in range(stop):
                if x >= start:
                    L.append(a)
                a,b =b,a+b
            return L

f=Slice()
print(f[0])
print(f[0:5])

6.__getattr__
当调用不存在的属性时，比如score，Python解释器会试图调用__getattr__(self, attr)来尝试获得属性
class Student(object):    
    def __getattr__(self, attr):        
        if attr=='age':            
            return lambda: 25        
        raise AttributeError('\'Student\' object has no attribute \'%s\'' % attr)


s = Student()
print(s.age())
print(s.name)


# 重要
class Chain(object):    
    def __init__(self, path=''):        
        self._path = path    
    def __getattr__(self, path):        
        return Chain('%s/%s' % (self._path, path))    
    def __str__(self):        
        return self._path    
    __repr__ = __str__
    def __call__(self,name):
        return Chain('%s/%s' % (self._path, name))

print(Chain().users('michael').repos.pubilc.owner('jack'))

7.__call__
任何类，只需要定义一个__call__()方法，就可以直接对实例进行调用
__call__()还可以定义参数。对实例进行直接调用就好比对一个函数进行调用一样
怎么判断一个变量是对象还是函数呢？我们需要判断一个对象是否能被调用，能被调用的 对象就是一个Callable对象

8. __getattribute__
1. 无论调用对象的什么属性，包括不存在的属性，都会首先调用“_ getattribute_”方法，注意避免无限递归
2. 只有找不到对象的属性时，才会调用“_ getattr_”方法；
class AboutAttr(object):
    def __init__(self, name):
        self.name = name

    def __getattribute__(self, item):
        try:
            return super(AboutAttr, self).__getattribute__(item)
        except KeyError:
            return 'default'
        except AttributeError as ex:
            return self.__getattr__(item)

    def __getattr__(self, item):
        return 'default'

at = AboutAttr('test')
print(at.name)
print(at.not_exised)

#无限递归
# 为了避免无限递归，应该把获取属性的方法指向一个更高的超类，例如object
class A:
    x = 'a'

    def __getattribute__(self, item):
        print('__getattribute__')
        return self.item
        # return super().__getattribute__(self, item)

a = A()
print(a.x) # ecursionError: maximum recursion depth exceeded
'''


# TODO  枚举类
'''
import re

from enum import Enum
Month = Enum('TEST', ('Jan', 'Feb', 'Mar', 'Apr'))
for name, member in Month.__members__.items():    
    print(name, '=>', member, ',', member.value) 

# Jan => TEST.Jan , 1

class Color(Enum):
    YELLOW =1
    RED =2
    GREEN =3

print(Color.YELLOW)
print(Color.YELLOW.value)
print(Color(1))
print(type(Color(1)))
'''


# TODO  staticmethod classmethod
'''
# 方法不需要访问任何成员，或者只需要显式访问这个类自己的成员。这样的方法不需要额外参数，应当用 @staticmethod装饰。
# 方法不需要访问实例的成员，但需要访问基类或派生类的成员。这时应当用@classmethod装饰。装饰后的方法，其第一个参数不再传入实例，而是传入调用类本身 
# 使用@classmethod时需要注意，由于在继承场景下传入的第一个参数并不一定是这个类本身
# 因此并非所有访问类成员的场景都应该用@classmethod
# 涉及到继承 推荐用classmethod
# https://www.zhihu.com/question/26930016
区别
在定义静态类方法和类方法时，@staticmethod 装饰的静态方法里面，想要访问类属性或调用实例方法，必须需要把类名写上；
而@classmethod装饰的类方法里面，会传一个cls参数，代表本类，这样就能够避免手写类名的硬编码。
在调用静态方法和类方法时，实际上写法都差不多，一般都是通过 类名.静态方法() 或 类名.类方法()。
也可以用实例化对象去调用静态方法和类方法，但为了和实例方法区分，最好还是用类去调用静态方法和类方法。
使用场景
所以，在定义类的时候，
假如不需要用到与类相关的属性或方法时，就用静态方法@staticmethod；
假如需要用到与类相关的属性或方法，然后又想表明这个方法是整个类通用的，而不是对象特异的，就可以使用类方法@classmethod。
# https://stackoverflow.com/questions/12179271/meaning-of-classmethod-and-staticmethod-for-beginner?r=SearchResults&s=2|390.6225

class Date(object):

    def __init__(self, day=0, month=0, year=0):
        self.day = day
        self.month = month
        self.year = year

    @classmethod
    def from_string(cls, date_as_string):
        day, month, year = map(int, date_as_string.split('-'))
        date1 = cls(day, month, year)
        return date1

    @staticmethod
    def is_date_valid(date_as_string):
        day, month, year = map(int, date_as_string.split('-'))
        return day <= 31 and month <= 12 and year <= 3999

date2 = Date.from_string('11-09-2012')
is_date = Date.is_date_valid('11-09-2012')

class Base():
    init = False
    def normal_method(self):  # <bound method Base.normal_method of <__main__.Base object at 0x000002424C298EB0>>
        print('normal method')
        
    @classmethod
    def set_init(cls):     # <bound method Base.set_init of <class '__main__.Base'>>  ,b.set_init 和Base.set_init相同
        cls.init = True    # 传入的是Derived类，给Derived添加了成员,Derived的init和Base的init不是同一个属性，屏蔽掉了
        cls().normal_method()
 
    # @staticmethod   #可以直接用类的对象调用  # <function Base.set_init at 0x000002424C2A60D0> ，b.set_init 和Base.set_init相同
    # def set_init():
    #     Base.init = True

class Derived(Base):
    pass

print('-------------')

Derived.set_init()
print(Derived.init)
print(Base.init)
print(id(Derived.init))
print(id(Base.init))
# del Derived.init
# print(id(Base.init))
# print(id(Derived.init))
'''


# TODO 元类
'''
def fn(self,name='world'):
    print('hello,%s' % name)

Hello = type('hello',(object,),dict(hello=fn))

h = Hello()
h.hello()
print(type(Hello))
print(type(h))
print(type(h.hello))

class ListMetaclass(type):
    def __new__(cls,name,bases,attrs):
        print('%s,%s,%s,%s' %(cls,name,bases,attrs))
        attrs['add'] = lambda self,value:self.append(value)
        # return type.__new__(cls, name, bases, attrs) 等价
        return type(name,bases,attrs)

class MyList(list, metaclass=ListMetaclass):
    pass

L = MyList()
L.add(1)
print(L)


class ModelMetaclass(type):
    def __new__(cls,name,bases,attrs):
        if name == 'Model':
            return type.__new__(cls,name,bases,attrs)
        print('Found model:%s' % name)
        mappings = dict()
        for k,v in attrs.items():
            if isinstance (v,Field):
                print('Found Mapping: %s ==> %s' % (k,v))
                mappings[k] = v
        for k in mappings.keys():
            attrs.pop(k)
        attrs['__mappings__'] = mappings
        attrs['__table__'] = name
        return type.__new__(cls,name,bases,attrs)

class Model(dict,metaclass=ModelMetaclass):
    def __init__(self,**kw):
        super(Model,self).__init__(**kw)
    def __getattr__(self,key):
        try:
            return self[key]
        except KeyError:
            raise AttributeError(r"'Model' object has no attribute '%s'" % key)
    def __setattr__(self,key,value):
        self[key] = value
    def save(self):
        fields = []
        params = []        
        args = []        
        for k, v in self.__mappings__.items():
            fields.append(k)
            params.append('?') 
            args.append(getattr(self, k, None))        
        sql = 'insert into %s (%s) values (%s)' % (self.__table__, ','.join(fields), ','.join(params))        
        print('SQL: %s' % sql)        
        print('ARGS: %s' % str(args)) 

class Field(object):
    def __init__(self,name,column_type):
        self.name = name
        self.column_type = column_type
    def __str__(self):
        return '<%s:%s>' % (self.__class__.__name__,self.name)

class StringField(Field):
    def __init__(self,name):
        super(StringField,self).__init__(name,'varchar(100)')

class IntegerField(Field):
    def __init__(self,name):
        super(IntegerField,self).__init__(name,'bigint')

class User(Model):
    # 定义类的属性到列的映射：
    id = IntegerField('id')
    name = StringField('username')
    email = StringField('email')
    password = StringField('password')

u = User(id=12345, name='Michael', email='test@orm.org', password='my-pwd') 
u.save() 
'''


# TODO 二维数组的正确写法
'''
num_list = [ [0]*5 ]*2  # error
num_list = [ [0] * 5 for i in range(2)]   # right

#  获取list特定元素下标
# 仅仅能获取都第一个匹配的value的下标
a=[72, 56, 76, 84, 80, 88,76]
print(a.index(76))

# 利用enumerate函数
print(list(enumerate(a)))  # tuple 
print [i for i,x in enumerate(a) if x == 76]
'''


# TODO 'and or'
# and中含0，返回0； 均为非0时，返回后一个值， 
2 and 0   # 返回0
2 and 1   # 返回1
1 and 2   # 返回2

# or中， 至少有一个非0时，返回第一个非0,
2 or 0   # 返回2
2 or 1   # 返回2
0 or 1   # 返回1 





























    




