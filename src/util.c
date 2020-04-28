#include "util.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

u32 num_digits(i32 num) {
  if (num < 0) {
    num *= -1;
  }
  u32 digits;
  for (digits = 0; num > 0; ++digits) {
    num /= 10;
  }
  return digits + (num <= 0 ? 1 : 0);
}

char *i32_to_str(i32 num) {
  const u32 digits = num_digits(num);
  char *str = malloc(digits + 1);
  sprintf(str, "%i", num);
  return str;
}
