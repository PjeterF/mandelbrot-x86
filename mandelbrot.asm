section .data
test: times 10 db 'a'
section .text

	global mandelbrot

mandelbrot:
	push ebp
	mov ebp, esp
	
	push ebx
	push esi
	push edi

	; main body
	
	mov eax, [ebp+8]
	call translate
	mov [ebp+8], eax
	
	mov eax, [ebp+12]
	call translate
	mov [ebp+12], eax
	
	mov esi, 0 ; real part of Z
	mov edi, 0 ; imaginary part of Z
	
	mov ecx, 0 ; maximum number of iterations
loop:
	cmp ecx, 100
	je end
	
	; calculate Z*Z
	
	; real part
	mov eax, esi
	mov ebx, esi
	call multiply
	mov edx, eax
	
	mov eax, edi
	mov ebx, edi
	call multiply
	
	sub edx, eax ; edx - calculated real part
	
	; imaginary part
	mov eax, 2
	shl eax, 16
	mov ebx, esi
	call multiply
	mov ebx, edi
	call multiply
	 
	mov esi, edx
	mov edi, eax
	
	add esi, [ebp+8]
	add edi, [ebp+12]
	
	mov edx, 2
	shl edx, 16
	
	cmp esi, edx
	jg end
	
	cmp edi, edx
	jg end
	
	mov edx, -2
	shl edx, 16
	
	cmp esi, edx
	jl end
	
	cmp edi, edx
	jl end
	
	inc ecx
	jmp loop
	
end:
	;return value is in eax
	mov eax, ecx	
		
	pop edi
	pop esi
	pop ebx

	pop ebp
	ret
	
; eax, ebx - numbers to multiply | returns result in eax
multiply:
	push edx

	imul ebx
	shl edx, 16
	shr eax, 16
	or eax, edx
	
	pop edx
	ret

; eax - pixel index | returns result in eax
translate:
	push ebx
	push ecx

	shl eax, 16
	
	mov cl, [ebp+16]
	sub cl, 2
	shr eax, cl
	
	mov ebx, 2
	shl ebx, 16
	
	sub eax, ebx
	
	pop ecx
	pop ebx
	ret
	
section .data
minus : dd 0xFFFE0000 ;-2
divisor: dd 0x00400000 ;64
divisor_c: dd 0x00000400 ;1/64
