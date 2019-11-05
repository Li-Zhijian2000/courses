lab2 bomb
=========

预备知识
-------

调用栈 | 
--------|-
arguement n | 
... |  
arguement 7 | 
return address | 
caller-saved registers | 
local variables | 

---
---

1 | 2 | 3 | 4 | 5 | 6 | 
--|---|---|---|---|---|-
%rdi | %rsi | %rdx | %rcx | %r8 | %r9 | 

* callee-saved:  
  * %rbx, %rbp, %r12~%r15
  * 被调用者要么不改变它们，要么就是把原始值压入栈中，然后在返回前弹出旧值
* caller-saved:
  * except from caller-saved registers and %rsp
  * 通常，对于传递参数的寄存器，调用者并不会选择在调用前保存它们，而是在需要的时候重新构造它们
* movq/lea imm(%rdx, %rcx)
* 强制对齐
  > 任何针对x86-64处理器的编译器和运行时系统必须保证分配用来保存可能会被SSE寄存器读或写的数据结构的内存，都必须满足16字节对齐：  
  > * 任何内存分配函数生成的块的起始地址都必须是16的倍数。
  > * 大多数函数的栈帧的边界都必须是16字节的倍数

phase 1
------

为了调试方便，我们预先在 ` 文件中随机输入6个字符串
``` bash
(gdb) file bomb
(gdb) b phase_1
(gdb) r input.txt 
```
我们可以看到 `phase_1` 函数长这样：
``` x86asm
phase_1:
  sub    $0x8,%rsp                        # 将栈帧边界对齐到16字节
  mov    $0x402400,%esi                   # 传递参数
  callq  0x401338 <strings_not_equal>     # 调用string_not_equal
  test   %eax,%eax
  je     0x400ef7 <phase_1+23>            # 若返回值为1，不跳转，然后爆炸
  callq  0x40143a <explode_bomb>
  add    $0x8,%rsp
  retq
```
这个函数大致意思比较输入的字符串和位于 `0x402400` 的字符串，若两字符串不相同，则引爆炸弹.我们便看看这个字符串是何方神圣：
``` 
(gdb) x/s 0x402400
0x402400:   "Border relations with Canada have never been better."
```
将这句话复制到 `input.txt` 的第一行便大功告成了。

phase 2
------

接着我们给 `phase_2` 打上断点，重新运行
```
(gdb) b phase_2
(gdb) r input.txt
```

``` x86asm
phase_2:
  push   %rbp
  push   %rbx
  sub    $0x28,%rsp
  mov    %rsp,%rsi
  callq  0x40145c <read_six_numbers>
```
分配了0x28字节的栈帧后，`phase_2` 直接把 `%rsp` 作为参数传递给了 `read_six_numbers` ，结合函数的名字，我们猜测这个函数接着让我们从输入的字符串中读取6个整数，并存在开辟的栈帧中，读者可以猜猜怎样的源代码可以生成这种汇编。接下来进入这个函数

``` x86asm
# 为了方便阅读，我小小地更改了下无前后关系的语句的顺序
read_six_numbers:
  sub    $0x18,%rsp
  # 保存在寄存器中的参数
  mov    %rsi,%rdx
  lea    0x4(%rsi),%rcx
  lea    0x8(%rsi),%r8
  lea    0xc(%rsi),%r9
  # 保存在栈中的参数
  # 记住我们是无法直接从内存移动数据到内存，所以必须借助中间寄存器
  lea    0x10(%rsi),%rax
  mov    %rax,(%rsp)
  lea    0x14(%rsi),%rax
  mov    %rax,0x8(%rsp)

  mov    $0x4025c3,%esi
  mov    $0x0,%eax
  callq  0x400bf0 <__isoc99_sscanf@plt>
