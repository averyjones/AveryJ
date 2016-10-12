.syntax unified

.text

.align 8
.global bitAnd_ARM
.func bitAnd_ARM, bitAnd_ARM
.type bitAnd_ARM, %function



bitAnd_ARM:
    @ Save caller's registers on the stack
    push {r4-r11, ip, lr}

	MVN  r0, r0			@ x = ~x
	MVN  r1, r1			@ y = ~y
	ORR  r2, r1, r0		@ z = x|y
	MVN  r0, r2			@ return ~z

    @ restore caller's registers
    pop {r4-r11, ip, lr}

    @ ARM equivalent of return
    BX lr
.endfunc



.global getByte_ARM
.func getByte_ARM, getByte_ARM
.type getByte_ARM, %function

getByte_ARM:
    @ Save caller's registers on the stack
    push {r4-r11, ip, lr}

	@ r0 = x, r1 = n, r2 = 8, r3 = 8*n
	MOV  r2, #8
    MUL  r3, r2, r1		
    ASR  r0, r0, r3		@ x = x >> (8*n)
    AND  r0, 0xFF		@ return (x & 0xFF)
    
    @ restore caller's registers
    pop {r4-r11, ip, lr}

    @ ARM equivalent of return
    BX lr
.endfunc




.global logicalShift_ARM
.func logicalShift_ARM, logicalShift_ARM
.type logicalShift_ARM, %function

logicalShift_ARM:
    @ Save caller's registers on the stack
    push {r4-r11, ip, lr}

	@ r0 = x, r1 = n, r2 = isZero, r3 = mask, 
	@ r4 = 31+isZero, r5 = 0x10000000, r6 = ~0, r7 = n + ~0, r8 = 1
	
    ORR  r2, r1, #0		@ setting isZero
    EOR  r2, r2, #1
    
    LSR  r0, r0, r1		@ x = x >> n
    
    ADD  r4, r2, #31	@ creating the mask
    MOV  r8, #1
    LSL  r5, r8, r4
    MVN  r6, #0
    ADD  r7, r6, r1
    ASR  r3, r5, r7
    MVN  r3, r3
    
    AND  r0, r0, r3		@ return (x&mask)
    
    @ restore caller's registers
    pop {r4-r11, ip, lr}

    @ ARM equivalent of return
    BX lr
.endfunc




.global bitCount_ARM
.func bitCount_ARM, bitCount_ARM
.type bitCount_ARM, %function

bitCount_ARM:
    @ Save caller's registers on the stack
    push {r4-r11, ip, lr}

    
    @ restore caller's registers
    pop {r4-r11, ip, lr}

    @ ARM equivalent of return
    BX lr
.endfunc




.global fitsBits_ARM
.func fitsBits_ARM, fitsBits_ARM
.type fitsBits_ARM, %function

fitsBits_ARM:
    @ Save caller's registers on the stack
    push {r4-r11, ip, lr}

    @ r0 = x, r1 = n, r3 = mask, r4 = tempX, r5 = shift, r6 = ~n
    MVN  r0, r6			@ shift = 33 + ~n
    ADD  r5, r6, #32
    
    LSL  r3, r0, r5		@ mask = x << shift
    
    ASR  r4, r3, r5		@ tempX = mask >> shift
    
    EOR  r0, r4, r0		@ x = tempX ^ x
    
    EOR  r0, r0, #1		@ returns 1 if can be represented
    
    @ restore caller's registers
    pop {r4-r11, ip, lr}

    @ ARM equivalent of return
    BX lr
.endfunc




.global negate_ARM
.func negate_ARM, negate_ARM
.type negate_ARM, %function

negate_ARM:
    @ Save caller's registers on the stack
    push {r4-r11, ip, lr}

    MVN r0, r0		@ x = ~x
    ADD r0, r0, #1	@ x += 1
    
    @ restore caller's registers
    pop {r4-r11, ip, lr}

    @ ARM equivalent of return
    BX lr
.endfunc




.global isLessOrEqual_ARM
.func isLessOrEqual_ARM, isLessOrEqual_ARM
.type isLessOrEqual_ARM, %function

isLessOrEqual_ARM:
    @ Save caller's registers on the stack
    push {r4-r11, ip, lr}

    
    @ restore caller's registers
    pop {r4-r11, ip, lr}

    @ ARM equivalent of return
    BX lr
.endfunc

.end

