
  //-----------------------------------------------------------------------------------------------//
 //										IDs: 311590707, 207064353								  //
//-----------------------------------------------------------------------------------------------//


#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "opcodes.h"
#include "shell.h"
#include <inttypes.h>
#include<limits.h> 
#include<stdbool.h>


  //-----------------------------------------------------------------------------------------------//
 //										Variables												  //
//-----------------------------------------------------------------------------------------------//
int op;    				// decoded opcode 
int rs;     			// decoded rs operand 
int rt;     			// decoded rt operand 
int rd;     			// decoded rd operand 
uint32_t uimmediate;	// decoded unsigned immediate
uint32_t target;		// decoded target
int32_t immediate;		// decoded signed immediate
int shifter;			// decoded shift amount

  //-----------------------------------------------------------------------------------------------//
 //										Helper functions										  //
//-----------------------------------------------------------------------------------------------//
int decode_opcode(uint32_t instruction) { 
	return (int) ((instruction & MASK_OPCODE) >> SHIFT_OPCODE); 
}
int decode_rs(uint32_t instruction) {
	return (int) ((instruction & MASK_RS) >> SHIFT_RS);
}
int decode_rt(uint32_t instruction) {
	return (int) ((instruction & MASK_RT) >> SHIFT_RT);
}
int16_t decode_immediate(uint32_t instruction) {
	return (int16_t) ((instruction & MASK_IMM16) >> SHIFT_IMM16); 
}
uint32_t decode_target(uint32_t instruction) {
	return (uint32_t) ((instruction & MASK_IMM26) >> SHIFT_IMM26); 
}
int decode_funct(uint32_t instruction) {
	return (int) ((instruction & MASK_FUNCT) >> SHIFT_FUNCT);
}
int decode_rd(uint32_t instruction) {
	return (int) ((instruction & MASK_RD) >> SHIFT_RD);
}
int decode_shamt(uint32_t instruction) {
	return (int) ((instruction & MASK_SHAMT) >> SHIFT_SHAMT); 
}

bool signed_overflow(uint32_t source, uint32_t utarget, uint32_t result)
{
	uint32_t s_sign = source & SIGN_BIT_32;
	uint32_t t_sign = utarget & SIGN_BIT_32;
	uint32_t result_sign = result & SIGN_BIT_32;

	bool overflow;
	if (s_sign != t_sign) 
		overflow = false;

	else if (result_sign != s_sign)
		overflow = true;

	else
		overflow = false;

	return overflow;
}

  //-----------------------------------------------------------------------------------------------//
 //										Instruction by Opcode									  //
//-----------------------------------------------------------------------------------------------//


// Add Immediate 
// Opcode: 0x08
void addi() {
	if (signed_overflow(curr_state.regs[rs], immediate, curr_state.regs[rs] + immediate)) {
		printf("Error: Interger overflow exception\n");
		next_state.ip = curr_state.ip + 4;
		return;
	}
	next_state.regs[rt] = curr_state.regs[rs] + immediate;
	next_state.ip = curr_state.ip + 4;
}

//Add Immediate Unsigned 
// Opcode: 0x09
void addiu() {
	next_state.regs[rt] =  curr_state.regs[rs] + uimmediate; 
	next_state.ip = curr_state.ip + 4;
}

//AND Immediate
//Opcode: 0x0C
void andi() {
	next_state.regs[rt] = curr_state.regs[rs] & uimmediate;
	next_state.ip = curr_state.ip + 4;
}

//Branch On Equal
//Opcode: 0x04
void beq() {
	if (curr_state.regs[rs] == curr_state.regs[rt]) {
		next_state.ip = curr_state.ip + immediate; 
	} else {
		next_state.ip = curr_state.ip + 4;
	}
}

//Branch On Greater Than Zero
//Opcode: 0x07
void bgtz() {
	if (!(curr_state.regs[rs] & SIGN_BIT_32 ) && (curr_state.regs[rs] != 0)) {
		next_state.ip = curr_state.ip + immediate;
	} else {
		next_state.ip = curr_state.ip + 4;
	}
}

//Branch On Less Than Or Equal Zero
//Opcode: 0x06
void blez() {
	if ((curr_state.regs[rs] & SIGN_BIT_32 ) || curr_state.regs[rs] == 0) {
		next_state.ip = curr_state.ip + immediate;
	} else {
		next_state.ip = curr_state.ip + 4; 
	}
}

//Branch On Not Equal Zero
//Opcode: 0x05
void bne() {
	if (curr_state.regs[rs] != curr_state.regs[rt]) {
		next_state.ip = curr_state.ip + immediate;
	} else {
		next_state.ip = curr_state.ip + 4;
	}
}

