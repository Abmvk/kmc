.global 	_start

.section 	.data
	message: .asciz "Hello, World!\n"

.section 	.text

_start:
	mov x0, 1
	ldr x1, =message
	mov x2, 14
	mov x8, 64
	svc 0

	mov x8, 93
	mov x0, 0
	svc 0

