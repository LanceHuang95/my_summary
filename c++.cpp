day1

1.双冒号::作用域运算符 
int a =200;
int main()
{
    int a =100
    cout<<a<<::a<<endl; //100 200  全局作用域
}

2.namespace 
    1.命名空间解决命名冲突，可以放 函数 类 变量
    2.命名空间必须定义在全局作用域下，不能放在函数内
    3.命名空间可以嵌套命名空间
    4.命名空间是开放的，可以随时在原空间上添加内容
    5.无名、匿名命名空间 相当于写了 static int m_C ; static int m_D;只能在当前文件内使用
    6.命名空间可以起别名 namespace A = B;  A::a,B::a 

3.using声明 using A::a  编译器又有就近原则(注意二义性)
  using 编译指令  using namespace A 

4.C++对C语言增强
a.全局变量检测增强
b.函数检测增强:  参数类型检测 返回值检测 传参个数检测	
c.类型转换检测增强  malloc返回void* ，C中可以不用强转，C++必须强转
d.struct增强  C中不许有函数 C++可以   使用C必须加关键字 struct ，C++可以不加
e.bool数据类型增强  C没有 C++有  true 真  false假  sizeof  1
f.三目运算符增强  C中返回的是值  C++中返回的是变量
g.const增强  C语言中const是伪常量，可以通过指针修改  C++中const会放入到符号表中  C语言中const默认是外部链接，C++中const默认是内部链接  
const分配内存情况  //会分配内存即可通过指针间接修改
  对变量取地址，会分配临时内存  // const int m_A = 10;int * p = (int*)&m_A; //会分配临时内存 注意：m_A为const int *类型
  extern关键字下的const会分配内存
  用普通变量初始化const变量   int a = 10; const int b = a; //会分配内存
  自定义数据类型会分配内存

尽量用const代替define define宏没有作用域概念  define宏常量没有类型

5.引用基本语法(必须引用合法内存空间，不能直接引用数值)
  Type &别名 = 原名
  引用必须初始化   //int &a; 必须初始化
  一旦初始化后 不能修改 int &b = a; 引用初始化后不可以修改了   int c = 20;b = c; //这是赋值，不是修改！！！
  对数组建立引用  int arr[10];int(&pArr)[10] = arr;     typedef int(ARRAYREF)[10]; ARRAYREF & pArr2 = arr;
  注意事项，不要返回局部变量的引用  static生命周期为整个程序运行周期，可见性为当前函数
  如果函数返回值是引用，那么函数的调用可以作为左值  函数 int& doWork2()；doWork2() = 1000
  引用的本质 就是一个指针常量

6.指针的引用:用一级指针引用 可以代替二级指针

void allocatMemory(Person ** p) // **p 具体的Person对象  *p 对象的指针   p 指针的指针
{
	*p = (Person *)malloc(sizeof(Person));

	(*p)->m_Age = 100;
}

void test01()
{
	Person * p = NULL;
	allocatMemory(&p);
	cout <<  "p的年龄： " <<p->m_Age << endl;
}

//利用指针引用开辟空间
void allocatMemoryByRef(Person* &p)
{
	p = (Person*)malloc(sizeof(Person));
	p->m_Age = 1000;
}

