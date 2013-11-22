        ;;
        ;; ___delay32
        ;;
        ;; 32-bit cycle delay
        ;;
        ;; inputs:
        ;;   w1:w0 = delay in cycles (min == 12, including call)
        ;; outputs:
        ;;   none
        ;; registers used:
        ;;   w0,w1
        ;;
	.ifndef ffunction
	.section .init, code
	.else 
	.section .init.delay32, code
	.endif
        .global ___delay32
___delay32:

        sub  #1023,w0
        subb #0,w1
        bra  lt,2f

4:      repeat #1006
        nop

        sub  #1012, w0
        subb #0, w1
        bra  ge, 4b
        add  #1,w0
2:      add  #1010,w0
        bra  lt,3f
        repeat w0
        nop
3:      return

.include "null_signature.s"