//Jump 
//Opcode: 0x02
void j() {
	uint32_t current_addr = (curr_state.ip & 0xF0000000);  //maybe 0xe0000000
	next_state.ip = current_addr + target; 
}

//Jump And Link
//Opcode: 0x03
void jal() {
	uint32_t current_addr = (curr_state.ip & 0xF0000000); // maybe 0xe0000000
	next_state.ip = current_addr + target; 
	next_state.regs[$ra] = curr_state.ip + 4;
}

//Load Byte
//Opcode: 0x20
void lb() {
	uint32_t address = curr_state.regs[rs] + immediate;
	int8_t byte = (int8_t) (mem_read_32(address) & 0x000000FF); 
	next_state.regs[rt] = (int32_t) byte; 
	next_state.ip = curr_state.ip + 4; 
}

//Load Byte Unsigned
//Opcode: 0x24
void lbu() {
	uint32_t address = curr_state.regs[rs] + immediate;	
	uint8_t byte = (uint8_t) (mem_read_32(address) & 0x000000FF); 
	next_state.regs[rt] = (uint32_t) byte; 
	next_state.ip = curr_state.ip + 4; 
}

//Load Halfword
//Opcode: 0x21
void lh() {
	uint32_t address = curr_state.regs[rs] + immediate;
	int16_t halfword = (int16_t) (mem_read_32(address) & 0x0000FFFF);
	next_state.regs[rt] = (int32_t) halfword; 
	next_state.ip = curr_state.ip + 4;
}

//Load Halfword Unsigned
//Opcode: 0x25
void lhu() {
	uint32_t address = curr_state.regs[rs] + immediate;
	uint16_t halfword = (uint16_t) (mem_read_32(address) & 0x0000FFFF);
	next_state.regs[rt] = (uint32_t) halfword; 
	next_state.ip = curr_state.ip + 4;
}

//Load Upper Immediate 
//Opcode: 0x0F
void lui() {
	next_state.regs[rt] = immediate; 
	next_state.ip = curr_state.ip + 4;
}

//Load Word
//Opcode: 0x23
void lw() {
	uint32_t address = curr_state.regs[rs] + immediate; 
	next_state.regs[rt] = mem_read_32(address); 
	next_state.ip = curr_state.ip + 4; 
}

//OR Immediate  
//Opcode: 0x0D
void ori() {
	next_state.regs[rt] = curr_state.regs[rs] | uimmediate;
	next_state.ip = curr_state.ip + 4;
}

//Store Byte 
//Opcode: 0x28
void sb() {
	uint32_t address = curr_state.regs[rs] + immediate;
	uint32_t byte = (curr_state.regs[rt] & 0x000000FF);
	mem_write_32(address, byte);
	next_state.ip = curr_state.ip + 4;
}

//Store Halfword
//Opcode: 0x29
void sh() {
	uint32_t address = curr_state.regs[rs] + immediate;
	uint32_t byte = (curr_state.regs[rt] & 0x0000FFFF);
	mem_write_32(address, byte);
	next_state.ip = curr_state.ip + 4;
}


//Set On Less Than Immediate 
//Opcode: 0x0A
void slti() {
	if (((int32_t) curr_state.regs[rs]) < immediate) {
		next_state.regs[rt] = (uint32_t) 1;
	} else {
		next_state.regs[rt] = (uint32_t) 0; 
	}
	next_state.ip = curr_state.ip + 4;
}

//Set On Less Than Immediate Unsigned
//Opcode: 0x0B
void sltiu() {
	if (curr_state.regs[rs] < ((uint32_t) immediate)) {
		next_state.regs[rt] = (uint32_t) 1;
	} else {
		next_state.regs[rt] = (uint32_t) 0; 
	}
	next_state.ip = curr_state.ip + 4;
}

//Store Word
//Opcode: 0x2B
void sw() {
	uint32_t address = curr_state.regs[rs] + immediate;
	mem_write_32(address, curr_state.regs[rt]);
	next_state.ip = curr_state.ip + 4;
}

//Exclusive OR Immediate  
//Opcode: 0x0E
void xori() {
	next_state.regs[rt] = curr_state.regs[rs] ^ uimmediate;
	next_state.ip = curr_state.ip + 4;
}


  //-----------------------------------------------------------------------------------------------//
 //										Instruction by Special									  //
//-----------------------------------------------------------------------------------------------//

