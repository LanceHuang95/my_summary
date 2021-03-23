#******************************************************
#******************************************************
1、global和nonlocal理解
示例1：
a = 10
def func():
    a = 20
    def inner():
        global a
        a = 30
        print(a)
    inner()
    print(a)
print(a)
func()
print(a)
结果是：10 30 20 30
解析：注意global影响的是全局变量，函数内部局部变量不受影响

第1个10是全局变量a=10；

第2个30是局部声明全局变量，

并对全局变量进行了修改a=30；

第3个20是局部变量a并未受inner函数影响，所以仍然是a=20；

第4个30是由于全局变量a受func影响，所以变成了a=30

示例2
a = 10
def func():
    print(a)
    a = 20
    print(a)
func()
结果是：报错

a = 10
def func():
    print(a)
func()
结果是：10

解析：全局变量要用可以，要修改必须用global声明

第1段代码是函数要对全局变量进行修改（a=20），那么python会认为a是一个局部变量，但函数内又未对局部变量a进行定义，所以报错；

第2段代码函数内不声明全局变量，并且不修改全局变量，所以能正常使用。

示例3
a = 10
def func():
    a = 20
    def inner():
        nonlocal a
        a = 30
        print(a)
    inner()
    print(a)
print(a)
func()
print(a)
结果是：10 30 30 10
解析：nonlocal是在函数内部影响

nonlocal声明的变量既不是全局变量，也不是局部变量，而是嵌套函数内变量。所以函数内原局部变量变化了类型。

示例4
a = 10
def func():
    def inner():
        nonlocal a
        a = 30
        print(a)
    inner()
    print(a)
print(a)
func()
print(a)
结果是：报错
解析：global或者nonlocal声明前，必须都要有变量的赋值

 

2、包管理
要导入private、protected属性方法有以下几类：

（1）通过__all__添加，如

#bb.py
__all__=('func','__func','_A')#放入__all__中所有属性均可导入，即使是以下划线开头
class _A():
    def __init__(self,name):
        self.name=name
    def func():
        print "func() is run!"
    def func1():
        print "func1() is run!"
def _func(): #protected方法
    print "_func() is run!"
def __func(): #private方法
    print "__func() is run!"
 
 
#test_bb.py
from bb import *
func()
func() is run!
func1() #func1不在__all__中，无法导入
NameError: name 'func1' is not defined
_func() #_func不在__all__中，无法导入
NameError: name '_func' is not defined
__func()#__func在__all__中，可以导入
__func() is run!
a=_A('zhangsan')#_A在__all__中，可以导入
print a.name
zhangsan

(2)通过明确导入具体的方法

#test_bb.py
from bb import func,_func,__func #可以通过这种方式导入public,protected,private
func()
_func()
__func()
 
func() is run!
_func() is run!
__func() is run!
 
# 虽然_func()、__func()属于"protected , private"权限的，但是如果使用该方式，是可以直接导入访问的

（3）通过使用module.xxx调用

#test_bb.py
import bb #可以通过这种方式导入public,protected,private
bb.func()
bb._func()
bb.__func()
 
func() is run!
_func() is run!
__func() is run!
 
# 可以通过import模块的方式导入模块，然后使用模块.XX的方式访问"public,protected,private"权限的内容

 

3、闭包
（1）示例代码：

def func(a, b):
    def line(x):
        return a * x - b

    return line
    
line = func(2, 3)
print(line(5))
结果是：7
解析：闭包外层参数可以在内存中保留

在这段代码中，外函数func有接收参数 a=2，b=3，内函数line接收参数x=5，在内函数体中计算了a*x-b 即 2×5-3的值作为返回值，外函数返回内函数的引用，这里的引用指的是内函数line在内存中的起始地址，最终调用内函数line()得到返回值7 ；

如果要在内函数中修改外函数的值，那就用nonlocal

def func(a, b):
    def line(x):
        nonlocal a
        a = 3
        return a * x - b
    return line

line = func(2, 3)
print(line(5))
结果是：12
(2)常考理解

def count():
    fs = []
    for i in range(1, 4):
        def f():
             return i*i
        fs.append(f)
    return fs
f1, f2, f3 = count()
f1()
f2()
f3()
结果是：9 9 9
解析：循环体中的临时变量可以在内存中保留（其实和闭包无关）

由于i=3执行完后，继续保留在内存中；当f1()执行时，才真正执行。

如果要实现1 4 9的输出，加入局部变量即可，如

def count():
    fs = []
    for i in range(1, 4):
        def f(a=i):
             return a*a
        fs.append(f)
    return fs
f1, f2, f3 = count()
f1()
f2()
f3()
结果是：1 4 9
真题测试：

