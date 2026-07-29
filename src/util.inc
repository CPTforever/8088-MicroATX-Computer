%ifndef UTIL_INC
%define UTIL_INC

; void busy_wait(uint16_t cx)
;   uses cx 
;   waits for i * cx cycles + j (where i and j are some constant)
busy_wait:
jcxz _busy_wait_exit
_busy_wait_loop:
loop _busy_wait_loop
_busy_wait_exit:
ret

; void busy_wait_32(uint32_t dx:ax)
;   use ax, cx, dx
;   busy waits for i * (dx * 0xffff) + j * ax + k (where i, j, k are some constant)
busy_wait_32:
mov ax, cx
call busy_wait

test dx, 0
jz _busy_wait_32_exit
_busy_wait_32_loop:
mov cx, 0xffff
call busy_wait
dec dx
jnz _busy_wait_32_loop
_busy_wait_32_exit:
ret

%endif
