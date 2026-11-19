# Predictions written BEFORE compiling or running anything (Assignment 4)

## Q2 - Person / Student / Staff / TeachingAssistant (virtual bases)
Program as given: output line  ->  "Person Student Staff TA " then newline
  (virtual base Person is built first, once, by the most-derived class; then Student, Staff, TA)
Without 'virtual' in both bases -> "Person Student Person Staff TA "
  compiler messages: none (no warning, no error) because the program never names a Person member.
  Accessing ta.name in that layout would be an error: request for member 'name' is ambiguous.

## Q3 - Engine / Vehicle / Car
Output: "Vehicle Engine Car | ~Car ~Engine ~Vehicle " then newline
Rule: base classes first (declaration order), then member objects (declaration order), then the body.
      Destruction is the exact reverse.

My own trace programs (Q3.3):
  Student object : ctor order  Address Person Course Student        dtor order ~Student ~Course ~Person ~Address
  Staff object   : ctor order  Address Person Staff                  dtor order ~Staff ~Person ~Address
  TA object      : ctor order  Address Person Course Student Staff TA   dtor order ~TA ~Staff ~Student ~Course ~Person ~Address
Q3.4 sizeof experiment (Person{int}; Student{double}; Staff{double}; x86-64 g++):
  with virtual bases    -> sizeof(TeachingAssistant) = 40
  without virtual bases -> sizeof(TeachingAssistant) = 32   (two Person copies but no vptrs)

## Q4 - Account / SeniorAccount
Program as given: "3.5 4 3.5" then newline
  p->rate()   : rate() is not virtual -> bound at compile time to Account::rate -> 3.5
  p->vrate()  : virtual -> run-time dispatch -> SeniorAccount::vrate -> 4
  copy.vrate(): copy is an Account (sliced) -> 3.5

## Q5 - Cart
Expected from the question: 324.00
If add() returned Cart (by value): each chained call works on a temporary copy, so the
discount is lost and 'Dal' is lost -> c holds Rice and Oil only, no discount -> "240.00"
Array-of-pointers test: Asha 180.00, Bala 207.00, Chitra 508.25, Dev 30.00 -> highest = Chitra 508.25

## Q1 payroll test
Professor 50000+0.42*50000+10000 = 81000 ; LabAssistant 20000+8400 = 28400 ;
GuestFaculty 12*1500 = 18000 ; Librarian 30000+12600 = 42600 ; total 170000

## Q6 rental demo (hand calculation)
Bicycle 2 days = 200 ; TwoWheeler 3d,1 late,4L = 1200+400+50+600 = 2250 ;
Car 4d,2 late,25L = 4800+2500+800+3600 = 11700 ; ElectricCar 2d,1 late,20kWh = 3000+240+400+2250 = 5890 ;
ElectricBus 1d,60kWh = 5000+720+200+1500 = 7420 ; total 27460 ; overdue TwoWheeler is refused.
written 2026-11-02 14:03:32 UTC