# 场景一
def multipliers():
    return [lambda x: i * x for i in range(4)] # 这里是[]
print([m(2) for m in multipliers()])
# 场景二
def multipliers():
    return [lambda x, i=i: i * x for i in range(4)]  # 这里是[]，并且有i=i的赋值运作
print([m(2) for m in multipliers()])
# 场景三
def multipliers():
    return （lambda x: i * x for i in range(4)） # 这里是()
print([m(2) for m in multipliers()])
结果是：
[6,6,6,6]
[0,2,4,6]
[0,2,4,6]
解析：场景三中的（lambda x: i * x for i in range(4)）是生成器表达式，生成器并不是真正的创建列表，而是返回一个生成器对象，等价于yield lambda x:i*x
 

4、类和实例
类定义代码：

class TestClass(object):
    # 类变量，可直接调用
    val1 = 100

    def __init__(self):
        # （实例）属性或成员变量，需要实例后调用
        self.val2 = 200

    # 类的实例方法，需要实例后调用
    def fcn(self, val=400):
        # 类方法的局部变量，不可实例/类访问
        val3 = 300
        self.val4 = val
        self.val5 = 500
        print(self.val5)

    # 类的静态方法，可直接调用
    @staticmethod
    def test():
        print('静态方法test')
    
    # 类的类方法，可直接调用，还可以访问类变量、类方法，但是无法访问（实例）属性
    @classmethod
    def test2(cls):
        print('classmethod方法test')
        print(cls.val1)

    # 私有方法，类外无法调用，即使实例也不行
    def __test3(self):
        print('私有方法test')
        
inst = TestClass()
inst1 = TestClass()
inst2 = TestClass()
示例1：类变量和属性、类方法变量的访问
# 实例的类变量可以访问
print(inst.val1)
# 实例的属性可以访问
print(inst.val2)
# 类的类变量可以直接访问
print(TestClass.val1)
# 类的属性不可以直接访问，非法
print(TestClass.val2)
# 类方法的局部变量不可访问，非法
print(inst.val3)
print(inst.val4)
print(inst.val5)

结果是：100 200 100 报错 报错 报错 报错
示例2：实例对类变量进行修改
# 实例的类变量仅能影响当前实例，无法影响其他实例或者类
inst1.val1 = 1000
print(inst1.val1)
print(TestClass.val1)
print(inst2.val1)
# 类的类变量可以同时影响实例和类
TestClass.val1 = 2000
print(inst2.val1)
print(TestClass.val1)
inst3 = TestClass()
print(inst3.val1)
# 实例属性优先级高于类属性，因此实例属性会屏蔽到类属性
print(inst1.val1)
结果是：1000 100 100 2000 2000 2000 1000
示例3：实例对属性进行修改
# 实例的属性变化仅能影响当前实例，无法影响其他实例或者类
inst1.val2 = 3000
print(inst1.val2)
print(inst2.val2)
# 由于类不能直接访问属性，所以直接修改属性不会有任何作用
TestClass.val2 = 4000
print(inst1.val2)
print(inst2.val2)
print(TestClass.val2)
inst3 = TestClass()
print(inst3.val2)
结果是：3000 200 3000 200 4000 200 
解析：

1、实例可以访问类的所有变量/属性，但是类不能直接访问（实例）属性，即无法直接修改属性；

2、类直接修改类变量会影响所有实例，实例修改类变量或者属性无法影响其他实例

 

4.1 静态方法、类方法、实例方法的访问方式
静态方法test的各种访问方式：

方式一：可以
bc = BaseClass()
bc.test()
方式二：错误
BaseClass.test(BaseClass())
方式三：可以
BaseClass().test()
方法四：可以
BaseClass.test()
类方法test2 的访问方式：

方式一：可以
bc = BaseClass()
bc.test2()
方式二：错误
BaseClass.test2(BaseClass())
方式三：可以
BaseClass().test2()
方法四：可以
BaseClass.test2()
实例方法fcn 的访问方式：

方式一：可以
bc = BaseClass()
bc.fcn()
方式二：可以
BaseClass.fcn(BaseClass())
方式三：可以
BaseClass().fcn()
方法四：错误
BaseClass.fcn()
解析：

其实上面四种方式访问，方式一和三是同一种，即先实例后访问，因此类方法、静态方法、实例方法都是支持的。

只有类方法、静态方法可以用类直接访问，所以方式四都是可以。

方式二我理解是将fcn(BaseClass())中的BaseClass()当作self来处理。

引申：实例方法必须在创建对象后才可以访问

答案：正确

 

4.2 私有变量、公共变量、实例属性的访问方式
原考题测试：

class BaseClass:
    __a = "Base" # 私有类变量

    @classmethod
    def display(cls):
        print(cls.__a)

    @classmethod
    def change(cls, s):
        cls.__a = s

