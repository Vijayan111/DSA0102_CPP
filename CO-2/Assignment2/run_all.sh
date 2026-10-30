#!/bin/bash
# compiles and runs every program of every task folder (the three files that must fail are only compiled)
FLAGS="-std=c++17 -Wall -Wextra"
for d in Q*/; do
  for f in $d*.cpp; do
    b=$(basename $f .cpp)
    case $b in
      q2_const_error|q3_ambiguous|q3_long_ambiguous) echo "== $b (expected to fail)"; g++ $FLAGS $f -o /tmp/$b 2>&1 | head -5 ;;
      q2_vector_asan) echo "== $b"; g++ $FLAGS -g -fsanitize=address $f -o /tmp/$b && /tmp/$b 2>&1 | head -5 ;;
      *) echo "== $b"; g++ $FLAGS $f -o /tmp/$b && /tmp/$b ;;
    esac
  done
done
