#!/bin/sh

alias mr="make release"
alias md="make debug"
alias rmr="make clean && make release"
alias rmd="make clean && make debug"

deb() {
  # If no argument was passed, default to 1
  [ $# -eq 0 ] && set $1 1
  debug/bcc tests/test$1.bc
}

rel() {
  # If no argument was passed, default to 1
  [ $# -eq 0 ] && set $1 1
  release/bcc tests/test$1.bc
}

t() {
  # If no argument was passed, default to 1
  [ $# -eq 0 ] && set $1 1
  echo "[Test $1]"
  release/bcc tests/test$1.bc >| release/bcc.out
  echo "[Parser]"
  diff release/bcc.out tests/test$1_result.txt
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
