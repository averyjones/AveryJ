.syntax unified

.text

.align 8
.global bitAnd_ARM
.func bitAnd_ARM, bitAnd_ARM
.type bitAnd_ARM, %function



bitAnd_ARM:
    @ Save caller's registers on the stack
    push {r4-r11, ip, lr}

	@ compute AND by flipping the inputs, ORing them together, and 
	@ flipping the result

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

	@ shift the desired byte to the LSByte spot and isolate it using AND

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

	@ determine if x is zero, then create a mask to change the possible 
	@ sign fill into the MSB to be zero/logical

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

    @ count the number of bits set to 1 by isolating each bit and shifting
    
    @ r0 = x, r1 = left add, r2 = right add, r3 = shift right value
    AND  r1, r0, #0x55555555		@ x = (x&a) + ((x>>1)&a)
    LSR  r3, r0, #1
    AND  r2, r3 #0x55555555
    ADD  r0, r1, r2
    AND  r1, r0, #0x33333333		@ x = (x&b) + ((x>>2)&b)
    LSR  r3, r0, #2
    AND  r2, r3 #0x33333333
    ADD  r0, r1, r2
    AND  r1, r0, #0x0F0F0F0F		@ x = (x&c) + ((x>>4)&c)
    LSR  r3, r0, #4
    AND  r2, r3 #0x0F0F0F0F
    ADD  r0, r1, r2
    AND  r1, r0, #0x00FF00FF		@ x = (x&d) + ((x>>8)&d)
    LSR  r3, r0, #8
    AND  r2, r3 #0x00FF00FF
    ADD  r0, r1, r2
    AND  r1, r0, #0x0000FFFF		@ x = (x&e) + ((x>>16)&e)
    LSR  r3, r0, #16
    AND  r2, r3 #0x0000FFFF
    ADD  r0, r1, r2
    
    
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

	@ find if an integer can be represented by shifting it back and 
	@ forth then checking if still equals the original

    @ r0 = x, r1 = n, r3 = mask, r4 = tempX, r5 = shift, r6 = ~n
    MVN  r6, r1			@ shift = 33 + ~n
    ADD  r5, r6, #33
    
    LSL  r3, r0, r5		@ mask = x << shift
    
    ASR  r4, r3, r5		@ tempX = mask >> shift
    
    EOR  r0, r4, r0		@ x = tempX ^ x
    
    @ r7 = ~x, r8 = -x, r9 = ~(-x)
    MVN  r7, r0			@ x = !x
    ADD  r8, r7, #1
    MVN  r9, r8
    AND  r0, r9, r7
    MOV  r10, #31
    LSR  r0, r0, r10
    AND  r0, #1
    
    
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
    
    @ negate using the rules for 2's complement (flip bits and add 1)

	@ r0 = x
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
    
    @ determine if x is less than or equal to y by subtracting x from y 
    @ and finding the sign of the difference

	@ r0 = x, r1 = y, r2 = difference, r3 = signDiff, r4 = (~x + 1), r5 = ~x
	MVN  r5, r0				@ difference = y + (~x + 1)
	ADD  r4,  r0, #1
	ADD  r2, r4, r1
	LSR  r2, r2, #31 		@ signDiff = (difference >> 31) & 1
	AND  r3, r2, #1
	
	@ r5 = ~x, r6 = -x, r7 = ~(-x)
	ADD  r6, r5, #1			@ return !signDiff
	MVN  r7, r6
	AND  r0, r7, r5
	LSR  r0, r0, #31
	AND  r0, r0, #1
	
    
    @ restore caller's registers
    pop {r4-r11, ip, lr}

    @ ARM equivalent of return
    BX lr
.endfunc

.end

