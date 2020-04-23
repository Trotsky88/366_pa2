
        global  _set_bit_elem
        global  _get_bit_elem
        section .text

_set_bit_elem:
                push rbp            ; save the base pointer on the stack (at rsp+8)
                mov rbp, rsp        ; set up the rbp for the bottom of this frame
                mov rax, rdx
                imul rax, rsi
                add rax, rcx
                mov rbx, rax
                sar rax, 3
                sal rax, 3
                sub rbx, rax
                mov rax, 8
                sub rax, rbx
                dec rax
                mov rbx, 0
                mov rsi, 1
                begin_shift:
                    cmp rbx, rax
                    je complete
                shift_left:
                    sal rsi, 1
                    inc rbx
                    jmp begin_shift
                complete:
                mov rax, rdx
                mov rbx, 10
                imul rax, rbx
                add rax, rcx
                sar rax, 3
                or [rdi+rax], rsi
                mov rsp, rbp        ; restore stack pointer to before we pushed parameters onto the stack
                pop rbp             ; remove rbp from the stack to restore rsp to initial value
                ret



_get_bit_elem:
        push rbp            ; save the base pointer on the stack (at rsp+8)
        mov rbp, rsp        ; set up the rbp for the bottom of this frame

        mov rax, rdx
                imul rax, rsi
                add rax, rcx
                mov rbx, rax
                sar rax, 3
                sal rax, 3
                sub rbx, rax
                mov rax, 8
                sub rax, rbx
                dec rax
                mov rbx, 0
                mov rsi, 1
                check_begin_shift:
                    cmp rbx, rax
                    je check_complete
                check_shift_left:
                    sal rsi, 1
                    inc rbx
                    jmp check_begin_shift
                check_complete:
                mov rax, rdx
                mov rbx, 10
                imul rax, rbx
                add rax, rcx
                sar rax, 3
                and [rdi+rax], rsi
                mov rax, [rdi+rax]
                cmp rax, 0
                setg al
                movsx rax, al

        mov rsp, rbp        ; restore stack pointer to before we pushed parameters onto the stack
        pop rbp             ; remove rbp from the stack to restore rsp to initial value
        ret                 ; return value in rax
