#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


/* Setting a bit

   setbit(x);
   clearbit(x);

   These are the same two operations, one clears the bit and one sets the bit.
   These assume that that we're using uint32 types.

   Also, we've got the maximum integer size specified in advance, as N.

   Pseudo-code:

   buckets = ceil(N/32);
 */

typedef struct {
  uint32_t words[2];
} Bitmap;


Bitmap
setbit(Bitmap bitmap, uint32_t val)
{
  uint word = val / 32;
  uint bit = val % 32;

  bitmap.words[word] = bitmap.words[word] | (0x1 << bit);

  return bitmap;
}

void
print_bits(uint32_t x)
{
  printf("%4u: ", x);
  for (unsigned int i = 31; i < 32; i--){
    if ((x >> i) & 0x1) printf("1");
    else                printf("0");
  }
  printf("\n");
}

void
test()
{
  Bitmap map;
  map.words[0] = 0;
  map.words[1] = 0;

  print_bits(map.words[0]);
  print_bits(map.words[1]);

  map = setbit(map, 0);
  map = setbit(map, 1);
  map = setbit(map, 3);
  map = setbit(map, 31);
  map = setbit(map, 32);
  map = setbit(map, 33);
  map = setbit(map, 35);
  map = setbit(map, 63);
  
  print_bits(map.words[0]);
  print_bits(map.words[1]);

}


int main(int argc, char **argv)
{
  for (uint32_t i = 0; i < 20; i++){
    print_bits(i);
  }

  uint32_t max = 0;
  max--;
  print_bits(max);

  printf("Testing....\n");
  test();
}
