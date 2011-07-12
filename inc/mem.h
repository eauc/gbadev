#ifndef MEM_H_
#define MEM_H_

/*
  MEMORY
*/

#define MEM_BIOS          0x00000000
#define MEM_BIOS_SIZE     16384

#define MEM_OB_WRAM       0x02000000
#define MEM_OB_WRAM_SIZE  262144

#define MEM_IC_WRAM       0x03000000
#define MEM_IC_WRAM_SIZE  32768

#define MEM_IO            0x04000000
#define MEM_IO_SIZE       1023

#define MEM_PALETTE       0x05000000
#define MEM_PALETTE_SIZE  1024

#define MEM_VIDEO         0x06000000
#define MEM_VIDEO_SIZE    98304

#define MEM_OAM           0x07000000
#define MEM_OAM_SIZE      1024

#define MEM_ROM0          0x08000000
#define MEM_ROM0_SIZE     0

#define MEM_ROM1          0x0A000000
#define MEM_ROM1_SIZE     0

#define MEM_ROM2          0x0C000000
#define MEM_ROM2_SIZE     0

#define MEM_SRAM          0x0E000000
#define MEM_SRAM_SIZE     65536

#endif