void test02()
{
	Person * p = NULL;
	allocatMemoryByRef(p);
	cout << "p的年龄：" << p->m_Age << endl;

7.常量引用   使用场景 修饰形参为只读   const int &a = 10;会分配内存，可间接修改  //相当于 int temp =10; const int &a =temp;

8.内联函数 ： 声明和实现时都需要加inline关键字   类内部的成员函数默认加inline
  注意：不能存在任何形式的循环语句   	不能对函数进行取址操作

9.函数默认参数(c语言中没有) ：如果一个位置有了默认参数，从该位置起，右边的参数都必须有默认参数
  函数声明和实现只能有一个有默认值    占位参数(只有类型，无变量)也可以有默认参数

10.函数重载： 必须在同一个作用域 函数参数 个数 或顺序 或类型 不同;返回值不作为重载条件
  注意：函数重载和函数默认参数二义性问题 
  void fun(int a,int b=10) ;void fun(int a) ;  fun(10)//无法区分

void func3(int &a) //引用必须要引合法的内存空间
{
	cout << " int &a" << endl;
}

void func3(const int &a)  //const也是可以作为重载的条件  int tmp = 10; const int &a = tmp;
{
	cout << "const int &a" << endl;
}

void test03()
{
	//int a = 10;
	func3(10);
}

11.c语言写的接口能被c++调用 如下写：

#ifdef __cplusplus
extern "c"{
#endif

  函数

#ifdef __cplusplus
}
#endif

c++导入相应头文件


day2 类 继承

1.构造函数
  无参构造写法 ：Person p1;  注意不能写成 Person p1();//编译器认为这是函数声明
  有参构造写法： Person p2(10); 或者 Person p2 =Person（10）  //Person（10）是匿名对象 执行当前后会析构
  隐式类型转换： Person p1 =100; 相当于调用 Person p1 =Person(100);

2.拷贝构造函数
  Person (const Person & p);
  写法: Person p1(p2);或者Person p1 =Person(p2);
  注意：不能用拷贝构造函数初始化匿名对象
    如果写成左值 Person(p1) 等价于 Person p1;
    写成右值 Person p1 =Person(p2) 可以

3.调用时机： 
  用已经创建好的对象初始化新的对象  
  以值传递方式给函数参数传值  
  以值的方式返回局部对象

4.构造函数的调用规则
  如果提供了有参的构造，那么系统就不会提供默认的构造了，但是会提供拷贝构造
  如果提供了拷贝构造函数，那么系统就不会提供其他的构造函数了

5.explicit关键字作用：防止构造函数中的隐式类型转换

6.new运算符 
  通过new开辟数组 一定会调用默认构造函数,所以一定要提供默认构造
	Person * pArray = new Person[10];
	Person pArray2[2] = { Person(1), Person(2) }; //在栈上开辟数组，可以指定有参构造

  void *p = new Person(10); 
	//当用void* 接受new出来的指针 ，会出现释放的问题
	delete p;
	//无法释放p ，所以避免这种写法

  //malloc会调用构造吗？ 不会  new会调用构造

7.静态成员变量和静态成员函数
  1.静态成员变量
    编译阶段分配内存(早于运行)
    所有该类的对象共享数据
    通过对象访问 也可以直接通过类名访问
    类内声明 类外初始化
  2.静态成员函数
    可以访问静态成员变量，不可以访问普通成员变量
    普通成员函数都可以访问
    静态成员函数也有权限
    通过对象访问 也可以直接通过类名访问
8.单例模式
  目的：让类只有一个实例，实例一般不需要自己释放
  写法：将默认构造和拷贝构造 私有化(private)
       内部维护一个对象指针
       私有化唯一指针
       对外提供getInstance方法来访问这个指针

class Printer{
public:
	static Printer* getInstance(){ return pPrinter;}
	void PrintText(string text)
  {
		cout << "打印内容:" << text << endl;
		cout << "已打印次数:" << mTimes << endl;
		cout << "--------------" << endl;
		mTimes++;
	}
private:
	Printer(){ mTimes = 0; }
	Printer(const Printer&){}
private:
	static Printer* pPrinter;
	int mTimes;
};

Printer* Printer::pPrinter = new Printer;

void test()
{
	Printer* printer = Printer::getInstance();
	printer->PrintText("离职报告!");
	printer->PrintText("入职合同!");
	printer->PrintText("提交代码!");
}

9.类的成员变量和成员函数分开存储 空类的大小为1  	只有非静态成员属性才属于对象身上，成员函数代码是类的对象共用的(通过this指针区分)

10.this指针 指针永远指向当前对象 非静态成员函数才有this指针  Type * const this //指针指向不能变

11.空指针访问成员函数
  如果成员函数没用到this,空指针可以直接访问
  如果成员函数用到this指针，注意if判断 this 是否为空

12.常函数常对象
  1.常函数
    void fun() const {}
    常函数修饰this指针 const Type * const this  不能改变this指针执行的值
  2.常对象
    const Person P1
    常对象不可以调用普通的成员函数 可以调用常函数
    用 mutable 修饰的成员变量在常函数中能修改

13.友元 friend
  1.全局函数做友元函数: 全局函数写到 类中做声明，并在前面加friend
  2.整个类做友元类 ：类中写 friend class 类名     友元是单向的，不可传递
  3.单个成员函数做友元函数： friend void Person::fun();

14.运算符的重载
  1. 返回类型 operator重载的运算符(参数){};
  2.在class内重载 和 全局函数重载 参数个数
  3.<<重载 2.4	写到全局函数中 
  ostream& operator<< ( ostream & cout, Person & p1  ) {}
  如果重载时候想访问 p1的私有成员，那么全局函数要做Person的友元函数
  4.重载++运算符 Type & operator++() 前置 (注意返回引用)  Type operator++(int) 后置(返回值)
  	前置理念 先++ 后返回自身   后置理念 先保存住原有值  内部++ 返回临时数据
  5.智能指针实现
class Person
{
public:
	Person(int age){	this->m_Age = age;}
  void showAge(){cout << "年龄为：" << this->m_Age << endl;}
	~Person(){cout << "Person的析构调用" << endl;}
  int m_Agenew
};

//智能指针
//用来托管自定义类型的对象，让对象进行自动的释放
class smartPointer
{
public:
	smartPointer(Person * person){	this->person = person;}
	//重载->让智能指针对象 想Person *p一样去使用
	Person * operator->(){	return this->person;}
	//重载 * 
	Person& operator*(){return *this->person;}
	~smartPointer(){
		cout << "智能指针析构了" << endl;
		if (this->person !=NULL)
		{
			delete this->person;
			this->person = NULL;
		}
	}
private:
	Person * person;
};

void test01()
{
	//Person p1(10); //自动析构
	//Person * p1 = new Person(10);
	//p1->showAge();
//	delete p1;
	smartPointer sp(new Person(10)); //sp开辟到了栈上，自动释放
	sp->showAge(); // sp->->showAge(); 编译器优化了 写法
	(*sp).showAge();
}

  6.如果类中有指向堆区的指针，就可能出现深浅拷贝的问题所以要重载 = 运算符 如果想链式编程 return*this 
  7.[]运算符重载 返回数组索引的引用  int & operator[](int index)  return this->pAddress[index]
  8.总结：
    	=, [], () 和 -> 操作符只能通过成员函数进行重载 
      << 和 >>只能通过全局函数配合友元函数进行重载 
      不要重载 && 和 || 操作符，因为无法实现短路规则
15.函数调用运算符重载  	
    仿函数 重载()运算符  对象() 看似像函数调用  MyAdd()   匿名对象
class MyPrint
{
public:
	void operator()( string text)
	{cout << text << endl;}
};
void test01()
{
	MyPrint myPrint;
	myPrint("hello world1111"); // 仿函数
}

class MyAdd
{
public:
	int operator()(int v1,int v2)
	{	return v1 + v2;}
};
void test02()
{
	//MyAdd myAdd;
	//cout << myAdd(1, 1) << endl;

	cout << MyAdd()(1, 1) << endl; //匿名对象
}

16.继承中的对象模型 
  1.子类会继承父类中所有的内容 ，包括了私有属性,只是我们访问不到，编译器给隐藏了
  2.cl /d1 reportSingleClassLayout类名 文件名
  3.继承中的构造和析构顺序 子类创建对象时，先调用父类的构造，然后调用自身构造  析构顺序与构造顺序相反
  4.子类是不会继承父类的构造函数和析构函数 补充内容，如果父类中没有合适默认构造，那么子类可以利用初始化列表的方式

17.继承中的同名处理
  1.成员属性 先直接调用子类，如果调用父类，需要作用域
  2.成员函数 直接调用子类函数 父类函数所有版本会被隐藏 除非显式作用域运算符调用

18.继承中静态成员的处理
  1.类似非静态成员函数处理
  2.如果想访问父类中的成员，加作用域即可

19.多继承的概念以及问题 class A : public B1, public B2,….
  1.引发二义性问题
  2.想解决二义性问题，就需要通过作用域来进行区分
  3.菱形继承问题以及解决
  4.解决问题利用虚基类
  5.sheepTuo 内部结构 vbptr 虚基类指针 指向一张 虚基类表 通过表找到偏移量 找到共有的数据 内部工作原理 （可以不掌握）

day03 多态 模板

1.静态联编和动态联编
  a.多态分类：静态多态（函数重载） 动态多态（虚函数 继承关系）
  b.静态联编： 地址早绑定 编译阶段
  c.动态联编： 地址晚绑定 运行阶段
  d.多态：父类的指针或引用指向子类对象

2.多态原理解析
  1.父类有了虚函数后，内部结构发生变化 内部多了 vfprt 虚函数表指针指向vftable虚函数表
  2.子类进行继承会继承vfptr vftable 构造函数中会将虚函数指针 指向自己的虚函数表
  3.如果发生重写，会替换虚函数表中原有的父类的函数 改为子类当前的函数
  4. ((void(*)())  (*(int*)*(int*)animal))();
  5.开发有原则  开闭原则  --  对扩展开放  对修改关闭
  6.利用多态实现 – 利于后期扩展，结构性非常好，可读性高， 效率稍微低，发生多态内部结构复杂

3.抽象类和纯虚函数
  1.纯虚函数写法： virtual void fun() =0;
  2.抽象类 ：不可实例化对象
  3.如果继承了抽象类，必须重写抽象类中的纯虚函数、

4.虚析构和纯虚析构
  1.虚析构 virtual ~Person(){}
  2.用途：通过父类指针指向子类对象释放时 不干净导致的问题
  3.纯虚析构函数： virtual ~Person() =0
  4.纯虚析构函数 类内声明 类外实现 如果出现纯虚析构函数，该类为抽象类 不可实例化

5.向上类型转换(子类转基类，安全)和向下类型转换(基类转子类，不安全)  如果发生多态 转换总是安全的

6.函数模板 
  1.template <class/typename T> 
    void myswap(T &a ,T &b)
    myswap（a,b） 自动类型推导  按照a b的类型 来替换T
    myswap<int>(a,b) 显示指定类型
  2.函数模板与普通函数的区别以及调用规则
    1.区别 普通函数可以进行隐式类型转换  模板不可以
    2.调用规则
	    c++编译器优先考虑普通函数
	    可以通过空模板实参列表的语法限定编译器只能通过模板匹配
	    函数模板可以像普通函数那样可以被重载
      如果函数模板可以产生一个更好的匹配，那么选择模板
  3.模板机制
      模板并不是万能的，不能通用所有的数据类型
      模板不能直接调用，生成后的模板函数才可以调用
      二次编译，第一次对模板进行编译，第二次对替换T类型后的代码进行二次编译
  4.模板局限性
      模板不能解决所有的类型
      如果出现不能解决的类型，可以通过具体化来解决问题
      template<> 返回值 函数名<具体类型>（参数）

7.类模板
  1.template<class T1, calss T2>
    class Person
    {
      T1 a;
      T2 b;
    };
  2.与函数模板区别
      可以有默认类型参数  函数模板不能有默认类型参数
      不会进行自动类型推导 函数模板会自动类型推导
  3.类模板中的成员函数 一开始不会创建出来，而是在运行时才去创建

8.类模板做函数的参数方式
  1.显示指定类型  void doWork( Person<string ,int> & p ) 
  2.参数模板化    template<class T1 ,class T2>
                void doWork2(Person<T1, T2> & p)
  3.整体模板化    template<class T>
                void doWork3(T&p)

9.类模板遇到继承
  1.基类如果是模板类，必须让子类告诉编译器 基类中的T到底是什么类型
    如果不告诉，那么无法分配内存，编译不过
    利用参数列表class Child :public Base<int>

10.类模板的分文件编写问题以及解决
  1.类模板碰到友元函数.h .cpp分别写声明和实现
  2.但是由于 类模板的成员函数运行阶段才去创建，导致包含.h头文件，不会创建函数的实现，无法解析外部命令
  3.解决方案  保护 .cpp文件 （不推荐）
  4.不要进行分文件编写，写到同一个文件中，进行声明和实现，后缀名改为.h

11.类模板碰到友元函数
  1.友元函数类内实现
    friend void printPerson( Person<T1 ,T2> & p ) 
  2.友元函数类外实现
   类内声明 friend void printPerson<>(Person<T1, T2> & p); //没有<>普通函数 声明  加上 <>模板函数声明
   让编译器提前看到printPerson声明  template<class T1, class T2>void printPerson(Person<T1, T2> & p);
   让编译器看到Person类声明 template<class T1, class T2> class Person;


day04 类型转换 异常 文件

1.类型转换
  1.静态转换 static_cast  static_cast< 目标类型>（原始数据）
      可以进行基础数据类型转换  父与子类型转换  没有父子关系的自定义类型不可以转换
  2.动态转换 dynamic_cast 不可以转换基础数据类型  父子之间可以转换 父转子,不可以 子转父,可以  发生多态,都可以
  3.常量转换 const_cast  不能对非指针或者非引用进行转换
  4.重新解释转换 reinterpret_cast  最不安全，最鸡肋 不推荐

2.异常
  1. try{可能出现异常的语句} catch(捕获类型) ...代表 所有其他类型  
      如果不想处理异常，继续向上抛出 throw 
      如果没有任何处理异常的地方，那么成员调用terminate函数，中断程序
  2.自定义异常类 ，可以抛出自定义的对象  ，捕获自定义的异常
  3.栈解旋 从try开始到 throw 抛出异常之前  所有栈上的对象 都会被释放 这个过程称为栈解旋 栈上对象构造顺序与析构顺序相反

3.异常的接口声明 如果想抛出特定的类型异常 ，可以利用异常的接口声明
    void func() throw ( int) 只能抛出 int类型
    throw() 不抛出任何类型异常

4.异常变量生命周期
  如果  MyException e，会多开销一份数据 ,调用拷贝构造
  如果  MyExcepiton *e   ， 不new提前释放对象 new 自己管理delete
  推荐  MyException &e  容易些 而且 就一份数据

5.异常的多态使用 利用多态来实现 printError同一个接口调用 抛出不同的错误对象，提示不同错误

6. 使用系统标准异常
    #incldue <stdexcept>
    throw out_of_range（”aaa”） 。。。
    catch(out_of_range & e)  cout  <<  e.what();
7.编写自己的异常类
    自己的异常类 需要继承于  exception
    重写  虚析构   what（）
    内部维护以错误信息 字符串
    构造时候传入 错误信息字符串，what返回这个字符串
    string 转 char *   .c_str();

8.标准的输入流
  1.cin.get 缓冲区中读取一个字符
    cin.get(两个参数) 不读换行符
    cin.getline () 读取换行 并且扔掉
    cin.ignore 忽略 （N） N代表忽略字符数 
    cin.peek 偷窥   偷看1个字符然后放回去
    cin.putback  放回 把字符放回缓冲区
  2.输入流案例
    判断用户输入的是字符串还是数字 利用偷窥 或者 放回
    让用户输入指定范围内的数字，如果不正确 重新输入
  3.cin.fail() 看标志位  0正常 1不正常
    cin.clear()重置标志位
    cin.syne() 清空缓冲区
  4.标准输出流
    流对象的成员函数  
    cout.width(20);
    cout.fill('*');
    cout.setf(ios::left); //设置格式  输入内容做对齐
    cout.unsetf(ios::dec); //卸载十进制
    cout.setf(ios::hex); //安装16进制
    cout.setf(ios::showbase); // 强制输出整数基数  0  0x
    cout.unsetf(ios::hex);
    cout.setf(ios::oct);
    控制符  头文件 iomanip
	  cout << setw(20)
		<< setfill('~')
		<< setiosflags(ios::showbase) //基数
		<< setiosflags(ios::left) //左对齐
		<< hex // 十六进制
		<< number
  5.文件操作
  写文件 ofstream  ofs  open 指定打开方  isopen 判断是否打开成功  ofs << “数据” ofs.close
  读操作 ifstream  ifs  指定打开方式 ios：：in isopen判断是否打开成功 三种方式读取数据

day5 STL

1.string容器
    1.构造 、 赋值 assign 
    2.对字符存取 [] at区别  []访问越界直接挂  at 抛出异常 out_of_range
    3.substr  配合 find查找 邮件用户名
    4.char *  string 互转 char * 隐式转换成string 反之不可以  c_str 转大写 toupper  
    5.find  如果找不到  返回 -1 找到返回第一次出现的位置
2.vector容器  单端数组、动态数组
    1.构造、赋值、 大小 size 重置大小 resize 容量 capacity  是否为空 empty 交换 swap
    2.巧用swap收缩空间 
      vector<int>(v).swap(v);   vector<int>(v)匿名对象，用完被释放 v本身是一个vector
    3.reserve(int len) 预留空间 容器预留len个元素长度，预留位置不初始化，元素不可访问，开辟大容量数组时使用此方法可减少 调整开辟的空间的次数
      void test04()
      {
        vector<int>v;
        v.reserve(100000); //预留出空间
        int * p = NULL;
        int num = 0;
        for (int i = 0; i < 100000;i++)
        {
          v.push_back(i);
          if (p!=&v[0])
          {
            p = &v[0];
            num++;
          }
        }
        cout << num << endl;
        // 开辟100000数据用了多少次
      }
    4.insert 插入（迭代器） erase删除 （迭代器） clear（）清空容器
    5.pop_back 尾删 front 第一个数据  back最后一个数据
    6.逆序遍历 reverse_iterator    rbegin rend
    7.如和区分迭代器是否支持随机访问 
        vector<int>::iterator itBegin = v.begin();
        itBegin = itBegin + 3;
        //如果上述写法不报错，这个迭代器是随机访问迭代器  
    8.vector的插入操作可能造成重新分配内存空间，导致原有的迭代器全部失效
3.deque容器 双端数组  没有容量 
    1.API  赋值、构造、大小、交换、插入 、删除
    2.头部删除 头部插入 pop_front push_front
    3.中迭代器  iterator 普通  reverse_iterator 逆序迭代器  const_iterator只读迭代器
    4.排序 sort 引用头文件 algorithm  
    5.sort(d.begin(),d.end()) 从小到大 sort(d.begin(),d.end(),函数指针/防函数/lambda表达式)
    eg.  bool myCompare(int v1, int v2){return v1 > v2; }   sort(d.begin(),d.end(),myCompare);

4.stack栈容器 top push pop size empty

5.queue队列容器 front back push pop size empty

6.list容器：双向循环链表 迭代器是不支持随机访问的
  1.赋值、构造、大小、为空、删除 、添加
  2.移除 remove( 10 )  删除容器中所有与10 匹配的元素
  3.反转排序 reverse 反转  排序 成员函数 sort   默认排序 从小到大  自定义数据类型，必须指定排序规则 高级  remove删除list容器中自定义数据类型

7.set关联式容器：红黑树
  1.只有key值，按照key，插入数据自动排序 
  2.insert 插入值，erase  参数可以传值 或者 迭代器
  3.find（） 返回值 迭代器  找不到返回的  end()
  4.count 计数  对于set而言  结果 就是 0 或者1 
  5.lower_bound(keyElem);//返回第一个key>=keyElem元素的迭代器。
    upper_bound(keyElem);//返回第一个key>keyElem元素的迭代器。
    equal_range(keyElem);//返回容器中key与keyElem相等的上下限的两个迭代器。
  6.对组 pair 第一个值 first  第二个值 second 默认括号 make_pair()
  7.set插入返回值是 对组  < 迭代器， 是否成功标示>
  8.指定set排序规则，利用仿函数  set插入自定义数据类型 

8.map容器：每个元素 都是一个pair
  1.对于map而言 key是不可以重复 multimap可以
  2.4中插入方式  
      map<int, string> mapStu;
    // 第一种 通过pair的方式插入对象
    mapStu.insert(pair<int, string>(3, "小张"));
    // 第二种 通过pair的方式插入对象
    mapStu.inset(make_pair(-1, "校长"));
    // 第三种 通过value_type的方式插入对象
    mapStu.insert(map<int, string>::value_type(1, "小李"));
    // 第四种 通过数组的方式插入值
    mapStu[3] = "小刘";
    mapStu[5] = "小王";
  3.count 统计 map 0 或1  multimap可能大于1
  4.排序规则自己指定

day06 算法 适配器

1.函数对象（仿函数）
  1.重载 () 所以函数的对象 使用（）像函数调用 是类 而不是普通的函数
  2.内部记录状态
  3.作为类型 与模板进行配合使用

2.谓词 普通函数或者仿函数返回值 bool类型
  1.一元 一个参数 二元 两个参数
  2.一元 查找 大于20的数字   find_if 返回迭代器
  3.二元 排序

3.内建函数对象 取反 加法 大于 greater<int>()

4.适配器
  a.
    1.函数适配器 eg.0~9 加起始值 进行输出 用户提供起始值
    1.bind2nd  绑定
    2.继承  binary_function<参数类型1，参数类型2，返回值类型>
    3.const修饰 operator()  
    4.取反适配器  not1  一元 找出小于5   not2 二元  排序  not2(  less<int>() ) 从大到小 相当于  greater<int>()
  b.
    1.普通函数指针适配   ptr_fun 
  c.
    1.成员函数适配
    //如果容器存放的是对象指针，  那么用mem_fun
    //如果容器中存放的是对象实体，那么用mem_fun_ref	
5.常用遍历算法
  1.for_each  可有有返回值  可以绑定参数进行输出
  2.transform  将容器中的数据进行搬运到另一个容器中  注意：目标容器需要开辟空间
  3.常用查找算法
      find  按值查找 Person
      find_if 按条件查找 Person*
      adjacent_find算法 查找相邻重复元素 返回第一个重复元素的迭代器位置
      binary_search算法 二分查找法 必须容器是有序序列
      count 和count_if
  4.常用排序算法
      merge算法 容器元素合并，并存储到另一容器中，两容器要有序，并且顺序一致
      sort 排序
      random_shuffle 洗牌  自己提供随机种子
      reverse反转
5.常用的拷贝和替换算法
    copy复制
    replace  replace_if 替换
    swap 交换
6.常用算数生成算法
    头文件 numeric 
    accumulate 累加
    fill 填充
7.常用集合算法
    交集 set_intersection
    并集 set_union
    差集 set_difference



























    