//Add 
//SPECIAL: 0x20
void add() {
	int32_t source = (int32_t) curr_state.regs[rs];
	int32_t itarget = (int32_t) curr_state.regs[rt];
	if (signed_overflow(source, itarget, source + itarget)) {
		printf("Error: Interger overflow exception\n");
		next_state.ip = curr_state.ip + 4;
		return;
	}
	next_state.regs[rd] = source + itarget; 
	next_state.ip = curr_state.ip + 4;
}

//Add Unsigned 
//SPECIAL: 0x21
void addu() {
	int32_t source = (int32_t) curr_state.regs[rs];
	int32_t itarget = (int32_t) curr_state.regs[rt];
	next_state.regs[rd] = source + itarget; 
	next_state.ip = curr_state.ip + 4;
}

//And
//SPECIAL: 0x24
void and() {
	next_state.regs[rd] = curr_state.regs[rs] & curr_state.regs[rt];
	next_state.ip = curr_state.ip + 4;
}

//Jump And Link Register 
//SPECIAL: 0x09
void jalr() {
	next_state.regs[rd] = curr_state.ip + 4;
	next_state.ip = curr_state.regs[rs];
}

//Jump Register 
//SPECIAL: 0x08
void jr() {
	next_state.ip = curr_state.regs[rs]; 
}

//Nor 
//SPECIAL: 0x27
void nor() {
	next_state.regs[rd] = ~(curr_state.regs[rs] | curr_state.regs[rt]);
	next_state.ip = curr_state.ip + 4;
}

//Or
//SPECIAL: 0x25
void or() {
	next_state.regs[rd] = curr_state.regs[rs] | curr_state.regs[rt];
	next_state.ip = curr_state.ip + 4;
}

//Shift Left Logical
//SPECIAL: 0x00
void sll() {
	next_state.regs[rd] = (curr_state.regs[rt] << shifter); 
	next_state.ip = curr_state.ip + 4;
} 

//Shift Left Logical Variable
//SPECIAL: 0x04
void sllv() {
	shifter = (curr_state.regs[rs] & 0x000001F);
	next_state.regs[rd] = (curr_state.regs[rt] << shifter); 
	next_state.ip = curr_state.ip + 4;
}

//Set On Less Than
//SPECIAL: 0x2A
void slt() {
	int32_t source = (int32_t) curr_state.regs[rs];
	int32_t itarget = (int32_t) curr_state.regs[rt];
	if (source < itarget) {
		next_state.regs[rd] = 1;
	} else {
		next_state.regs[rd] = 0; 
	}
	next_state.ip = curr_state.ip + 4;
}

//Set On Less Than Unsigned 
//SPECIAL: 0x2B
void sltu() {
	uint32_t source = (uint32_t) curr_state.regs[rs];
	uint32_t utarget = (uint32_t) curr_state.regs[rt];
	if (source < utarget) {
		next_state.regs[rd] = 1;
	} else {
		next_state.regs[rd] = 0; 
	}
	next_state.ip = curr_state.ip + 4;
}

//Shift Right Arithmetic
//SPECIAL: 0x03
void sra() {
	uint32_t result = (int32_t)curr_state.regs[rt] >> (int32_t)shifter; 
	next_state.regs[rd] = result;
	next_state.ip = curr_state.ip + 4;
}

//Shift Right Arithmetic Variable
//SPECIAL: 0x07
void srav() {
	shifter = (curr_state.regs[rs] & 0x000001F);
	uint32_t result = curr_state.regs[rt] >> shifter; 
	next_state.regs[rd] = result;
	next_state.ip = curr_state.ip + 4;
}

//Shift Right Logical
//SPECIAL: 0x02
void srl() {
	next_state.regs[rd] = (curr_state.regs[rt] >> shifter);
	next_state.ip = curr_state.ip + 4;
}

//Shift Right Logical Variable
//SPECIAL: 0x06
void srlv() {
	int shifter = (curr_state.regs[rs] & 0x000001F);
	next_state.regs[rd] = (curr_state.regs[rt] >> shifter); 
	next_state.ip = curr_state.ip + 4;
}

//Subtract
//SPECIAL: 0x22
void sub() {
	int32_t source = (int32_t) curr_state.regs[rs];
	int32_t itarget = (int32_t) curr_state.regs[rt];
	if (signed_overflow(source, itarget, source + itarget)) {
		printf("Error: Interger overflow exception\n");
		next_state.ip = curr_state.ip + 4;
		return;
	}
	next_state.regs[rd] = source - itarget;
	next_state.ip = curr_state.ip + 4;
}

//Subtract Unsigned 
//SPECIAL: 0x23
void subu() {
	int32_t source = (int32_t) curr_state.regs[rs];
	int32_t itarget = (int32_t) curr_state.regs[rt];
	next_state.regs[rd] = source - itarget;
	next_state.ip = curr_state.ip + 4;
}

