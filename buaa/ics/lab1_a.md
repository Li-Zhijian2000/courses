question 1
----------------

```c++
string dec2(int x, int i) {
    string res = ""; 
    while (x > 0) {
        int q = x % i;
        res += (q <= 9) ? + q + '0' : q - 10 + 'A';
        x /= i;
    }
    reverse(res.begin(), res.end());
    return res;
}
int main() {
    int dec;
    printf("input: ");
    while (cin >> dec) {
        printf("%-34s%-34s%-34s\n", "decimal", "binary", "hexadecimal");
        printf("%-34d%-34s%-34s\n", dec, dec2(dec, 2).c_str(), dec2(dec, 16).c_str());
        putchar('\n');
        printf("input: ");
    }
}
```

output:
```
input: 188
decimal                           binary                            hexadecimal                       
188                               10111100                          BC       

input: 876108
decimal                           binary                            hexadecimal                       
876108                            11010101111001001100              D5E4C    
                         
input: 3778552
decimal                           binary                            hexadecimal                       
3778552                           1110011010011111111000            39A7F8   
```

question 2
----------
```bash
$ cat code.c
//code.c
int accum = 0;
int sum(int x, int y) {
    int t = x + y;
    accum += t;
    return t;
}

$ cat main.c
//main.c
#include<stdio.h>
int main() {
    printf("%d\n", sum(1, 3));
}
```
1. assembly code of `code.c`
   ```
   $ gcc -m32 -S code.c -o code.s
   
   $ cat code.s
           .file   "code.c"
           .text
           .globl  accum
           .bss
           .align 4
           .type   accum, @object
           .size   accum, 4
   accum:
           .zero   4
           .text
           .globl  sum
           .type   sum, @function
   sum:
   .LFB0:
           .cfi_startproc
           pushl   %ebp
           .cfi_def_cfa_offset 8
           .cfi_offset 5, -8
           movl    %esp, %ebp
           .cfi_def_cfa_register 5
           subl    $16, %esp
           call    __x86.get_pc_thunk.ax
           addl    $_GLOBAL_OFFSET_TABLE_, %eax
           movl    8(%ebp), %ecx
           movl    12(%ebp), %edx
           addl    %ecx, %edx
           movl    %edx, -4(%ebp)
           movl    accum@GOTOFF(%eax), %ecx
           movl    -4(%ebp), %edx
           addl    %ecx, %edx
           movl    %edx, accum@GOTOFF(%eax)
           movl    -4(%ebp), %eax
           leave
           .cfi_restore 5
           .cfi_def_cfa 4, 4
           ret
           .cfi_endproc
   .LFE0:
           .size   sum, .-sum
           .section        .text.__x86.get_pc_thunk.ax,"axG",@progbits,__x86.get_pc_thunk.ax,comdat
           .globl  __x86.get_pc_thunk.ax
           .hidden __x86.get_pc_thunk.ax
           .type   __x86.get_pc_thunk.ax, @function
   __x86.get_pc_thunk.ax:
   .LFB1:
           .cfi_startproc
           movl    (%esp), %eax
           ret
           .cfi_endproc
   .LFE1:
           .ident  "GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
           .section        .note.GNU-stack,"",@progbits
   ```

2. disassembly of function `sum`
   
   ```
   $ gcc -m32 -c code.c -o code.o
   
   $ objdump -d code.o
   code.o:     file format elf32-i386

   Disassembly of section .text:

   00000000 <sum>:
      0:   55                      push   %ebp
      1:   89 e5                   mov    %esp,%ebp
      3:   83 ec 10                sub    $0x10,%esp
      6:   e8 fc ff ff ff          call   7 <sum+0x7>
      b:   05 01 00 00 00          add    $0x1,%eax
     10:   8b 4d 08                mov    0x8(%ebp),%ecx
     13:   8b 55 0c                mov    0xc(%ebp),%edx
     16:   01 ca                   add    %ecx,%edx
     18:   89 55 fc                mov    %edx,-0x4(%ebp)
     1b:   8b 88 00 00 00 00       mov    0x0(%eax),%ecx
     21:   8b 55 fc                mov    -0x4(%ebp),%edx
     24:   01 ca                   add    %ecx,%edx
     26:   89 90 00 00 00 00       mov    %edx,0x0(%eax)
     2c:   8b 45 fc                mov    -0x4(%ebp),%eax
     2f:   c9                      leave
     30:   c3                      ret

   Disassembly of section .text.__x86.get_pc_thunk.ax:

   00000000 <__x86.get_pc_thunk.ax>:
      0:   8b 04 24                mov    (%esp),%eax
      3:   c3                      ret
   ```

