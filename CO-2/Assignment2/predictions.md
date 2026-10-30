# Predictions written BEFORE compiling or running anything

## Q1
Fee = 45000, concession 10%.
 - call by value   -> stored fee 45000 (only the local copy changes)
 - call by reference -> stored fee 40500
 - call by pointer -> stored fee 40500
q1_predict.cpp output:
1 12 13
1 100
16 13 6 <newline>          (note trailing space after 6)
 a is passed by value (stays 1), b by reference (2->12), c through pointer (3->13).
 bigger(a,c): a=1, c=13 -> returns c, so c = 100.
 show(1)=1+5+10=16 (y,z default), show(1,2)=1+2+10=13 (z default), show(1,2,3)=6 (none default)
q1_complete expected: after call by value : 45000 / after call by reference: 40500
sizeof(long long)=8, sizeof(Student {char name[64]; int marks[100]; long long fee;}) = 472

## Q2
marks = 72 85 91 64 88
 highest()+=2 -> 72 85 93 64 88 ; highest()=95 -> 72 85 95 64 88 ; copy version leaves array unchanged.
 returning ref to local: g++ warns "reference to local variable returned [-Wreturn-local-addr]"; running it is undefined behaviour.
 vector: after push_back beyond capacity the buffer address changes (true); index stays valid, pointer/reference go stale.

## Q3
 charge(2.0) -> ambiguous (overload 1 vs 3), charge(2.0,true) -> ambiguous (overload 2 vs 3): compile error.
 Redesign: charge(int grams,bool=false,bool=false), charge(double kg,bool=false,bool=false), charge(const Parcel&)
 rate Rs 50/kg, express +40, insured +25
 charge(2)                  -> int grams overload  -> 0.10
 charge(2.0)                -> double kg overload  -> 100.00
 charge(2.0f)               -> double kg (float->double promotion beats float->int conversion) -> 100.00
 charge(1500,true)          -> int grams overload  -> 115.00
 charge(1.5,true,true)      -> double kg overload  -> 140.00
 charge(Parcel{3.0,false,true}) -> Parcel overload -> 175.00

## Q4
 12 transactions, last 10 kept: statement shows transaction numbers 12 down to 3, final balance 11200.

## Q5
 Token: 101 103 104 4  (constructor runs 4 times, next starts at 100)
 BusTicket: Asha Seat 1, Bala Seat 2, Chitra Seat 3, Dev Waiting, Issued: 3
 function called twice (2 tickets each, capacity 3): after call 1 count=2, after call 2 count=3 (one ticket on waiting list)

## Q6
 205 false
 11:50 vs 12:10 -> 20 minutes, earlier true ; same time twice -> 0, false, false
 -O0: inline and non-inline about the same; -O2: inline faster

## Q7 (design D)
 Shifting array cost per add grows ~linearly with capacity; circular buffer stays constant.
 Expect circular >= 500x faster at capacity 10000, and within 0.3x..3x of shifting at capacity 10.
Fri Oct 30 09:07:09 UTC 2026