class SubClass(BaseClass):
    __a = "Sub"

bc = BaseClass()
sc = SubClass()
bc.display()
sc.display()
sc.change("Sub")
bc.display()
sc.display()
结果是：Base Base Base Sub
解析：子类无法访问父类的私有属性\私有方法，所以调用父类访问时用的仍是父类的私有属性；
引申：类的私有属性是不是一定无法从外部访问

答案：错误，如上示例代码，可以通过bc._BaseClass__a来访问，但bc.__a是不能访问的。

 

考题变化1：将BaseClass类中定义的类变量是a='Base'（将__a改为a）

class BaseClass:
    a = "Base" # 公共类变量

    @classmethod
    def display(cls):
        print(cls.a)

    @classmethod
    def change(cls, s):
        cls.a = s

class SubClass(BaseClass):
    a = "Sub"

bc = BaseClass()
sc = SubClass()
bc.display()
sc.display()
sc.change("Sub")
bc.display()
sc.display()
结果是：Base Sub Base Sub
解析：当类变量为公共时，子类才能真正访问。
考题变化2：将classmethod变为saticmethod

class BaseClass:
    a = "Base"
    @staticmethod
    def display(cls):
        print(cls.a)
    @staticmethod
    def change(cls, s):
        cls.a = s
class SubClass(BaseClass):
    a = "Sub"
bc = BaseClass()
sc = SubClass()
bc.display()
sc.display()
sc.change("Sub")
bc.display()
sc.display()
结果是：报错，报display函数缺少参数
解析： @staticmethod不需要表示自身对象的self和自身类的cls参数，就跟使用函数一样。 @classmethod也不需要self参数，但第一个参数需要是表示自身类的cls参数。
考题变化3：将BaseClass类中定义的类变量变为实例属性

class BaseClass:
    def __init__(self):
        self.a = 'Base'  # 实例属性

    @classmethod
    def display(cls):
        print(cls.a)

    @classmethod
    def change(cls, s):
        cls.a = s

class SubClass(BaseClass):
    def __init__(self):
        super().__init__()
        self.a = "Sub"

bc = BaseClass()
sc = SubClass()
bc.display()
sc.display()
sc.change("Sub")
bc.display()
sc.display()
结果是：报错
解析：类方法无法访问实例属性。
 

5、json数据解析
（1）python字典类型 转json 对象：json.dumps

（2）json对象转python 字典：json.loads

（3）向文件中写入json数据：json.dump

（4）从文件中读取json数据：json.load

解析：可信工作级真题，关键要理解各自用途

 

6、排序函数
a = [1, 3, 2, 4]
print(a.sort())
print(a)
b = [1, 3, 2, 4]
print(sorted(b))
print(b)

结果是：
None
[1, 2, 3, 4]
[1, 2, 3, 4]
[1, 3, 2, 4]
解析：可信工作级真题

1、sort直接将原列表进行排序，sorted不改变原列表

2、若不加reverse参数，默认为Flase

考题测试：

1、 s="123abc",以下语句打印的结果为s的倒序的是:
A、s.sort(reverse=True)
	print(s)
B、print(s[::-1])
C、s = sorted(s, reverse=True)
	print(s)
D、s1 = ""
	for i in range(len(s)-1, -1, -1):
    	s1 += s[i]
	print(s1)
答案是：BD
解析：
A、sort只能用于list，字符串不支持sort()方法
C、可以实现倒序，但结果是["c","b","a","3","2","1"]，与题目要求不符
 

 

7、装饰器
原考题一测试：

def counter(cls):
    obj_list = []
    def wrapper(*args, **kwargs):
        new_obj = cls(*args, **kwargs)
        obj_list.append(new_obj)
        print('Count: %s' % len(obj_list))
        return new_obj
    return wrapper

@counter
class Test:
    MSG = 'Hello'
    def __init__(self, x, y=[]):
        y.append(x)
        print(Test.MSG, len(y))

Test(1)
Test(2)
答案是：报错
解析：类Test经过装饰器装饰后，其类型变成了函数，函数没有类变量的概念，因此Test.MSG报错。
原考题二测试：

def _print(s):
    print('%s ' % s, end='')

def test1(a, b, c, d, e, f):
    _print(a)
    def inner(func):
        _print(b)
        def wrapper(*args, **kwargs):
            _print(c)
            func(*args, **kwargs)
            _print(d)
        _print(e)
        return wrapper
    _print(f)
    return inner

def test2(func):
    _print('a')
    def wrapper(*args, **kwargs):
        _print('b')
        func(*args, **kwargs)
        _print('c')
    _print('d')
    return wrapper

