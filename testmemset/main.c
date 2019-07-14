#include <stdlib.h>
#include <stdio.h>
#include "../_shared/types.h"
#include <string.h>

typedef struct Memory {
  void* pointer;
  u64 TotalSize;
	u64 UsedSize;
} Memory;

int main(void)
{   
  Memory memory;
  memory.size = 50;
  memory.pointer = malloc(memory.size);

  memset(memory.pointer,0,memory.size);
  printf("%u\n", *((u8 *)(memory.pointer)));
  return 0;
}
