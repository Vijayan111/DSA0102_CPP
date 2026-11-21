# Assignment 5 – CO5: Reliable Software with Runtime Polymorphism and Exceptions

Student: Vijayan P  
Register Number: 192525312  
Department: AI&ML  
Course: Object Oriented Programming with C++ (DSA01)  
Compiler: g++ (record your installed version with `g++ --version`)  
Build flags: `-std=c++17 -Wall -Wextra` (benchmark additionally uses `-O2`)

## Folder structure
- `Task01/` polymorphic hospital bills and payer hierarchy
- `Task02/` exception validation, logging, rethrowing and stack unwinding
- `Task03/` virtual dispatch/switch and exception-cost experiment
- `Task04/` extension with a new bill and payer
- `Evidence/` sample terminal outputs, UML diagram and output text files

## Compile and run
From this folder, for example:
```bash
g++ -std=c++17 -Wall -Wextra Task01/billing_polymorphism.cpp -o Task01/billing
./Task01/billing
g++ -std=c++17 -Wall -Wextra Task02/exceptions.cpp -o Task02/exceptions
./Task02/exceptions
g++ -std=c++17 -O2 -Wall -Wextra Task03/benchmark.cpp -o Task03/benchmark
./Task03/benchmark
g++ -std=c++17 -Wall -Wextra Task04/extension.cpp -o Task04/extension
./Task04/extension
```

## Task result notes
- Task 1: A common abstract `Bill` interface processes outpatient, inpatient, day-care and emergency bills through base-class pointers. Payers use a separate abstract interface.
- Task 2: Invalid values throw standard or domain-specific exceptions. `settle` logs and rethrows `ClaimError` with `throw;`; RAII guard demonstrates cleanup during stack unwinding.
- Task 3: Runs a million-record comparison and records local timings. Timings depend on compiler, CPU, operating system and system load; rerun before submitting measured claims.
- Task 4: Adds `MaternityBill` and `EmployeeBenefit` without editing the original concrete bill classes.

## Important submission checks
1. Replace sample output images with genuine screenshots captured from your own VS Code terminal after running each source file.
2. Record your actual compiler version and machine details.
3. Run AddressSanitizer using `g++ -std=c++17 -g -fsanitize=address -fno-omit-frame-pointer ...` and save the report.
4. Create the required GitHub repository `DSA01-192525312-Assignment5`, commit each task separately and add its link to the report.
5. The supplied screenshots are clearly labelled sample outputs, not screenshots from your computer.