@test1(1, 2, 3, 4, 5, 6)
@test2
def log(s):
    _print(s)

log('hello')
结果是： 1 6 a d 2 5 3 b hello c 4
解析：
（1）装饰顺序 : 就近原则
被装饰的函数，组装装饰器时，是从下往上装饰
（2）执行顺序 : 就远原则
装饰器调用时是从上往下调用
 

8、函数
def append(value, num_list=[]):
    num_list.append(value)
    return num_list

list1 = append(10)
list2 = append(123, [])
list3 = append('a')
print(list1)
print(list2)
print(list3)
答案是：[10,'a'] [123] [10,'a'] 
解析：
第1次append(10)结束，函数nun_list变量已从初始值变为[10]，list1和num_list的内存地址是一样的，都为[10]
第2次append(123,[])，函数num_list变量读取入参值，变为[]，此时num_list的内存地址与第1次的内存地址是不一样的，所以list1没受list2的影响，仍为[10]
第3次append('a')开始时，由于num_list参数未传，初始值又只能被初始化一次，所以list1、list3、num_list内存地址都是一样的，并且被修改成了[10,'a']
list1 = [1,2,3,4,5]
for item in list1:
   list1.remove(item)
print(list1)
答案是：[2,4]
解析：remove是直接remove对应元素，非索引；list1被移除元素后，对应取值顺序不变（第1个元素遍历后，取第2个元素，以此类推）
 

9、复制、浅拷贝、深拷贝
import copy

A = [1, [2, ], [3, 4, [5, ]], ]

B = A
C = A[::]
D = A.copy()
E = copy.copy(A)
F = copy.deepcopy(A)

A.append(6)
A[1].append(7)
A[2].append(8)
A[2][2].append(9)

print(A)
print(B)
print(C)
print(D)
print(E)
print(F)
结果是：
[1, [2, 7], [3, 4, [5, 9],8], 6]
[1, [2, 7], [3, 4, [5, 9],8], 6]
[1, [2, 7], [3, 4, [5, 9],8],]
[1, [2, 7], [3, 4, [5, 9],8],]
[1, [2, 7], [3, 4, [5, 9],8],]
[1, [2, ], [3, 4, [5, ]], ]
解析：

A和B地址完全相同，属于复制

CDE相同（A[::]、A.copy()、copy.copy(A)均是A的浅拷贝 ），copy可变对象时只新建第一层的元素，嵌套的可变对象还是原来地址

deepcopy是全部新建地址，与原地址无关

引申：https://blog.csdn.net/yuzipeng/article/details/106006521

（1）可变对象：list/dict/set

（2）不可变对象：int/str/float/tuple

考题测试1：

x = 1
y = [1]

def foo():
    x = 2
    y.append(2)

foo()
print(x, y)
结果是：1 [1,2]
解析：python中的不可变类型的全局变量如int a=1,str b='hello', 若需要修改必须加global申明, 而全局变量是可变类型的,如list, dict ,则直接修改list.append(),dict[x]=xx
考题测试2：

s = 'hello'
item = [s]
s = 'world'
print(item)

items_1 = item * 3
items_1[0] = 'world'
print(items_1)

items_2 = [item] * 3
items_2[0][0] = 'world'
print(items_2)
答案是：
['hello']
['world', 'hello', 'hello']
[['world'], ['world'], ['world']]
解析：关键要理解item_1和item_2之间的元素差异
（1）可变对象与不可变对象内存地址的变化
item_1[0]是字符串，是不可变对象，当第1个元素值变化后，其内存地址也发生改变；而第2、3个元素内存地址不变，即值也不变
item_2[0]是列表，是可变对象，当第1个值变化后，内存地址没有变，变的是原内存地址对应的内容，导致第2、3个元素值也一起改变
（2）item*3 得到的3个元素内存地址是一样的
 

10、基本数据结构
1、下列哪种说法是错误的 （A） A、判断对象是否为空，可以采用如下函数：

def is_blank(obj):
    if not obj:
        return True
    else:
        return False
B、表达式3>2==2是合法的表达式，且该表达式的值为True C、空列表对象的布尔值是 False D、0+0j的布尔值是 False

解析：

选项A：比如0不是空值，但是is_blank(0)仍返回True

选项B：3>2==2等价于3>2 and 2==2

 

11、字符串各种查找方法
（1）s.find(str)如果找不到目标，则返回-1

（2）s.index(str)如果找不到目标，则报异常

（3）s.isdigit() 如果判断失败，则返回False。 # isXX类方法都是这样的结果

（4）re.match(pattern,s) 如果匹配失败，则返回None

（5）re.search(pattern,s) 如果搜索失败，则返回None

（6）re.findall(pattern,s) 如果找不到目标，则返回[]
