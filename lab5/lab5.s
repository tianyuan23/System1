#Author: Tianyuan Li
#This program is to do operations on int-arrays and short-arrays.

.file	"lab5.s"
.section	.rodata
.LC0:
	.string	"Products\n"
.LC1:
	.string	"Sums\n"
.LC2:
	.string	"Elements in intArray1\n"
.LC3:
	.string "%i\n"
.LC4:
	.string "\n"
.LC5:
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

	movl 	$intArray1, %eax	#store address of intArray1 in eax
	movl 	$intArray2, %ecx	#store address of intArray2 in ecx
	movl 	sizeIntArrays, %edx	#store value of sizeIntArray in edx
	pushl 	%ecx			#push 3rd parameter, pointer to intArray2 onto stack
	pushl 	%eax			#push 2nd parameter, pointer to intArray1 onto stack
	pushl 	%edx			#push 1st parameter, value of sizeIntArrray onto stack
	call	multInts		#call function multInts
	addl	$12, %esp		#remove parameters
	
	movl 	$shortArray1, %eax	#store address of shortArray1 in eax
	movl	$shortArray2, %ecx	#store address of shortArray1 in eax
	movw 	sizeShortArrays, %dx	#store value of sizeIntArray in dx
	pushl 	%ecx			#push 3rd parameter, pointer to shortArray2 onto stack
	pushl 	%eax			#push 2nd parameter, pointer to shortArray1 onto stack
	pushw 	%dx			#push 1st parameter, value of sizeShortArrray onto stack
	call	addShorts		#call funtion addShorts
	addl	$10, %esp		#remove parameters

	movl 	$intArray1, %eax	#store address of intArray1 in eax
	movl 	sizeIntArrays, %edx	#store value of sizeIntArray in edx
	pushl	%eax			#push 2nd parameter, pointer to intArray1 onto stack
	pushl 	%edx			#push 1st parameter, value of sizeIntArrray onto stack	
	call	printArray		#call function printArray
	add	$8, %esp		#remove parameters

	movl 	$intArray1, %eax	#store address of intArray1 in eax
	movl 	sizeIntArrays, %edx	#store value of sizeIntArray in edx
	pushl	%eax			#push 2nd parameter, pointer to intArray1 onto stack
	pushl 	%edx			#push 1st parameter, value of sizeIntArrray onto stack
	call	invertArray		#call funtion invertArray
	add	$8, %esp		#remove parameters

	movl 	$intArray1, %eax	#store address of intArray1 in eax
	movl 	sizeIntArrays, %edx	#store value of sizeIntArray in edx
	pushl	%eax			#push 2nd parameter, pointer to intArray1 onto stack
	pushl 	%edx			#push 1st parameter, value of sizeIntArrray onto stack	
	call	printArray		#call function printArray
	add	$8, %esp		#remove parameters

	movl	$0, %eax		#set return reg to 0
	leave
	ret
	.size	main, .-main

multInts:
	pushl	%ebp			#save caller’s frame pointer
	movl	%esp, %ebp		#set function’s frame pointer
	pushl	$.LC0			#push string pointer
	call	printf			#call printf to print string
	addl	$4, %esp		#remove string point from stack
	movl	16(%ebp), %ecx		#store 3rd parameter, intArray2 to ecx
	movl	12(%ebp), %eax		#store 2nd parameter, intArray1 to eax
	movl	8(%ebp), %edx		#store 1st parameter, sizeIntArray to edx
	pushl	%edi			#preserve callee save reg
	movl	$0, %edi		#init index in edi
loop_multInts:
	cmpl	%edi, %edx		#cmp index and size
	je	exit_multInts		#exit if equal
	pushl 	%eax			#preserve caller save reg
	pushl	%ecx
	pushl 	%edx
	movl	(%ecx, %edi, 4), %ecx	#store two values in same index of two arrays in ecx and eax
	movl	(%eax, %edi, 4), %eax
	imull	%ecx, %eax		#do multiplication
	pushl	%eax			#push result onto stack
	pushl	$.LC3			#push string point
	call 	printf			#call printf to print result
	addl	$8, %esp		#remove parameters from stack
	popl	%edx			#restore caller save reg
	popl	%ecx
	popl	%eax
	incl	%edi			#increment index
	jmp	loop_multInts		#jump back to top of loop
