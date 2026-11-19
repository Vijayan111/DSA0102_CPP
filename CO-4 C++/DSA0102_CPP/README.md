# DSA0102_CPP  (CO4 Assignment 4 - Designing Reusable Class Hierarchies)

- **Name:** Vijayan P
- **GitHub:** https://github.com/Vijayan111/DSA0102_CPP.git
- **Register number:** 192525312
- **Course:** Object Oriented Programming with C++ (DSA01)
- **Compiler:** g++ 13.3.0 (Ubuntu 24.04)
- **Compile command (every program):** `g++ -std=c++17 -Wall -Wextra <file>.cpp -o <name>`
  (sanitizer runs add `-g -fsanitize=address`; benchmarks are run with `-O0` and `-O2`)

## Folders
| Folder | Task | Programs |
|---|---|---|
| Q1 | Class design review | `q1_original.cpp` (given classes, evidence), `q1_hierarchy.cpp` (repair), `q1_bench.cpp` (single class + switch) |
| Q2 | Requirement to hierarchy | `q2_classes.cpp`, `q2_predict.cpp`, `q2_predict_novirtual.cpp`, `q2_ambiguous.cpp` (fails on purpose), `q2_access_test.sh`, `q2_compose.cpp` |
| Q3 | Constructors / member classes | `q3_trace.cpp`, `q3_experiment.cpp` (`-DNOVIRTUAL`), `q3_predict.cpp`, `q3_complete.cpp`, `q3_reorder.cpp`, `q3_no_virtual_base_init.cpp` (fails on purpose), `q3_alt_ptr.cpp` (`-DNOCOPY`) |
| Q4 | Pointers to derived classes | `q4_buggy.cpp`, `q4_fixed.cpp`, `q4_slicing_error.cpp` / `q4_override_error.cpp` (fail on purpose), `q4_predict.cpp`, `q4_alt_unique.cpp` (`-DVIRTUAL_DTOR`) |
| Q5 | Pointers to objects, `this` | `q5_ways.cpp`, `q5_array.cpp`, `q5_complete.cpp`, `q5_byvalue.cpp`, `q5_alt_vector.cpp` |
| Q6 | Vehicle rental fleet | `vehicles.h`, `fleet.h`, `electric_bus.h`, `q6_demo.cpp`, `q6_demo_ext.cpp`, `q6_alt_switch.cpp` |

Each folder has an `outputs/` directory with the exact terminal transcript of every run.
`predictions.md` holds the predictions written before anything was compiled.

## How to run
```
cd Q1 && g++ -std=c++17 -Wall -Wextra q1_hierarchy.cpp -o q1_hierarchy && ./q1_hierarchy
cd Q6 && g++ -std=c++17 -Wall -Wextra q6_demo_ext.cpp -o q6_demo_ext && ./q6_demo_ext
```
(Q4 sanitizer: `g++ -std=c++17 -g -fsanitize=address q4_buggy.cpp -o q4_buggy_asan && ./q4_buggy_asan`;
leak report: `ASAN_OPTIONS=new_delete_type_mismatch=0 ./q4_buggy_asan`.)

## Result of each task
1. Three duplicated payroll classes repaired into `Staff` -> `SalariedStaff` -> `Professor/LabAssistant/Librarian` and `GuestFaculty`; total payroll Rs 170000 in one loop.
2. Diamond `TeachingAssistant` solved with virtual bases: output `Person Student Staff TA`; without `virtual`: `Person Student Person Staff TA` and `ta.name` is ambiguous.
3. Construction order base -> member -> body, destruction reversed; `virtual` raises `sizeof(TeachingAssistant)` from 32 to 40 for the small test classes; `-Wreorder` warning recorded.
4. Three defects found (hidden `rate()`, non-virtual destructor leaking 800 bytes, slicing) and proved with AddressSanitizer; repaired program is clean.
5. Four ways to reach a `Cart`, chaining with `*this`; `Cart` returned by value gives 240.00 instead of 324.00.
6. Rental fleet with abstract `Vehicle`; `ElectricBus` added in a new header without editing existing classes; total Rs 27460.
