# Integer Sorting

From Programming Pearls, ch 1.


## Building

For normal output
`clang -g -Weverything -O0 -o bitmap_sort ./bitmap_sort.c  -lm -lbsd`

For "Pretty" but useless output:

`clang -DPRETTY_OUTPUT -g -Weverything -O0 -o bitmap_sort ./bitmap_sort.c  -lm -lbsd`
