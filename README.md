# 语法分析器的设计与实现

## 要求（摘自课本

**实验内容** - 编写语法分析程序，实现对算术表达式的语法分析。要求所分析算术表达式由如下文法产生：

```
E -> E+T | E-T | T
T -> T*F | T/F | F
F -> (E) | num
```

**实验要求**
- 在对输入的算术表达式进行分析的过程中，依次输出所采用的产生式。
- 编程实现课本P92页的算法4.2，为给定文法自动构造预测分析表
- 编程实现课本P88页的算法4.1，构造LL(1)预测分析程序

## 算法（摘自课本

### 算法4.1 - 非递归预测分析方法

- 输入 - 输入符号串ω、文法G的一张预测分析表M
- 输出 - 若ω∈L(G)则输出ω的最左推导，否则报错

方法：

```c++
初始化{
	将$压入栈底
	将文法开始符号S压入栈顶
	将ω$放入输入缓冲区中
	向前指针ip指向ω$的第一个符号
}
根据预测分析表M对输入符号串ω做出自顶向下分析{
	do {
		令X是栈顶文法符号，a是ip指向的符号
		if (X是终结符号 || X == '$'){
			if (X == a){
				从栈顶弹出X
				ip向前移动一个位置
			} else {
				ERROR
			}
		} else { // X是非终结符
			if (M[X, a] == X -> Y1Y2...Yk){
				从栈顶弹出X
				依次把Yk, Y(k-1), ..., Y1压入栈 // Y1在栈顶
				输出产生式X -> Y1Y2...Yk
			} else {
				ERROR
			}
		}
	} while (X != '$'); // 栈非空，分析继续
}
```

### 算法4.2 - 预测分析表的构造方法

- 输入 - 文法G
- 输出 - 文法G的预测分析表M

方法：

```c++
for (文法G的每一个产生式A -> α){
	for (每个终结符号a∈FIRST(α))
		把A -> α放入表项M[A, a]中
	if (ε∈FIRST(α))
		for (每个b∈FOLLOW(A))
			把A -> α放入表项M[A, b]中
}
for (所有没有定义的表项M[A, a]) 标上错误标识
```

## 设计

参考之前写的[左递归消除程序](https://github.com/DiscreteTom/left-recursion-killer)的符号表数据结构，定义Symbol类区分非终结符和终结符，定义SymbolTable类保存符号表

输入要求：
- 无环路
- 无ε-生成式
- 无左递归（后期可以把输入先导入左递归消除程序

输入格式：
- 解析时会忽略所有空格和制表符，所以如果为了美观可以添加任意数量的空格和制表符
- 每行只能有一个非终结符的生成式，但是生成式可以有多个候选式。候选式使用`|`分隔
- 允许一个非终结符有多行生成式
- 单个非终结符以大写字母开头，后面可以接任意个英文单引号`'`
- 生成式的左侧只能有一个非终结符，此非终结符后面必须有箭头`->`。
- 只识别每行的第一个箭头`->`，同一行后面还有箭头会视为终结符
- 字符`~`表示ε，即空串
- **因为字符`$`作为分析结束符号，不能出现在文法中，所以使用两个`$`引起来的字符串被视为一个终结符，如`$num$`将把`num`视为一个非终结符而不是三个。要求`$`中的字符串长度大于1**
- 上面没有提到的可打印符号均可作为终结符。终结符后面可以接任意个英文单引号`'`