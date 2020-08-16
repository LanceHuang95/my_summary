c 提高


第一天： 类型 内存区

1.typedef
typedef struct Person
{
    char * p;
    int age;
}MyPerson


char * p1,p2  //p1为char*,p2为char类型
//查看类型： cout<<typeid(p1).name<<endl;
typedef char * pCHAR;
pCHAR p1,p2;


typedef longlong Mytype  //提高程序可移植性


2.void 不能定义变量
void * 主要用于数据结构的封装

3.sizeof 返回实际变量占用的大小，而不只是它用到的空间
#pragma pack(1)  对齐模式

4.unsigned与有符号类型运算：结果为unsigned
当数组名作为函数参数时，在函数内部，形参也就是个指针，所以不再返回数组的大小

5.全局区/静态区/常量区（1.字符串常量char *p="hello" (某些编译器仍可以修改，最好加const修饰) 2.const修饰的全局变量）

6.栈区：不要返回局部变量的地址

8.只要是连续的内存空间，都能使用下标方式访问内存
用完堆内存，一定要释放
定义变量一定要初始化

9. 理解下面的内存

void allocateSapce(char ** p)
{
    char * temp =malloc(l00);
    memset(temp,0,100);
    strcpy(temp,"helloworld");

    *p =temp;
    //注意理解 p=temp
}

void test03()
{
    char * p =null;
    allocateSapce(&p);
    printf("p=%s\n",p);
}

10.const全局变量放在常量区 直接修改间接修改都不行  
注意： 以下代码能通过编译，运行时报错
const int a=100; 
void test()
{
    int * b =（int*) &a;//&a类型为 const int *
    *p=200
}

const局部变量放在栈区，可以简介修改


第二天：函数 栈 指针

1.宏函数(不是函数，只是预处理进行简单文本替换，频繁使用且简单短小的场合使用)一定场景下比函数效率高  #define MYADD(x,y)  ((x)+(y))
2.函数调用过程所需要的信息一般包括以下几个方面：
	函数的返回地址；
	函数的参数；
	临时变量；
	保存的上下文：包括在函数调用前后需要保持不变的寄存器。
函数 压栈  跳转 返回

函数参数的传递顺序和方式
栈的维护方式(清理)


内存生长方向：小端模式(高位字节放高地址，低位字节放低地址)

3.
//使用offsetof 引入头文件 #include<stddef.h>
struct Person
{
	int a;
	char b;
	char buf[64];
	int d;
};

void test02()
{
	struct Person p = { 10, 'a', "hello world!", 100 };
	char b;
	printf("a off:%d\n", offsetof(struct Person,b));
    printf("%d\n",*(int *)((char *)&p+offsetof(struct Person,d))); //output: 100

}

4.NULL指针，它作为一个特殊的指针变量，表示不指向任何东西  对一个NULL指针因引用是一个非法的操作

5.数组名作函数参数会退化为指向数组首元素的指针  
函数形参（首元素的指针，数组长度）
char * str[] ={"aaa","bbb","ccc"};
printArray(str，sizeof(str)/sizeof(char*))；

void printArray(char ** arr,int len);

6.字符串拷贝 3种方式
void copyString01(char *dst, const char *source)
{
	int len = strlen(source);
	for (int i = 0; i < len; ++i)
		dst[i] = source[i];
	dst[len] = '\0';
}

void copyString02(char *dst, const char *source)
{
	while (*source != '\0')
	{
		*dst = *source;
		++dst;
		++source;
	}
	*dst = '\0';
}

void copyString03(char *dst, const char *source)
{
	if (NULL == dst)
		return;
	if (NULL == source)
		return;
	while (*dst++ = *source++);
}

7.字符串反转
void reverseString(char *str)
{
	if (NULL == str)
	{
		return;
	}
	int len = strlen(str);
//数组方式
#if flag == 0
	int start = 0;
	int end = len - 1;
	while (start < end)
	{
		char temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		++start;
		--end;
	}
#else
//指针方式
	char *pStart = str;
	char *pEnd = str + len - 1;
	while (pStart < pEnd)
	{
		char temp = *pStart;
		*pStart = *pEnd;
		*pEnd = temp;
		++pStart;
		--pEnd;
	}
#endif
}

8. calloc  realoc

9.
%*s或%*d	跳过数据
%[width]s	读指定宽度的数据
%[a-z]	匹配a到z中任意字符(尽可能多的匹配)
%[aBc]	匹配a、B、c中一员，贪婪性
%[^a] 	匹配非a的任意字符，贪婪性
%[^a-z]	表示读取除a-z以外的所有字符

10. 指针易错点
    越界
    malloc 修改原指针指向
    返回局部变量地址
    同一内存释放多次

