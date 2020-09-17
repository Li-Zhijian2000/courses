# LAB04B

17376283 李智健

## 实验4

(1)（2）代码相同

通过 DEBUG 观察可知，`mov ax, 4c00h` 位于 `076a:0017`，所以循环次数应设为 17 次

```assembly
assume cs:code
code segment
    
    mov ax, 0020h
    mov ds, ax
    mov bx, 0
    mov cx, 17

s:  mov [bx], bx
    inc bx
    loop s

    mov ax, 4c00h
    int 21h

code ends
end
```

(3)

```assembly
assume cs:code
code segment
    
    mov ax, 
    mov ds, ax
    mov ax, 0020h
    mov es, ax
    mov bx, 0
    mov cx, 

s:  mov al, [bx]
	mov es:[bx], al
    inc bx
    loop s

    mov ax, 4c00h
    int 21h

code ends
end
```

## 实验5

(1)

1. data 段中的数据分别为 0123h, 0456h, 0789h, 0abch, 0defh, 0fedh, 0cbah, 0987h
2. cs = 076c, ss = 076b, ds = 076a
3. data 的段地址为 X-2 ,stack 段的段地址为 X-1

(2)

1. data 段中的数据分别为 0123h, 0456h, 0, 0, 0, 0, 0, 0
2. cs = 076c, ss = 076b, ds = 076a
3. data 的段地址为 X-2 ,stack 段的段地址为 X-1

(3)

1. data 段中的数据分别为 0123h, 0456h, 0, 0, 0, 0, 0, 0
2. cs = 076a, ss = 076e, ds = 076d
3. data 的段地址为 X-2 ,stack 段的段地址为 X-1

(4) 
只有第 3 个程序才能正确执行，只有第 3 个程序的代码段位于程序的最前面。

(5)

```
code segment
start:
	mov ax,a
	mov ds,ax
	mov bx,0
	
	mov ax,b
	mov es,ax
	
	mov ax,c
	mov ss,ax
	
	mov cx,8
	
s:	mov al, ds:[bx]
	add al, es:[bx]
	mov ss:[bx], al
	inc bx
	loop s
	
code ends
end start
```

(6)

```
code segment
start:
	mov ax, a
	mov ds, ax
	mov bx, 0
	mov ax, b
	mov ss, ax
	mov sp, 08h
	mov cx, 8
	
s:	mov ax, ds:[bx]
	push ax
	inc bx
	loop s
	
code ends
end start
```