//System Call
//SPECIAL: 0x0C
void syscall() {
	if (curr_state.regs[$v0] == SYSCALL_EXIT) {
		running = 0; 
		return;
	} 	
	next_state.ip = curr_state.ip + 4;
}

//Exclusive Or
//SPECIAL: 0x26
void xor() {
	next_state.regs[rd] = curr_state.regs[rs] ^ curr_state.regs[rt];
	next_state.ip = curr_state.ip + 4;
}


  //-----------------------------------------------------------------------------------------------//
 //										Instruction by REGIMM									  //
//-----------------------------------------------------------------------------------------------//

//Branch On Greater Than Or Equal To Zero
//REGIMM: 0x01
void bgez() {
	if (!(curr_state.regs[rs] & SIGN_BIT_32 )) {
		next_state.ip = curr_state.ip + immediate;
	} else {
		next_state.ip = curr_state.ip + 4;
	}
}

//Branch On Greater Than Or Equal To Zero And Link
//REGIMM: 0x11
void bgezal() {
	next_state.regs[$ra] = curr_state.ip + 4;
	if (!(curr_state.regs[rs] & SIGN_BIT_32)) {
		next_state.ip = curr_state.ip + immediate;
	} else {
		next_state.ip = curr_state.ip + 4;
	}
}

//Branch On Less Than Zero 
//REGIMM: 0x00
void bltz() {
	if ((curr_state.regs[rs] & SIGN_BIT_32 )) {
		next_state.ip = curr_state.ip + immediate;
	} else {
		next_state.ip = curr_state.ip + 4;
	}
}

//Branch On Less Than Zero And Link
//REGIMM: 0x10
void bltzal() {
	next_state.regs[$ra] = curr_state.ip + 4;
	if ((curr_state.regs[rs] & SIGN_BIT_32 )) {
		next_state.ip = curr_state.ip + immediate;
	} else {
		next_state.ip = curr_state.ip + 4;
	}
}

  //-----------------------------------------------------------------------------------------------//
 //										Instruction processing									  //
//-----------------------------------------------------------------------------------------------//


