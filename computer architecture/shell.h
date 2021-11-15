/**
 *
 *   MIPS-32 Instruction Level Simulator
 *
 *   Architecture course
 *   Tel Hai College 2019
 *
 */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! *
 *                                                              *
 *                                          !אין לשנות קובץ זה                                                       *
 *                 sim.c מותר לשנות רק את                                                   *
 *                                                              *
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#ifndef _SIM_SHELL_H_
#define _SIM_SHELL_H_

#include <stdint.h>

#define FALSE 0
#define TRUE  1

#define MIPS_REGS 32

#define MAX_STR 20000   // longest input string supported

typedef struct CpuStateStruct {

  uint32_t ip;		    /* instruction pointer */
  uint32_t regs[MIPS_REGS]; /* register file. */
  uint32_t hi, lo;          /* special regs for mult/div. */
} CpuState;

/* Data Structure for Latch */

extern CpuState curr_state, next_state;

extern int running; /* run bit */

extern int heap_avail;
extern uint8_t *heap_base;

uint32_t mem_read_32(uint32_t address);
void     mem_write_32(uint32_t address, uint32_t value);

/* YOU IMPLEMENT THIS FUNCTION */
void process_instruction();

#endif
