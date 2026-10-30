# DSA01-<RegisterNumber>-Assignment2

**Name:** Vijayan P
**Register number:** <fill in>
**Compiler:** g++ 13.3.0 (change this to the version on YOUR machine: `g++ --version`)

## Compile command
    g++ -std=c++17 -Wall -Wextra file.cpp -o file
Timing programs (q1_copycost, q6_bench, q7_bench) were compiled twice, with `-O0` and with `-O2`.
AddressSanitizer demo: `g++ -std=c++17 -g -fsanitize=address q2_vector_asan.cpp -o q2_vector_asan`

## How to run
Go into a task folder, compile one file with the command above and run `./file` (`file.exe` on Windows).
`predictions.md` holds the predictions written before running anything.

## Programs that are supposed to FAIL to compile
q2_const_error.cpp, q3_ambiguous.cpp, q3_long_ambiguous.cpp (they show the compiler messages used as evidence).

## Result of each task
- Q1: only call by reference / pointer change the caller's fee (45000 -> 40500). Predicted output of q1_predict matched. Returning the new fee chosen for chained concessions.
- Q2: int& return lets `highest(...) += 2` work; returning a reference to a local warns and crashes; vector growth invalidates references (ASan heap-use-after-free); index is safest.
- Q3: original overloads are ambiguous; redesign with int grams / double kg / Parcel works for all six calls.
- Q4: last 10 transactions kept; shifting is O(k), circular index is O(1); circular chosen for 50.
- Q5: Token prints `101 103 104 4`; BusTicket output matches expected; static count survives destroyed objects.
- Q6: `205 false`; tests across noon and same time pass; inline helps only with -O2; friend functions kept.
- Q7: circular buffer redesign of the Q4 history, big speed-up at large capacity, identical contents.
