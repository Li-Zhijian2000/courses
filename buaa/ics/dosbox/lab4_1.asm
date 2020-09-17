assume cs:code
code segment
	mov ax, 0020h
	mov es, ax
	
	mov bx, 0
	mov cx, 63
	
s:
	mov es:[bx], bx
	inc bx
	loop s
	
	mov ax, 4c00h
	int 21h
ends
end