```
可以看到，`read_six_numbers` 调用了 `__isoc99_sscanf@plt`，其实就是我们的库函数 `sscanf` ，让我们回忆下它的声明：
> int sscanf ( const char *s, const char *format, ...);  


再看看 `sscanf` 的第二个参数存的是啥：
```
(gdb) x/s 0x4025c3
0x4025c3:   "%d %d %d %d %d %d" 
```

果然，我们要读取6个数，也就是需要传递八个参数，我们要把后两个参数保存在栈中。上面那段代码的意思其实就是把前4个数的地址分别放入 `%rdx, %rcx, %r8, %r9` ，将后 2 个数的地址分别放入 `(%rsp), 0x8(%rsp)`  

我们看看读入的参数长啥样（好像暴露答案了)因为 `%rsi` 是 caller-saved register，所以并不能保证 `%rsi` 在调用完 `sscanf` 后不改变，我们就提前把它存好  
```
(gdb) set $i = $rsi
(gdb) b __isoc99_sscanf@plt
(gdb) c
(gdb) finish
(gdb) x/6d $i
0x7ffffffedf80: 1   2   4   8
0x7ffffffedf90: 16  32
```
至于 `phase_2` 接下来则是一个循环，一一地比对读入的 6 个数，保证一个数是它前一个数的 2 倍，不符合条件就爆炸，没什么好说的，如果有困惑，可以参考下面的 C 代码  
```c
char *format = "%d %d %d %d %d %d";
void read_six_numbers(input, a)
{
    
    if (sscanf(input, format, 
               a, a+1, a+2, a+3, a+4, a+5) <= 5)
        explode_bomb();
}
void phase_2(char *input)
{
    int a[6];
    read_six_numbers(input, a);
    
    if (*a != 1) {
        explode_bomb();
        return;
    }
    for (int `lo = a+1, `hi = a+6; lo != hi; lo++) {
        int pre = *(lo - 1);
        pre *= 2;
        if (pre != *lo) {
            explode_bomb();
            return;
        }
    }
}
```

phase 3
------

`phase 3` 主要考察了 `switch` 语句，没什么好说的，直接给出对应的 C 语句  
``` 
(gdb) set $i = 0x402470
(gdb) x/8gx $i
0x402470:   0x0000000000400f7c  0x0000000000400fb9
0x402480:   0x0000000000400f83  0x0000000000400f8a
0x402490:   0x0000000000400f91  0x0000000000400f98
0x4024a0:   0x0000000000400f9f  0x0000000000400fa6
```
```c
char *format = "%d %d";
void phase_4(char *input)
{
    int a, b;
    if (sscanf(input, format, &a, &b) <= 2)
        explode_bomb();

    int tmp;    
    if (a <= 7U) {
        switch(a) {
            case 0:
                tmp = 0xcf;
                break;
            case 1:
                tmp = 0x137;
                break;   
            case 2:
                tmp = 0x2c3;
                break;  
            case 3:
                tmp = 0x100;
                break;  
            case 4:
                tmp = 0x185;
                break;  
            case 5:
                tmp = 0xce;
                break;  
            case 6:
                tmp = 0x2aa;
                break;  
            case 7:
                tmp = 0x147;
                break;  
        }
    } 
    else {
        tmp = 0;
        explode_bomb();
    }

    if (tmp != b) explode_bomb();
}
```

phase 4
------

仍旧是老样子，从输入中读取两个数，不妨设其为 a, b ，然后判断 a 是否大于 `0xe`，接着调用 `func4` 这个递归函数
```
phase_4:
  mov    $0xe,%edx
  mov    $0x0,%esi
  mov    0x8(%rsp),%edi
  callq  0x400fce <func4>                 # func(a, 0, 0xe);
```
```x86asm
# int func4(int a, int b, int c)
mov    %edx,%eax                        # int t1 = c
sub    %esi,%eax                        # t1 -= b
mov    %eax,%ecx                        # unsigned t2 = t1
shr    $0x1f,%ecx                       # t2 >>= 31
add    %ecx,%eax                        # t1 += t2;
sar    %eax                             # t1 >>= 1
lea    (%rax,%rsi,1),%ecx               # t2 = t1 + b
cmp    %edi,%ecx                        # cmp t2 : a
jle    0x400ff2 <func4+36>----
lea    -0x1(%rcx),%edx       |
callq  0x400fce <func4>      |          
add    %eax,%eax             |          
jmp    0x401007 <func4+57>---|----      # return 2 * func(a, b, t2 - 1)
mov    $0x0,%eax  <-----------   |      
cmp    %edi,%ecx                 |      # cmp t2 : a
jge    0x401007 <func4+57>-------| 
lea    0x1(%rcx),%esi            | 
callq  0x400fce <func4>          |
lea    0x1(%rax,%rax,1),%eax <----      # return 2 * func(a, b, t2 + 1) + 1
retq
```
先找出这个递归函数的出口，观察可以发现除了递归基，*func4* 还有两次可能的递归调用，因此，*func4* 应具有以下这种结构：
```c
if (/*---*/) return;

