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

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

#include "shell.h"

/***************************************************************
 *
 * Main memory.
 *
 ***************************************************************/

#define MEM_DATA_START  0x10000000
#define MEM_DATA_SIZE   0x00100000
#define MEM_TEXT_START  0x00400000
#define MEM_TEXT_SIZE   0x00100000
#define MEM_STACK_START 0x7ff00000
#define MEM_STACK_SIZE  0x00100000
#define MEM_KDATA_START 0x90000000
#define MEM_KDATA_SIZE  0x00100000
#define MEM_KTEXT_START 0x80000000
#define MEM_KTEXT_SIZE  0x00100000

typedef struct
{
    uint32_t start, size;
    uint8_t *mem;
} MemRegion;

/* memory will be dynamically allocated at initialization */
MemRegion mem_regions[] = { { MEM_TEXT_START, MEM_TEXT_SIZE, NULL },
                            { MEM_DATA_START, MEM_DATA_SIZE, NULL },
                            { MEM_STACK_START, MEM_STACK_SIZE, NULL },
                            { MEM_KDATA_START, MEM_KDATA_SIZE, NULL },
                            { MEM_KTEXT_START, MEM_KTEXT_SIZE, NULL } };

#define MEM_NREGIONS (sizeof(mem_regions)/sizeof(MemRegion))

/***************************************************************
 *
 * Forward declarations
 *
 ***************************************************************/
void cycle();
void get_command( FILE * dumpsim_file );
void go();
void help();
void initialize( char *program_filename[], int num_prog_files );
void init_memory();
void load_program( char *program_filename );
void mdump( FILE * dumpsim_file, int start, int stop );
uint32_t mem_read_32( uint32_t address );
void mem_write_32( uint32_t address, uint32_t value );
void run( int num_cycles );
void rdump( FILE * dumpsim_file );



/***************************************************************
 *
 * CPU State info.
 *
 ***************************************************************/
CpuState curr_state, next_state;
int running; /* run bit */
int intruction_count;

/***************************************************************
 *
 * Procedure: cycle
 *
 * Purpose: Execute a cycle
 *
 ***************************************************************/
void cycle()
{

    process_instruction();
    curr_state = next_state;
    intruction_count++;
}

/***************************************************************
 *
 * Procedure: get_command
 *
 * Purpose: Read a command from standard input
 *
 ***************************************************************/
void get_command( FILE * dumpsim_file )
{
    char buffer[20];
    int start, stop, cycles;
    int register_no, register_value;
    int hi_reg_value, lo_reg_value;

    printf( "MIPS-SIM> " );

    if( scanf( "%s", buffer ) == EOF )
        exit( 0 );

    printf( "\n" );

    switch( buffer[0] )
    {
    case 'G':
    case 'g':
        go();
        break;

    case 'H':
    case 'h':
        if( scanf( "%i", &hi_reg_value ) != 1 )
            break;
        curr_state.hi = hi_reg_value;
        next_state.hi = hi_reg_value;
        break;

    case 'I':
    case 'i':
        if( scanf( "%i %i", &register_no, &register_value ) != 2 )
            break;
        curr_state.regs[register_no] = register_value;
        next_state.regs[register_no] = register_value;
        break;

    case 'L':
    case 'l':
        if( scanf( "%i", &lo_reg_value ) != 1 )
            break;
        curr_state.lo = lo_reg_value;
        next_state.lo = lo_reg_value;
        break;

    case 'M':
    case 'm':
        if( scanf( "%i %i", &start, &stop ) != 2 )
            break;

        mdump( dumpsim_file, start, stop );
        break;

    case 'Q':
    case 'q':
        printf( "Bye.\n" );
        exit( 0 );

    case 'R':
    case 'r':
          rdump( dumpsim_file );
          break;

    case 'S':
    case 's':
            if( scanf( "%d", &cycles ) != 1 )
                break;
            run( cycles );
        break;

    case '1':
            run( 1 );
        break;

    case '2':
            run( 2 );
        break;

    case '3':
            run( 3 );
        break;

    case '4':
            run( 4 );
        break;

    case '?':
        help();
        break;

    default:
        printf( "Invalid Command\n" );
        break;
    }
}

/***************************************************************
 *
 * Procedure: go
 *
 * Purpose: Simulate MIPS until HALTed
 *
 ***************************************************************/
void go()
{
    if( running == FALSE )
    {
        printf( "Can't simulate, Simulator is halted\n\n" );
        return;
    }

    printf( "Simulating...\n\n" );
    while( running )
        cycle();
    printf( "Simulator halted\n\n" );
}