void process_instruction() {
	// fetch the instruction from memory
	uint32_t instruction = mem_read_32(curr_state.ip); 
	// decode the opcode from the instruction 
	op = decode_opcode(instruction);
	int special;
	int regimm;
	//continue and decode based on states reached
	switch (op)
    {
		//by OPCODE_SPECIAL
        case OPCODE_SPECIAL: 
			special = decode_funct(instruction);
			rs = decode_rs(instruction);
			rt = decode_rt(instruction);
			rd = decode_rd(instruction);
            switch (special)
            {
                case SPECIAL_ADD: 
					add();
					break;
                case SPECIAL_ADDU: 
					addu();
                    break;
				case SPECIAL_AND:
					and();
					break;
				case SPECIAL_JALR:
				    jalr();
					break;
				case SPECIAL_JR:
					jr();
					break;
				case SPECIAL_NOR:
					nor();
					break;
				case SPECIAL_OR:
					or();
					break;
				case SPECIAL_SLL:
					shifter = decode_shamt(instruction);
					sll(instruction);
					break;
				case SPECIAL_SLLV:
					sllv();
					break;
				case SPECIAL_SLT:
					slt();
					break;
				case SPECIAL_SLTU:
					sltu();
					break;
				case SPECIAL_SRA:
					shifter = decode_shamt(instruction);
					sra();
					break;
				case SPECIAL_SRAV:
					srav();
					break;
				case SPECIAL_SRL:
					shifter = decode_shamt(instruction);
					srl();
					break;
				case SPECIAL_SRLV:
					srlv();
					break;
				case SPECIAL_SUB:
					sub();
					break;
				case SPECIAL_SUBU:
					subu();
					break;
				case SPECIAL_SYSCALL:
					syscall();
					break;
				case SPECIAL_XOR:
					xor();
					break;
            }
            break;
		//by OPCODE_REGIMM
		case OPCODE_REGIMM: 
			regimm = decode_rt(instruction);
			rs = decode_rs(instruction);
            switch (regimm)
            {
                case REGIMM_BGEZ:
					immediate = (int32_t)(decode_immediate(instruction) << 2);
					bgez(instruction);
					break;
				case REGIMM_BGEZAL:
					immediate = (int32_t)(decode_immediate(instruction) << 2);
					bgezal();
					break;
				case REGIMM_BLTZ:
					immediate = (int32_t)(decode_immediate(instruction) << 2);
					bltz();
					break;
				case REGIMM_BLTZAL:
					immediate = (int32_t)((int32_t)decode_immediate(instruction) << 2);
					bltzal();
					break;
            }
            break;
		//else by OPCODE
        case OPCODE_ADDI:
			rs = decode_rs(instruction);
			rt = decode_rt(instruction);
			immediate = (int32_t)decode_immediate(instruction);
			addi();
			break;
        case OPCODE_ADDIU:
			rs = decode_rs(instruction);
			rt = decode_rt(instruction);
			uimmediate = (uint32_t)decode_immediate(instruction);
			addiu();
            break;
		case OPCODE_ANDI:
			rs = decode_rs(instruction);
			rt = decode_rt(instruction);
			uimmediate = (uint32_t)decode_immediate(instruction);
			andi(instruction);
		case OPCODE_BEQ:
			rs = decode_rs(instruction);
			rt = decode_rt(instruction);
			immediate = (int32_t)(decode_immediate(instruction) << 2);
			beq();
			break;
		case OPCODE_BGTZ:
			rs = decode_rs(instruction);
			rt = decode_rt(instruction);
			immediate = (int32_t)(decode_immediate(instruction) << 2);
			bgtz();
			break;
		case OPCODE_BLEZ:
			rs = decode_rs(instruction);
			rt = decode_rt(instruction);
			immediate = (int32_t)(decode_immediate(instruction) << 2);
			blez();
			break;
		case OPCODE_BNE:
			rs = decode_rs(instruction);
			rt = decode_rt(instruction);
			immediate = (int32_t)(decode_immediate(instruction) << 2);
			bne();
			break;
		case OPCODE_J:
			rs = decode_rs(instruction);
			rt = decode_rt(instruction);
			target = (decode_target(instruction) << 2);
			j();
			break;
		case OPCODE_JAL:
			rs = decode_rs(instruction);
			rt = decode_rt(instruction);
			target = (decode_target(instruction) << 2);
			jal();
			break;
		case OPCODE_LB:
			rs = decode_rs(instruction);
			rt = decode_rt(instruction);
			immediate = (int32_t)decode_immediate(instruction);
			lb();
			break;
		case OPCODE_LBU:
			rs = decode_rs(instruction);
			rt = decode_rt(instruction);
			immediate = (int32_t)decode_immediate(instruction);
			lbu();
			break;
		case OPCODE_LH:
			rs = decode_rs(instruction);
			rt = decode_rt(instruction);
			immediate = (int32_t)decode_immediate(instruction);
			lh();
			break;
		case OPCODE_LHU:
			rs = decode_rs(instruction);
			rt = decode_rt(instruction);
			immediate = (int32_t)decode_immediate(instruction);
			lhu();
			break;
		case OPCODE_LUI:
			rs = decode_rs(instruction);
			rt = decode_rt(instruction);
			immediate = (int32_t)((decode_immediate(instruction) << 16) & 0xFFFF0000); //maybe 8
			lui();
			break;
		case OPCODE_LW:
			rs = decode_rs(instruction);
			rt = decode_rt(instruction);
			immediate = (int32_t)decode_immediate(instruction);
			lw();
			break;
		case OPCODE_ORI:
			rs = decode_rs(instruction);
			rt = decode_rt(instruction);
			uimmediate = (uint32_t)decode_immediate(instruction);
			uimmediate = MASK_IMM16 & uimmediate;
			ori();
			break;
		case OPCODE_SB:
			rs = decode_rs(instruction);
			rt = decode_rt(instruction);
			immediate = (int32_t)decode_immediate(instruction);
			sb();
			break;
		case OPCODE_SH:
			rs = decode_rs(instruction);
			rt = decode_rt(instruction);
			immediate = (int32_t)decode_immediate(instruction);
			sh();
			break;
		case OPCODE_SLTI:
			rs = decode_rs(instruction);
			rt = decode_rt(instruction);
			immediate = (int32_t)decode_immediate(instruction);
			slti();
			break;
		case OPCODE_SLTIU:
			rs = decode_rs(instruction);
			rt = decode_rt(instruction);
			immediate = (int32_t)decode_immediate(instruction);
			sltiu();
			break;
		case OPCODE_SW:
			rs = decode_rs(instruction);
			rt = decode_rt(instruction);
			immediate = (int32_t)decode_immediate(instruction);
			sw();
			break;
		case OPCODE_XORI:
			rs = decode_rs(instruction);
			rt = decode_rt(instruction);
			uimmediate = (uint32_t)decode_immediate(instruction);
			xori();
			break;
	}	
}








