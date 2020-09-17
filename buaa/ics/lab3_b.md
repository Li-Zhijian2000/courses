# LAB03-B 17376283 李智健

## Question 1

1. 写入代码

![](lab3_b_p1.PNG)

逐条执行

![](lab3_b_p2.PNG)

![](lab3_b_p3.PNG)

![](lab3_b_p4.PNG)

填空题答案

```cpp
ax = C0EA
ax = C0FC
bx = 30F0
bx = 6021
sp = 00FE , 修改的内存单元的地址是 00FE，内容为 C0FC
sp = 00FC , 修改的内存单元的地址是 00FC，内容为 6021
sp = 00FE , ax=6021
sp = 0100 , bx=C0FC
sp = 00FE , 修改的内存单元的地址是 00FE，内容为 30F0
sp = 00FC , 修改的内存单元的地址是 00FC，内容为 2931
```

2. 分析3.19中为什么2000:0~2000:f中的内容会发生改变?

    因为 `mov sp, 10` 改变了栈偏移量

## Question 2

代码：

```assembly
assume cs:codesg
codesg segment
  mov ax, 2000h
  mov ss, ax
  mov sp, 0
  add sp, 10
  pop ax
  pop bx
  push ax
  push bx 
  pop ax
  pop bx
  mov ax, 4c00h
  int 21h
codesg ends
end
```

**生成可执行文件的命令截图：**

![](lab3_b_p5.PNG)

![](lab3_b_p6.PNG)

|   调试命令   |  ax  |  bx  |  ss  |  sp  | 栈顶 |
| :----------: | :--: | :--: | :--: | :--: | :--: |
| mov ax,2000H | 2000 | 0000 | 0769 | 0000 |  00  |
|  mov ss,ax   | 2000 | 0000 | 2000 | 0000 |  00  |
|   mov sp,0   | 2000 | 0000 | 2000 | 0000 |  00  |
|  add sp,10   | 2000 | 0000 | 2000 | 000A |  6A  |
|    pop ax    | 076A | 0000 | 2000 | 000C |  06  |
|    pop bx    | 076A | 7206 | 2000 | 000E |  00  |
|   push ax    | 076A | 7206 | 2000 | 000C |  6A  |
|   push bx    | 076A | 7206 | 2000 | 000A |  06  |
|    pop ax    | 7206 | 7206 | 2000 | 000C |  6A  |
|    pop bx    | 7206 | 076A | 2000 | 000E |  00  |
| mov ax,4c00H | 4C00 | 076A | 2000 | 000E |  00  |
|   int 21H    | 4C00 | 076A | 2000 | 000E |  00  |

#### 3.提交查看过程的截图。

![](lab3_b_p7.PNG)