if (/*---*/) {
    func4();
    /*
     ...
     */
    return;
}
if (/*---*/) {
    func4();
    /*
       ...
     */
    return;
}
```
进一步观察可发现，递归基并没有显式地表现出来，我们取两次跳转语句的交集，可以得出递归基的条件是 $t2 \le a \land t2 \ge a\to t2=a$，至于另外两次递归调用则清晰明了，在此不再赘述。
```c
int func4(int a, int b, int c)
{
    /* 
       compute t2 with b and c
       ...
     */

    // because b euqals to zero, we have a simplified version code to compute t2:
    int t2 = (c + ((unsigned)c >> 31)) / 2;

    if (t2 == a) return 0;
    if (t2 > a) return 2 * func4(a, b, t2 - 1);
    if (t2 < a) return 2 * func4(a, b, t2 + 1) + 1;
}
```

接下来我们回到 `phase_4` 看看输入的两个数需要满足什么条件
```
(gdb) backtrace
#0  0x0000000000400fce in func4 ()
#1  0x000000000040104d in phase_4 ()
#2  0x0000000000400e93 in main (argc=<optimized out>, argv=<optimized out>) at `    `.
(gdb) f 1
```

不妨令输入的两个数为 *a, b*，需满足

$$a <= 14U \land func(a, 0, 14) == 0 \land b == 0$$

`func` 是个递归函数，满足 `func(a, 0, 14) == 0` 的 a 有很多个，为了简便，我们直接令 `a = t2` ，得到其中一个解
```
(gdb) f 0
(gdb) b *0x400fe2
(gdb) c
(gdb) print $ecx
$1 = 7
```
因此，a=7, b=0 就是我们想要的答案了。事实上 a 还能取 3, 1, 0 ，读者不妨用笔算验证一下

phase 5
------

让我们来看看 `phase 5`
``` x86asm
push   %rbx
sub    $0x20,%rsp
mov    %rdi,%rbx
mov    %fs:0x28,%rax
mov    %rax,0x18(%rsp)

xor    %eax,%eax
callq  0x40131b <string_length>
cmp    $0x6,%eax
je     0x4010d2 <phase_5+112>
callq  0x40143a <explode_bomb>
```
一开始便是一句很奇怪的指令 `mov  %fs:0x28, %rax`，这是一种 [防止栈破坏的手段](https://security.stackexchange.com/questions/158609/how-is-the-stack-protection-enforced-in-a-binary) ，即在栈帧的开始处存储一个特殊值，在函数返回是检查这个位置的特殊值有无被破坏。如果被破坏，则程序中止。  

我们看到，输入的应是一个长度为 6 的字符串，让我们继续看看这个字符串应具有怎样的性质。

```x86asm
# 输入的字符串的首地址s存于%rbx
# char str[6];
mov    $0x0,%eax                        # i = 0
movzbl (%rbx,%rax,1),%ecx  <-----       # int a = s[i]
mov    %cl,(%rsp)               |       
mov    (%rsp),%rdx              |
and    $0xf,%edx                |       # a %= 16
movzbl 0x4024b0(%rdx),%edx      |       # a = unknowm[a]
mov    %dl,0x10(%rsp,%rax,1)    |       # str[i] = a
add    $0x1,%rax                |       # i++
cmp    $0x6,%rax                |       # cmp i : 6
jne    0x40108b <phase_5+41> ----
```
显然，这是个循环，构造出了 `str` 这个字符数组：
```c
char *unknown = (char *)0x4024b0;
char str[6];
for (int i = 0; i < 6; i++)
    str[i] = unknown[s[i] % 16];
