.file	"lab5.s"
.section	.rodata
.LC0:
	.string	"Products\n"
.LC1:
	.string	"Sums\n"
.LC2:
	.string	"Elements in intArray1\n"
.LC3:
	.string "%hi\n"
.data

sizeIntArrays:
	.long 4
sizeShortArrays:
	.word 5
intArray1:
	.long 10
	.long 25
	.long 33
	.long 48
intArray2:
	.long 20
	.long -37
	.long 42
	.long -61
shortArray1:
	.word 69
	.word 95
	.word 107
	.word 12
	.word 332
shortArray2:
	.word 27
	.word -87
	.word 331
	.word -49
	.word -88
.globl main
	.type	main, @function

.text
main:
	pushl 	%ebp
	movl 	%esp, %ebp

	movl	$shortArray1, %eax
	movl	$shortArray2, %ecx
	movw	sizeShortArrays, %dx
	pushl 	%ecx
	pushl 	%eax
	pushw 	%dx
	call	addShorts
	addl	$12, %esp
	

	
	movl	$0, %eax
	leave
	ret
	.size	main, .-main

addShorts:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	$.LC1
	call	printf
	addl	$4, %esp
	movl	14(%ebp), %ecx
	movl	10(%ebp), %eax
	movw	8(%ebp), %dx
	pushl	%edi
	pushl 	%ebx
	movl	$0, %edi
	movl	$0, %ebx
	movw	%dx, %bx
	decl	%ebx
	pushl 	%ebx
	call printf
	addl $4, %esp
	popl	%ebx
	popl	%edi
	leave
	ret



movl 	$intArray1, %eax
	movl 	sizeIntArrays, %edx
	pushl	%eax
	pushl	%edx
	call	invertArray
	add	$8, %esp



printArray:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	$.LC2
	call 	printf
	addl	$4, %esp
	movl	12(%ebp), %eax
	movl	8(%ebp), %edx
	pushl	%edi
	movl	$0, %edi
loop_printArray:
	cmpl	%edi, %edx
	je	exit_printArray
	pushl	%eax
	pushl	%edx
	movl	(%eax, %edi, 4), %eax
	pushl	%eax
	pushl	$.LC3
	call 	printf
	addl	$8, %esp
	popl	%edx
	popl	%eax
	incl	%edi
	jmp	loop_printArray
exit_printArray:
	popl	%edi
	pushl	$.LC4
	call	printf
	addl	$4, %esp
	leave
	ret
