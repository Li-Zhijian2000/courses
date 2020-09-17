## question 1

1. `xor %eax, %eax` 可将 `%eax` 置零

2. ```c
    int foo(int op, int a, int b) {
        int result = 0;
        switch(op) {
            case 0:
                result = a;
                result &= b;
                break;
            case 1:
                result = a;
                result |= b;
                break;
            case 2:
                result = a;
                result ^= b;
                break;
            case 3:
                result = ~a;
                break;
            case 4:
                result = a + b;
                break;
        }
        return result;
    }
    ```



## question 2

```c
typedef enum {MODE_A, MODE_B, MODE_C, MODE_D, MODE_E} mode_t;
int switch3(int *p1, int *p2, mode_t action) {
    int result = 0;
    switch(action) {
        case MODE_A:
            result = *p1;
            *p1 = *p2;
            break;
        case MODE_B:
            result = *p2 + *p1;
            *p2 = result;
            break;
        case MODE_C:
            *p2 = 59;
            result = *p1;
            break;
        case MODE_D:
            *p2 = *p1;
            result = 27;
            break;
        case MODE_E:
            result = 27;
            break;
        default:
            result = -1;
    }
    return result;
}
```



## question 3

1. `%eax = 0x8048395` 
2. `%eip = 0x804839b`



## question 4

1. ```c
    int lolwut(char *s) {
        int i, n;
        n = 0;
        for (i = 0; s[i] != 0; i++) {
            if (s[i] - '0' > 9) {
                return -1;
            }
            n = n*10 + s[i] - '0';
        }
        return n;
    }
    ```

2. ```assembly
    subl $4, %esp
    movl %ebx, (%esp)
    ```

3. ```
    0xffff000c
    ```

## question 5

1. 
   | address    |            |
   | ---------- | ---------- |
   | 0xffffd830 | 4          |
   | 0xffffd82c | 0x080483e6 |
   | 0xffffd828 | 0xffffd848 |
   | 0xffffd824 | %ebx       |
   | 0xffffd820 | 3          |
   | 0xffffd81c | 0x080483be |
   | 0xffffd818 | 0xffffd828 |
   | 0xffffd814 | 4          |
   | 0xffffd810 | 2          |

3. `0xffffd818`
4. `0xffffd810`



## question 6

1. `%ebp = 0x80003c`

2. `%esp = 0x7ffffc`

3. 
   
    ```c
    &x = 0x800038
	&y = 0x800034
    ```
4. 
    | address  |                |
    | -------- | -------------- |
    | 0x800040 | return address |
    | 0x80003c | 0x800060       |
    | 0x800038 | 0x53           |
    | 0x800034 | 0x46           |
    | ...      | not used       |
    | 0x800004 | 0x800038       |
    | 0x800000 | 0x800034       |
    | 0x7ffffc | 0x300070       |

5. `0x800008 ~ 0x800030`  are not used by `proc`



## question 7

### part 1

1. 查看 `0000:00 ~ 0000:1f` 的内存

    ![](lab3_a_p1.PNG)

2. ![](lab3_a_p2.PNG)

    然后将那些命令都输进去。。。

    ![](lab3_a_p3.PNG)

    之后不断按 `-t`

    1~4 

    ![](lab3_a_p4.PNG)

    5~8

    ![](lab3_a_p5.PNG)

    9~12

    ![](lab3_a_p6.PNG)

    13

    ![](lab3_a_p8.PNG)

3. 

    ```
    (1)  AX=0008
    (2)  BX=7000
    (3)  AX=7000
    (4)  AX=0008
    (5)  BX=0070
    (6)  AX=0078
    (7)  AX=10D8
    (8)  AX=0000
    (9)  AX=0070
    (10) BX=0000
    (11) BX=0060
    (12) AX=00D0
    ```

    

### part 2

1. `00000~9ffff` 主存储器

    `a0000~bffff` 显存

    `c0000~fffff` 各种 ROM

2. ![](lab3_a_p5.PNG)

3. 三个数字分别代表黑色、绿色、灰色