3. Generate the executable code to print the result of `main.c`
   ```
   $ gcc -m32 code.c main.c -o main
   main.c: In function ‘main’:
   main.c:4:20: warning: implicit declaration of function ‘sum’ [-Wimplicit-function-declaration]
        printf("%d\n", sum(1, 3));

   $ ./main
   4
   ```

question 3
----------

format A |  | format B |  | 
--------|------|---------|----|-
bits | value | bits | value | 
011 0000 | 1 | 0111 000 | 1 | 
101 1110 | $7\frac{1}{2}$ | 1001 111 | $7\frac{1}{2}$ | 
010 1001 | $\frac{25}{32}$| 0110 100 | $\frac{3}{4}$ | 
110 1111 | $15\frac{1}{2}$| 1011 000 | $16$ | 
000 0001 | $\frac{1}{64}$ | 0001 000 | $\frac{1}{64}$



question 4
----------

代码：
```cpp
int main() {
    short sx;
    printf("input: ");
    while (cin >> sx) {
        printf("%-30s%hd\n", "x", sx);
        printf("%-30s%u\n", "(unsigned)sx", (unsigned)sx);
        printf("%-30s%u\n", "(unsigned)(int)sx", (unsigned)(int)sx);
        printf("%-30s%u\n", "(unsigned)(unsigned short)", (unsigned)(unsigned short)sx);
        putchar('\n');
        printf("input: ");
    }
}
```

output:
```
input: 1
x                             1
(unsigned)sx                  1
(unsigned)(int)sx             1
(unsigned)(unsigned short)    1

input: -1
x                             -1
(unsigned)sx                  4294967295
(unsigned)(int)sx             4294967295
(unsigned)(unsigned short)    65535
```
显然，实现 `(unsigned)sx` 的正确方式应为先拓展，再转化为无符号数

question 5
---------
使用 `print_bytes` 来输出某变量的字节表示：
```c
void print_bytes(unsigned char *p, int len) {
    for (int i = 0; i < len; i++)
        printf("\t%p\t%.2x\n", p + i, p[i]);
}
int main() {
    int a = 0x12345678;
    float b = -0.0;
    printf("bytes expression of 0x%x:\n", a);
    print_bytes((unsigned char *)&a, sizeof(a));
    putchar('\n');
    printf("bytes expression of %f:\n", b);
    print_bytes((unsigned char *)&b, sizeof(b));
    putchar('\n');
    printf("pointer of a:\n");
    printf("\t%p\n", &a);
}
```
output:
```c
bytes expression of 0x12345678:
        0xffaf7fdc      78
        0xffaf7fdd      56
        0xffaf7fde      34
        0xffaf7fdf      12

bytes expression of -0.000000:
        0xffaf7fd8      00
        0xffaf7fd9      00
        0xffaf7fda      00
        0xffaf7fdb      80

pointer of a:
        0xffaf7fdc
```
`0x12345678` 从低字节到高字节依次存储为 `0x78, 0x56, 0x34, 0x12`

`-0.0` 的浮点表示为 `1000 0000 0000 0000 0000 0000 0000 0000`，转为 16 进制即为 `0x80000000`，依次存储为 `0x00, 0x00, 0x00, 0x80` 

因此，本机器为小端法

question 6
----------

1. 有 1 个错误，代码没有对提取出来的字节进行符号拓展
   
   `xbyte` 函数应为
   ```c
   return (int)(char)((word >> (bytenum << 3)) & 0xFF);
   ```

2. 只使用左移和右移

   ```c 
   typedef unsigned packed_t;

   int xbyte(packed_t word, int bytenum) {
       int tmp = word;
       return (tmp << ((3 - bytenum) << 3)) >> 24;
   }

   int main() {
       unsigned input;
       int i;
       printf("input: ");
       while (~scanf("%x%d", &input, &i)) {
           printf("0x%x 的第 %d 个字节为 %x\n", 
                  input, i, xbyte(input, i));
           printf("\ninput: ");
       }
   }
   ```

   output:
   ```
   input: f3f2f1f0 0
   0xf3f2f1f0 的第 0 个字节为 fffffff0

   input: f3f2f1f0 1
   0xf3f2f1f0 的第 1 个字节为 fffffff1

   input: f3f2f1f0 2
   0xf3f2f1f0 的第 2 个字节为 fffffff2

   input: f3f2f1f0 3
   0xf3f2f1f0 的第 3 个字节为 fffffff3

   input: 73727170 0
   0x73727170 的第 0 个字节为 70

   input: 73727170 3
   0x73727170 的第 3 个字节为 73
   ```