exit_multInts:
	popl	%edi			#restore callee save reg
	pushl	$.LC4			#print an empty line
	call	printf			
	addl	$4, %esp
	leave
	ret
	
addShorts:
	pushl	%ebp			
	movl	%esp, %ebp		
	pushl	$.LC1			#push string pointer
	call	printf			#print string
	addl	$4, %esp		#remove string point from stack
	movl	14(%ebp), %ecx		#store 3 parameters into dx, eax, ecx in order 
	movl	10(%ebp), %eax
	movw	8(%ebp), %dx
	pushl	%edi			#preserve callee save reg
	pushl 	%ebx
	movl	$0, %edi		#set initial index of shortArray1 to 0
	movl	$0, %ebx		#set index of shortArray2 to n
	movw	%dx, %bx
	decl	%ebx			#set initial index of shortArray2 to n-1
loop_addShorts:
	cmpl	$0, %ebx		#cmp index and size-1
	jl	exit_addShorts		#exit if less
	pushl 	%eax			#preserve caller save reg
	pushl	%ecx
	movw	(%ecx, %ebx, 2), %cx	#store two short values in each index of shortArray into cx and ax
	movw	(%eax, %edi, 2), %ax
	addw	%ax, %cx		#do addition
	pushw	%cx			#push result onto stack
	pushl	$.LC5			#push string point
	call 	printf			#print result
	addl	$6, %esp		#remove parameters from stack
	popl	%ecx			#restore caller save reg
	popl	%eax
	incl	%edi			#increment index of shortArray1
	decl	%ebx			#decrement index of shortArray2
	jmp	loop_addShorts		#jmp to top of loop
exit_addShorts:
	popl	%ebx			#restore callee save reg
	popl	%edi
	pushl	$.LC4			#print an empty line
	call	printf
	addl	$4, %esp
	leave
	ret
	
printArray:
	pushl	%ebp			
	movl	%esp, %ebp
	pushl	$.LC2			#push string pointer
	call	printf			#print string
	addl	$4, %esp		#remove string point from stack
	movl	12(%ebp), %eax		#store two parameters into edx and eax in order
	movl	8(%ebp), %edx
	pushl	%edi			#preserve callee save reg
	movl	$0, %edi		#init index in edi
loop_printArray:
	cmpl	%edi, %edx		#cmp index and size
	je	exit_printArray		#exit if equal
	pushl	%eax			#preserve caller save reg
	pushl	%edx
	movl	(%eax, %edi, 4), %eax	#store value to be printed into eax
	pushl	%eax			#push result onto stack
	pushl	$.LC3			#push string pointer
	call 	printf			#print current element
	addl	$8, %esp		#remove parameters
	popl	%edx			#restore caller save reg
	popl	%eax
	incl	%edi			#increment index
	jmp	loop_printArray		#loop to print next element
exit_printArray:
	popl	%edi			#restore callee save reg
	pushl	$.LC4			#print an empty line
	call	printf
	addl	$4, %esp
	leave
	ret


invertArray:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %eax		#store two parameters into edx and eax in order
	movl	8(%ebp), %edx
	decl	%edx			#set index to last element
	pushl	%ebx			#preserve callee save reg
	pushl	%esi
	pushl	%edi
	movl	$0, %edi		#set another index to first element
loop_invertArray:
	cmpl	%edi, %edx		#cmp 2 index
	jle	exit_invertArray	#jmp if less or equal
	movl 	(%eax, %edi, 4), %esi	#store two elements into esi and ebx 
	movl	(%eax, %edx, 4), %ebx
	movl	%esi, (%eax, %edx, 4)	#swap value in each other's address
	movl	%ebx, (%eax, %edi, 4)
	incl	%edi			#increment first index and decrement second index
	decl	%edx
	jmp	loop_invertArray	#jmp to top of loop
exit_invertArray:
	popl 	%edi			#restore callee save reg
	popl	%esi
	popl	%edx
	leave
	ret

	
	
