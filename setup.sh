#!/bin/sh

m() {
  # If no argument was passed, default to 1
  [ $# -eq 0 ] && set $1 1
  make && echo && ./bcc tests/test$1.bc
}

rem() {
  # If no argument was passed, default to 1
  [ $# -eq 0 ] && set $1 1
  make clean && make && echo && ./bcc tests/test$1.bc
}

t() {
  # If no argument was passed, default to 1
  [ $# -eq 0 ] && set $1 1
  ./bcc tests/test$1.bc > bcc.out
  diff bcc.out tests/test$1_result.txt
}