/***************************************************************
 *
 * Procedure: help
 *
 * Purpose: Print out a list of commands
 *
 ***************************************************************/
void help()
{
    printf( "----------------MIPS ISIM Help------------------------------\n" );
    printf( "g                     - run program to completion           \n" );
    printf( "s <n>                 - simulate program for n instructions \n" );
    printf( "1                     - same as s 1 (execute 1 instruction) \n" );
    printf( "2                     - same as s 2 (execute 2 instructions)\n" );
    printf( "3                     - same as s 3 (execute 3 instructions)\n" );
    printf( "s <n>                 - simulate program for n instructions \n" );
    printf( "m <low> <high>        - dump memory from low to high        \n" );
    printf( "r                     - dump the register & bus value       \n" );
    printf( "i <reg_num> <reg_val> - set GPR reg_num to reg_val          \n" );
    printf( "h <value>               - set the HI register to value      \n" );
    printf( "l <value>             - set the LO register to value        \n" );
    printf( "?                     - display this help menu              \n" );
    printf( "q                     - exit the program                    \n\n" );
}

/***************************************************************
 *
 * Procedure: initialize
 *
 * Purpose: Load machine language program and set up initial state of the machine
 *
 ***************************************************************/
void initialize( char *program_filename[], int num_prog_files )
{
    int i;

    printf( "initialize\n" );

    init_memory();

    for( i = 0; i < num_prog_files; i++ )
        load_program( program_filename[i] );

    next_state = curr_state;

    running = TRUE;
}

/***************************************************************
 *
 * Procedure: init_memory
 *
 * Purpose: Allocate and zero memory
 *
 ***************************************************************/
void init_memory()
{
    printf( "init_memory\n" );
    int i;
    for( i = 0; i < MEM_NREGIONS; i++ )
    {
        mem_regions[i].mem = malloc( mem_regions[i].size );
        memset( mem_regions[i].mem, 0, mem_regions[i].size );
    }
}

/***************************************************************
 *
 * Procedure: load_program
 *
 * Purpose: Load program and service routines into memory
 *
 ***************************************************************/
void load_program( char *program_filename )
{
#define LINE_SIZE 1024
    FILE * prog;
    int ii, word;
    char code[9];

    printf( "loading program <%s>\n", program_filename );

    prog = fopen( program_filename, "r" );
    if( prog == NULL )
    {
        printf( "Error: Can't open program file %s\n", program_filename );
        exit( -1 );
    }

    /* Read in the program. */
    char *line = (char *) malloc( LINE_SIZE );
    if( line == NULL )
    {
        printf( "Error: Can't malloc() line \n" );
        exit( -1 );
    }

    ii = 0;
    int loop = 1;
    size_t size = LINE_SIZE;
    while( loop )
    {
        int nr = getline( &line, &size, prog );
        if( nr == -1 )
        {
            if( errno != 0 )
                perror( "getline" );
            loop = 0;
        }

        if( line[0] != '[' )
            continue;
        if( line[3] != '4' )
            continue;
        strncpy( code, &line[11], 8 );
        code[8] = '\0';
        printf( "%s\n", code );
        sscanf( code, "%x\n", &word );
//        printf( "%x   %d <%s>\n", word, nr, line );
        mem_write_32( MEM_TEXT_START + ii, word );
        ii += 4;
    }

    free( line );

    curr_state.ip = MEM_TEXT_START;

    printf( "Read %d words from program into memory.\n\n", ii / 4 );
}

/***************************************************************
 *
 * Procedure: mdump
 *
 * Purpose: Dump a word-aligned region of memory to the output file.
 *
 ***************************************************************/
void mdump( FILE * dumpsim_file, int start, int stop )
{
    int address;

    printf( "\nMemory content [0x%08x..0x%08x] :\n", start, stop );
    printf( "-------------------------------------\n" );
    for( address = start; address <= stop; address += 4 )
        printf( "  0x%08x (%d) : 0x%08x\n", address, address, mem_read_32( address ) );
    printf( "\n" );

    /* dump the memory contents into the dumpsim file */
    fprintf( dumpsim_file, "\nMemory content [0x%08x..0x%08x] :\n", start, stop );
    fprintf( dumpsim_file, "-------------------------------------\n" );
    for( address = start; address <= stop; address += 4 )
        fprintf( dumpsim_file, "  0x%08x (%d) : 0x%08x\n", address, address,
                mem_read_32( address ) );
    fprintf( dumpsim_file, "\n" );
}

