.global _start								// startpunt

_start:
	mov x0, 0x0F
	mov x8, 93
	svc 0
	
