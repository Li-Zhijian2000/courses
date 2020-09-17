	.file	"test.c"
	.text
	.globl	array_sum1
	.type	array_sum1, @function
array_sum1:
.LFB0:
	.cfi_startproc
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	movl	8(%esp), %ebx
	movl	12(%esp), %ecx
	movl	$0, %edx
	movl	$0, %eax
	jmp	.L2
.L3:
	addl	(%ebx,%edx,4), %eax
	addl	$1, %edx
.L2:
	cmpl	%ecx, %edx
	jl	.L3
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE0:
	.size	array_sum1, .-array_sum1
	.globl	array_sum2
	.type	array_sum2, @function
array_sum2:
.LFB1:
	.cfi_startproc
	pushl	%esi
	.cfi_def_cfa_offset 8
	.cfi_offset 6, -8
	pushl	%ebx
	.cfi_def_cfa_offset 12
	.cfi_offset 3, -12
	movl	12(%esp), %ebx
	movl	16(%esp), %esi
	movl	$0, %edx
	movl	$0, %ecx
	movl	$0, %eax
	jmp	.L6
.L7:
	addl	(%ebx,%edx,4), %eax
	addl	4(%ebx,%edx,4), %ecx
	addl	$2, %edx
.L6:
	cmpl	%esi, %edx
	jl	.L7
.L8:
	cmpl	%esi, %edx
	jl	.L9
	addl	%ecx, %eax
	popl	%ebx
	.cfi_remember_state
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 4
	ret
.L9:
	.cfi_restore_state
	addl	(%ebx,%edx,4), %eax
	addl	$1, %edx
	jmp	.L8
	.cfi_endproc
.LFE1:
	.size	array_sum2, .-array_sum2
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
