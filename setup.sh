#!/bin/sh

alias mc="make clean && make"

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
  echo "[Test $1]"
  ./bcc tests/test$1.bc >| bcc.out
  echo "[Parser]"
  diff bcc.out tests/test$1_result.txt
  echo "[Code gen]"
  diff tests/test$1.iloc tests/test$1_ref.iloc
}

ta() {
  for i in 1 2 3 4 5 6 7 8; do
    if ! t $i; then
      break
    fi
  done
}