```
让我们接着往下看：
```x86asm
movb   $0x0,0x16(%rsp)                  # str[6] = '\0'
mov    $0x40245e,%esi               
lea    0x10(%rsp),%rdi 
callq  0x401338 <strings_not_equal>     #strings_not_equal(str, (char *)0x40245e)
```
似乎已经一目了然，就是检查构造出的 `str` 是否满足要求  
让我们看看这两个未知地址里存的是啥：
```
(gdb) x/s 0x4024b0
0x4024b0 <array.3449>:  "maduiersnfotvbylSo you think you can stop the phase with ctrl-c, do you?"
(gdb) x/s 0x40245e
0x40245e:   "flyers"
```
第一个字符串好像因为没有'\0'溢出了，不过我们只需要前16个字符 `maduiersnfotvbyl` ，我们需要6个下标将其映射到第二个字符串上，依次为 `9, 15, 14, 5, 6, 7`

由于我们的输入会被转换成 ascii 码再取低 4 位，因此我们要把下标进一步映射到可打印字符的 ascii 码，恰巧 '0' 的 ascii 码是 48，因此我们答案就是 `57, 63, 62, 53, 54, 55` ，也就是 `"9?>567"`

bomb 6
------

终于来到了最后一关:)  

命名规范  
* 全局变量前有 `g_`
* 数组用 $a_i,i\in [1,n)$ 表示
* 变量用 $t_i,i\in [1,n)$ 表示
* 指针用 $p_i,i\in [1,n)$ 表示
* 循环指示量用 $i,j,k\cdots$ 表示

循环的本质是有一条向上的跳转指令，这条跳转指令能够指明该循环的起点和终点。  

如果遇到嵌套循环，要先找到整段代码的出口（也就是跳得最后的跳转指令），出口所在的循环就是最外层的循环  

整个函数大致结构如下：
* `read_six_numbers`
* 嵌套循环
* 一个小循环
* 嵌套循环
* 两个小循环

一开始的 `read_six_numbers` 和 bomb 2 一样，在此就不再细说。

看看接下来的一个嵌套循环：
```x86asm
; int a1[6];
; read_six_numbers(input, a1);
mov    %rsp,%r13                            ;   int *p1 = a1
mov    $0x0,%r12d                           ;   int i = 0
                                            ; loop1:
mov    %r13,%rbp            <--------
mov    0x0(%r13),%eax               |   
sub    $0x1,%eax                    |       
cmp    $0x5,%eax                    |       
jbe    0x401128 <phase_6+52>        |       
callq  0x40143a <explode_phase>     |
add    $0x1,%r12d                   |       ;       i++
cmp    $0x6,%r12d                   |       
je     0x401153 <phase_6+95>-------------   ;       if i == 6, goto done1
mov    %r12d,%ebx                   |   |   ;       int j = i
                                    |   |   ; loop2:
movslq %ebx,%rax            <----   |   |
mov    (%rsp,%rax,4),%eax       |   |   |
cmp    %eax,0x0(%rbp)           |   |   |   
jne    0x401145 <phase_6+81>    |   |   |    
callq  0x40143a <explode_bomb>  |   |   |
add    $0x1,%ebx                |   |   |   ;           j++
cmp    $0x5,%ebx                |   |   |
jle    0x401135 <phase_6+65>----|   |   |   ;           if j <= 5, goto loop2
                                    |   |   ; done2:
add    $0x4,%r13                    |   |   ;       p1++
jmp    0x401114 <phase_6+32>---------   |   ;       goto loop1
                            <-----------|   ; done1:     