/***************************************************************
 *
 * Procedure: mem_read_32
 *
 * Purpose: Read a 32-bit word from memory
 *
 * Assumes little endian memory arrangement
 *
 ***************************************************************/
uint32_t mem_read_32( uint32_t address )
{
    int i;
    for( i = 0; i < MEM_NREGIONS; i++ )
    {
        if( (address >= mem_regions[i].start)
                && (address < (mem_regions[i].start + mem_regions[i].size)) )
        {
            uint32_t offset = address - mem_regions[i].start;
            uint32_t result = mem_regions[i].mem[offset];
            result |= mem_regions[i].mem[offset + 1] << 8;
            result |= mem_regions[i].mem[offset + 2] << 16;
            result |= mem_regions[i].mem[offset + 3] << 24;
            return (result);
        }
    }

    return 0;
}

/***************************************************************
 *
 * Procedure: mem_write_32
 *
 * Purpose: Write a 32-bit word to memory
 *
 * Assumes little endian memory arrangement
 *
 ***************************************************************/
void mem_write_32( uint32_t address, uint32_t value )
{
    int i;
    for( i = 0; i < MEM_NREGIONS; i++ )
    {
        if( address >= mem_regions[i].start
                && address < (mem_regions[i].start + mem_regions[i].size) )
        {
            uint32_t offset = address - mem_regions[i].start;

            mem_regions[i].mem[offset + 3] = (value >> 24) & 0xFF;
            mem_regions[i].mem[offset + 2] = (value >> 16) & 0xFF;
            mem_regions[i].mem[offset + 1] = (value >> 8) & 0xFF;
            mem_regions[i].mem[offset + 0] = (value >> 0) & 0xFF;
            return;
        }
    }
}

/***************************************************************
 *
 * Procedure: run n
 *
 * Purpose: Simulate MIPS for n cycles
 *
 ***************************************************************/
void run( int num_cycles )
{
    int i;

    if( running == FALSE )
    {
        printf( "Can't simulate, Simulator is halted\n\n" );
        return;
    }

    printf( "Simulating for %d cycles...\n\n", num_cycles );
    for( i = 0; i < num_cycles; i++ )
    {
        if( running == FALSE )
        {
            printf( "Simulator halted\n\n" );
            break;
        }
        cycle();
    }
}

/***************************************************************
 *
 * Procedure: rdump
 *
 * Purpose: Dump current register and bus values to the output file.
 *
 ***************************************************************/
void rdump( FILE * dumpsim_file )
{
    int k;

    printf( "\nCurrent register/bus values :\n" );
    printf( "-------------------------------------\n" );
    printf( "Instruction Count : %u\n", intruction_count );
    printf( "IP                : 0x%08x\n", curr_state.ip );
    printf( "Registers:\n" );
    for( k = 0; k < MIPS_REGS; k++ )
        printf( "$%02d: 0x%08x\n", k, curr_state.regs[k] );
//    printf( "HI: 0x%08x\n", curr_state.hi );
//    printf( "LO: 0x%08x\n", curr_state.lo );
    printf( "\n" );

    /* dump the state information into the dumpsim file */
    fprintf( dumpsim_file, "\nCurrent register/bus values :\n" );
    fprintf( dumpsim_file, "-------------------------------------\n" );
    fprintf( dumpsim_file, "Instruction Count : %u\n", intruction_count );
    fprintf( dumpsim_file, "PC                : 0x%08x\n", curr_state.ip );
    fprintf( dumpsim_file, "Registers:\n" );
    for( k = 0; k < MIPS_REGS; k++ )
        fprintf( dumpsim_file, "R%d: 0x%08x\n", k, curr_state.regs[k] );
    fprintf( dumpsim_file, "HI: 0x%08x\n", curr_state.hi );
    fprintf( dumpsim_file, "LO: 0x%08x\n", curr_state.lo );
    fprintf( dumpsim_file, "\n" );
}

/***************************************************************
 *
 * Procedure : main
 *
 ***************************************************************/
int main( int argc, char *argv[] )
{
    FILE * dumpsim_file;

    /* Error Checking */
    if( argc < 2 )
    {
        printf( "Error: usage: %s <program_file_1> <program_file_2> ...\n", argv[0] );
        exit( 0 );
    }

    printf( "MIPS Simulator\n\n" );

    initialize( &argv[1], argc - 1 );

    if( (dumpsim_file = fopen( "dumpsim", "w" )) == NULL )
    {
        printf( "Error: Can't open dumpsim file\n" );
        exit( -1 );
    }

    while( TRUE )
        get_command( dumpsim_file );

}
