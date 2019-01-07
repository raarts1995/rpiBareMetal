.text

.section ".text.startup"
.global _start, _lock, _unlock

// From the ARM ARM (Architecture Reference Manual). Make sure you get the
// ARMv5 documentation which includes the ARMv6 documentation which is the
// correct processor type for the Broadcom BCM2835. The ARMv6-M manuals
// available on the ARM website are for Cortex-M parts only and are very
// different.
//
// See ARM section A2.2 (Processor Modes)

.equ    CPSR_MODE_USER,         0x10
.equ    CPSR_MODE_FIQ,          0x11
.equ    CPSR_MODE_IRQ,          0x12
.equ    CPSR_MODE_SVR,          0x13
.equ    CPSR_MODE_ABORT,        0x17
.equ    CPSR_MODE_UNDEFINED,    0x1B
.equ    CPSR_MODE_SYSTEM,       0x1F

// See ARM section A2.5 (Program status registers)
.equ    CPSR_IRQ_INHIBIT,       0x80
.equ    CPSR_FIQ_INHIBIT,       0x40
.equ    CPSR_THUMB,             0x20

_start:
    // **********************************************************************
    //  LAB ASSIGNMENT: IMPLEMENT VECTOR TABLE HERE
    // **********************************************************************
	ldr pc, _reset_h
	ldr pc, _undefined_instruction_vector_h
	ldr pc, _software_interrupt_vector_h
	ldr pc, _prefetch_abort_vector_h
	ldr pc, _data_abort_vector_h
	ldr pc, _unused_handler_h
	ldr pc, _interrupt_vector_h
	ldr pc, _fast_interrupt_vector_h

_reset_h:                           .word   _reset_
_undefined_instruction_vector_h:    .word   _reset_ //undefined_instruction_vector
_software_interrupt_vector_h:       .word   software_interrupt_vector
_prefetch_abort_vector_h:           .word   prefetch_abort_vector
_data_abort_vector_h:               .word   data_abort_vector
_unused_handler_h:                  .word   _reset_
_interrupt_vector_h:                .word   interrupt_vector
_fast_interrupt_vector_h:           .word   fast_interrupt_vector
	
_reset_:
	// We enter execution in supervisor mode. For more information on
    // processor modes see ARM Section A2.2 (Processor Modes)

    // **********************************************************************
    //  LAB ASSIGNMENT: IMPLEMENT CODE TO PLACE VECTOR TABLE AT ADDRESS 0x00
    //***********************************************************************
	mov     r0, #0x8000
	mov     r1, #0x0000
	ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
	stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}
	ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
	stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}
	
    // We are going to use interrupt mode, so setup the interrupt mode
    // stack pointer which differs to the application stack pointer:
    mov r0, #(CPSR_MODE_IRQ | CPSR_IRQ_INHIBIT | CPSR_FIQ_INHIBIT )
    msr cpsr_c, r0
    mov sp, #(63 * 1024 * 1024)

    // Switch back to supervisor mode (our application mode) and
    // set the stack pointer towards the end of RAM. Remember that the
    // stack works its way down memory, our heap will work its way
    // up memory toward the application stack.
    mov r0, #(CPSR_MODE_SVR | CPSR_IRQ_INHIBIT | CPSR_FIQ_INHIBIT )
    msr cpsr_c, r0

    // Set the stack pointer at some point in RAM that will not harm us
    // It is different from the IRQ stack pointer above and no matter
    // what the GPU/CPU memory split, 64MB is available to the CPU
    // Keep it within the limits and also keep it aligned to a 32-bit
    // boundary!
    mov sp, #(64 * 1024 * 1024)

    // The c-startup function which we never return from. This function will
    // initialise the ro data section (most things that have the const
    // declaration) and initialise the bss section variables to 0 (generally
    // known as automatics). It will then call main, which should never return.
    bl      _cstartup

    // If main does return for some reason, just catch it and stay here.
_inf_loop:
    b       _inf_loop

_lock: 								// mask out IRQ interrupts
	MRS r0, cpsr
	ORR r0, r0, #0x80 				// set I bit means MASK out IRQ interrupts
	MSR cpsr, r0
	mov pc, lr

_unlock: 							// mask in IRQ interrupts
	MRS r0, cpsr
	BIC r0, r0, #0x80 				// clr I bit means MASK in IRQ interrupts
	MSR cpsr, r0
	mov pc, lr
