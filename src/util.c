#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

u32 num_digits(i32 num) {
  const bool negative = num < 0;
  if (negative) {
    num *= -1;
  }
  u32 digits;
  for (digits = 0; num > 0; ++digits) {
    num /= 10;
  }
  return digits + (negative ? 1 : 0);
}

char *i32_to_str(i32 num) {
  const u32 digits = num_digits(num);
  char *str = malloc(digits + 1);
  sprintf(str, "%i", num);
  return str;
}