```
三个关键跳转语句已经用箭头标注出其跳转结构，我们便可以从中判断出存在两个循环和外层循环是哪个。接下来就是依次判断循环递增变量、跳转条件，在此不再赘述，以下是 C 代码：

```c
void phase_6(char *input)
{
    int a1[6];
    read_six_numbers(input, d);

    int i = 0;
    int *p1 = a1;
    while (1) {
        if (*p1 - 1 > 5U) explode_bomb();

        i++;
        if (i == 6) break;

        for (int j = i; j <= 5; j++)
            if (a1[j] == *p1) explode_bomb();
        
        p1++;
    }
}
```
这两个循环的意思就是，输入的 6 个数应该是小于等于 7 的互不相同的正数，也就是必须是  [1, 7) 的全排列的一种。  

接下来是个小循环：  
```x86asm
mov    %rsp,%r14                        
lea    0x18(%rsp),%rsi                  ;   int *p2 = a1 + 6
mov    %r14,%rax                        ;   int *p1 = a1
mov    $0x7,%ecx                        
                                        ; loop:
mov    %ecx,%edx
sub    (%rax),%edx                      
mov    %edx,(%rax)                      ;       (*p1) = (7 - *p1)
add    $0x4,%rax                        ;       p1++
cmp    %rsi,%rax                        
jne    0x401160 <phase_6+108>           ;   if p1 != p2, goto loop
```
其实就是 $a1[i] = 7 - a1[i],\ i\in[0, 6)$

接下来的这部分则有些许复杂，各种跳转指令嵌套，似乎杂乱无章，让我们把关键语句标注出来：
```x86asm
<+123>: mov    $0x0,%esi                
<+128>: jmp    0x401197 <phase_6+163>
                                        ; loop2:
<+130>: mov    0x8(%rdx),%rdx             
<+134>: add    $0x1,%eax                
<+137>: cmp    %ecx,%eax                
<+139>: jne    0x401176 <phase_6+130>   ;   goto loop2
<+141>: jmp    0x401188 <phase_6+148>   ;   goto done2
                                        ; loop1:
<+143>: mov    $0x6032d0,%edx           
                                        ; done2:
<+148>: mov    %rdx,0x20(%rsp,%rsi,2)   
<+153>: add    $0x4,%rsi                
<+157>: cmp    $0x18,%rsi                 
<+161>: je     0x4011ab <phase_6+183>   ;   goto done1
<+163>: mov    (%rsp,%rsi,1),%ecx       
<+166>: cmp    $0x1,%ecx                
<+169>: jle    0x401183 <phase_6+143>   ;   goto loop1
<+171>: mov    $0x1,%eax                ;       
<+176>: mov    $0x6032d0,%edx           
<+181>: jmp    0x401176 <phase_6+130>   ;   goto loop2
                                        ; done1:
```
显然，这是个嵌套循环，<+143>~<+169> 是外层循环，<+130~+139> 是内层循环

另外，定义：
```c
typedef struct {
    int value;
    struct Node *next;
}Node;
Node *p;
```
汇编语句
```x86asm
; p in %rdx
<+130>: mov    0x8(%rdx),%rdx
```
其实是一个跟结构体相关的语句
```c
p = p->next;
```
接着让我们添加更多信息：
```x86asm
; int a1[6];
; Node *a2[6];
; Node *g_node;
<+123>: mov    $0x0,%esi                ;   int i = 0
<+128>: jmp    0x401197 <phase_6+163>
                                        ; loop2:
<+130>: mov    0x8(%rdx),%rdx           ;           p1 = p1->next
<+134>: add    $0x1,%eax                ;           j++
<+137>: cmp    %ecx,%eax                
<+139>: jne    0x401176 <phase_6+130>   ;           if j != t1, goto loop2
<+141>: jmp    0x401188 <phase_6+148>   ;           else, goto done2
                                        ; loop1:
<+143>: mov    $0x6032d0,%edx           ;       Node *p1 = g_node
                                        ; done2:
<+148>: mov    %rdx,0x20(%rsp,%rsi,2)   ;       a2[i] = p1
<+153>: add    $0x4,%rsi                ;       i++
<+157>: cmp    $0x18,%rsi                 
<+161>: je     0x4011ab <phase_6+183>   ;       if i == 6, goto done1
<+163>: mov    (%rsp,%rsi,1),%ecx       ;       int t1 = a1[i]
<+166>: cmp    $0x1,%ecx                
<+169>: jle    0x401183 <phase_6+143>   ;       if t1 <= 1, goto loop1
<+171>: mov    $0x1,%eax                ;       j = 1
<+176>: mov    $0x6032d0,%edx           ;       p1 = g_node
<+181>: jmp    0x401176 <phase_6+130>   ;       goto loop2
                                        ; done1:
```
接下来，我们便可以试着写出对应的 C 代码了
```c
typedef struct {
    int value;
    struct Node *next;
}Node;
Node *g_node;

void phase_6(char *input)
{
    /*
     int a1[6];
     */
    Node *a2[6];

    int i = 0;
    Node *p1 = g_node;
    while (1) {
        a2[i] = p1;
        i++;

        if (i == 6) break;
        
        if (a1[i] <= 1) p1 = g_node;
        else {
            int j = 1;
            p1 = g_node;
            while (j != a1[i]) {
                p1 = p1->next;
                j++;
            }
        }
    }
}
```
每一遍循环都把 `g_node` 这个链表的第 a1[i] 个值的地址放在 a2[i] 这个位置上

让我们接着往下看：
```x86asm
; Node *a2[6];
<+183>: mov    0x20(%rsp),%rbx          ;   Node *p1 = a2[0]
<+188>: lea    0x28(%rsp),%rax          ;   Node **p2 = a2 + 1
<+193>: lea    0x50(%rsp),%rsi          ;   Node **p3 = a2 + 6
<+198>: mov    %rbx,%rcx                ;   Node *p4 = p1
                                        ; loop:
<+201>: mov    (%rax),%rdx              
<+204>: mov    %rdx,0x8(%rcx)           ;       p4->next = *p2
<+208>: add    $0x8,%rax                ;       p2++
<+212>: cmp    %rsi,%rax
<+215>: je     0x4011d2 <phase_6+222>   ;       if p2 == p3, break
<+217>: mov    %rdx,%rcx                ;       p4 = p2-1
<+220>: jmp    0x4011bd <phase_6+201>   ;       goto loop
```
这种优化过的代码十分难以理解，我们把它还原：
```c
    for (int i = 1; i != 6; i++) {
        a1[i-1] = a2[i];
    }
```
其实就是把整个链表重新连接  

接着往下看：
```x86asm
<+222>: movq   $0x0,0x8(%rdx)           ; a2[5]->next = NULL;
<+230>: mov    $0x5,%ebp                
<+235>: mov    0x8(%rbx),%rax           ; p2 = p1->next
<+239>: mov    (%rax),%eax              
<+241>: cmp    %eax,(%rbx)
<+243>: jge    0x4011ee <phase_6+250>   ; if p1->value >= p2->value, bomb defused
<+245>: callq  0x40143a <explode_bomb>
<+250>: mov    0x8(%rbx),%rbx           ; p1 = p1->next
<+254>: sub    $0x1,%ebp
<+257>: jne    0x4011df <phase_6+235>
```
这段代码就是确保整个链表是一个降序排列，否则就爆炸

让我们看看一开始的链表是什么样子的：
```
(gdb) set $i = 0x6032d0
(gdb) x/24wd $i 
0x6032d0 <node1>:   332 1   6304480 0                        
0x6032e0 <node2>:   168 2   6304496 0                        
0x6032f0 <node3>:   924 3   6304512 0                        
0x603300 <node4>:   691 4   6304528 0
0x603310 <node5>:   477 5   6304544 0
0x603320 <node6>:   443 6   0   0
```
第一列是 `value`，第二列是序号，第三四列是 `next` （由于我们是以 32 位的形式打印，所以8个字节的指针值分成了两列） 

可以看到，这个链表一开始是乱序的，如果要把这个链表变为降序。我们的 a1 数组应满足：
$$a1[6] = \{3, 4, 5, 6, 1, 2\}$$
又因为我们一开始经历了一步  
$$a1[i] = 7 - a1[i],\ i\in[0, 6)$$  
所以我们的输入应该是  
$$a1[6] = \{4, 3, 2, 1, 6, 5\}$$