11. 位运算

    位运算都是对于补码而言
    int a =10;
    (a&1)判断奇偶性 
    (a&0)置为0
    (a|1)置为1
    异或(^):两位不等则为1(半加器)：A^B=R;R^B=A;R^A=B;A^B^B=A 
    //可用于交换两个变量
    a=a^b;
    b=a^b;
    a=a^b;

    左移：a<<b；// a的值为a=a*2^b
    右移：对于unsigned类型，使用0填充左端空出的位。对于有符号类型，结果依赖于机器。空出的位可能用0填充，或者使用符号(最左端)位的副本填充。


第三天：数组 结构

1.数组名在以下2种情况不是：指向首元素的指针 a.sizeof 2.对数组名取地址
  数组名是常量指针，不能将数组名指向其他指针

2. 定义一个指向数组的指针
    1.先定义数组类型，再定义数组指针类型

    typedef int (ARRAY_TYPE) [5];
    ARRAY_TYPE myarray;
    ARRAY_TYPE * pArray =&myarray  //对数组名取地址代表指向整个数组的指针
    *pArray类型就是数组名，指向首元素类型的指针

    *(*pArray+1)为 myarray[1]

    2.直接定义数组指针类型
     typedef int (* ARRAY_POINTER) [5];
     ARRAY_POINTER pArr =&arr;
    3.直接定义数组指针变量
     int(*pArr)[5]= &arr; 

    4.二维数组第i行j列 ：*(*(arr+i)+j)

//遍历二维数组
void printBiArray(int(*parr)[3], int len1, int len2) 
{
	for (int i = 0; i < len1; ++i)
	{
		for (int j = 0; j < len2; ++j)
		{
			//printf("%d ", *(*(parr + i) + j) );
			printf("%d ", parr[i][j]);
		}
	}
}
/*void printBiArray(int parr[][3], int len1, int len2)*/
printBiArray(arr,3,3);


3.选择排序
 void SelectSort(int arr[],int len)
 {
    for(int i=0;i<len;i++)
    {
        int min =i;
        for(int j=i+1;j<len;j++)
        {
            if(arr[j]<arr[min])
            {
                min =j;
            }
        }

        //里层循环执行完交换
        if(min != i)
        {
            int temp =arr[min];
            arr[min] =arr[i];
            arr[i]=temp;
        }
    }
 }


4.如果结构体内部有指针，且指针指向堆空间，如果发生赋值行为，就会产生两个问题：
    1.同一块内存空间被释放两次
    2.内存泄漏
//手动拷贝如下：
    if (teacher1.name != NULL)
	{
		free(teacher1.name);
		teacher1.name = NULL;
	}

	teacher1.name = malloc(strlen(teacher2.name) + 1);
	strcpy(teacher1.name, teacher2.name);

5.错误写法 char **arr = { "aaa", "bbb", "ccc", "ddd" }; //arr为4个字节的指针，无法容纳 16个字节

6.除了sizeof 对数组名取地址这两种情况下，其他任何情况下数组名都是指向首元素的指针


第四天：文件 函数指针 链表
1.feof和EOF区别
#if 0
	while (!feof(f)) //feof读取文件指针的flag
	{
		ch = fgetc(f);

		if (feof(f))   //若不判断，则会把文件结尾的标志EOF打印出来(两个空格)
		{
			break;
		}

		printf("%c", ch);
	}
#endif

	while ((ch = fgetc(f)) != EOF)
	{

		printf("%c", ch);
	}


2.	按照字符读写文件：fgetc(), fputc()
	按照行读写文件：fputs(), fgets()
	按照块读写文件：fread(), fwirte()
	按照格式化读写文件：fprintf(), fscanf()  //fscanf遇到空格和换行时结束
	按照随机位置读写文件：fseek(), ftell(), rewind()

3.函数指针定义
 1.定义函数类型，通过类型来定义函数指针
    typedef int(FUN_TYPE)(int,char);
	FUN_TYPE *pFunc = myfunc;  //FUN_TYPE f; f(20,'a') 不可以这样写 报错
	pFunc(10, 'a');
	(*pFunc)(20, 'b');
	myfunc(30,'c');
 2.直接定义函数指针类型
    typedef int(*FUNC_P)(int, char);
	FUNC_P pFunc2 = myfunc;
	pFunc2(20,'d');
 3.直接定义函数指针变量
    int(*pFunc3)(int, char) 

4.回调函数:函数指针做参数 


5.静态库和动态库
	1.静态库特点：编译时期完成   运行时与函数库再无瓜葛，移植方便  	浪费空间和资源  更新困难
	2.动态库特点： 程序运行的时候才进行链接  
	动态链接库中定义有两种函数：导出函数和内部函数
	导出函数可以被其它模块调用，内部函数在定义它们的DLL程序内部使用。
