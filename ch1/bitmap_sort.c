#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>


typedef unsigned int uint_t;
typedef uint32_t word_t;
#define WORD_SIZE 32

typedef struct {
  word_t *words;
  size_t num_words;
} Bitmap;


Bitmap setbit(Bitmap bitmap, uint_t val);
Bitmap clearbit(Bitmap bitmap, uint_t val);
int bit_is_set(Bitmap bitmap, uint_t val);
void print_bits(word_t prefix, word_t x);
void print_raw_bits(word_t x);
void test(unsigned long max);
void release_map(Bitmap map);
Bitmap make_map(unsigned long max_val);
void print_bitmap(Bitmap map);



Bitmap
setbit(Bitmap bitmap, uint_t val)
{
  uint_t word = val / WORD_SIZE;
  uint_t bit = val % WORD_SIZE;

  bitmap.words[word] = bitmap.words[word] | (0x1 << bit);

  return bitmap;
}

Bitmap
clearbit(Bitmap bitmap, uint_t val)
{
  uint_t word = val / WORD_SIZE;
  uint_t bit = val % WORD_SIZE;

  bitmap.words[word] = bitmap.words[word] ^ (0x1 << bit);

  return bitmap;
}

int
bit_is_set(Bitmap bitmap, uint_t val)
{
  uint_t word = val / WORD_SIZE;
  uint_t bit = val % WORD_SIZE;

  return bitmap.words[word] & ((~bitmap.words[word]) | (0x1 << bit));
}

void
print_bits(word_t prefix, word_t x)
{
  printf("%4u: ", prefix);
  print_raw_bits(x);
  printf("\n");
}

void
print_raw_bits(word_t x)
{
  for (uint_t i = 31; i < 32; i--){
    if ((x >> i) & 0x1) printf("1");
    else                printf("0");
  }
}

Bitmap
make_map(unsigned long max_val)
{
  Bitmap map;

  map.num_words = (size_t)ceil(max_val / (WORD_SIZE * 1.0));
  map.words = calloc(map.num_words, sizeof(word_t));

  return map;
}

void
release_map(Bitmap map)
{
  if (map.words)
    free(map.words);
}

void
test(unsigned long max_val)
{
  Bitmap map = make_map(max_val);

  print_bitmap(map);

  map = setbit(map, 0);
  map = setbit(map, 1);
  map = setbit(map, 3);
  map = setbit(map, 31);
  map = setbit(map, 32);
  map = setbit(map, 33);
  map = setbit(map, 35);
  map = setbit(map, 63);
  
  print_bitmap(map);

  map = clearbit(map, 33);

  print_bitmap(map);

  for (size_t i = 0; i < max_val+1; i++){ // Max val is inclusive
    //    printf("%2d: %s\n", i, (bit_is_set(map, i)?"✔":"✘"));
    if (bit_is_set(map, i))
      printf("%d\n", i);
  }

  release_map(map);
}

void
print_bitmap(Bitmap map)
{
  for (size_t i = 0; i < map.num_words; i++){
    print_bits(i, map.words[i]);
  }

  printf("Printing raw bitmap\n");
  for (size_t i = map.num_words-1; i < map.num_words; i--){
    print_raw_bits(map.words[i]);
  }
  printf("\n");

}


int main(int argc, char **argv)
{
  if (argc < 2)
    exit(-1);

  unsigned long max_value = strtoul(argv[1], NULL, 0);
  
  printf("Testing....\n");
  test(max_value);
}
