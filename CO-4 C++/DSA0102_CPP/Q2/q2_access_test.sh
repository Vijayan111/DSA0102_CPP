#!/bin/bash
# Q2.4 - verify the access table by compiling one tiny test per case (yes = compiles)
printf "%-10s %-10s %-13s %-13s %-13s\n" "inherit" "member" "in Student" "outside" "in derived"
for inh in public protected private; do
 for mem in pub prot priv; do
  res=""
  for ctx in own outside derived; do
   cat > /tmp/t.cpp <<EOT
class Person { public: int pub=1; protected: int prot=2; private: int priv=3; };
class Student : $inh Person { public: int own() { return $mem; } };
class Sub : public Student { public: int d() { return $mem; } };
int main() { Student s; Sub u; (void)u;
EOT
   case $ctx in
     own) echo "(void)s; } int f(Student& s){ return s.own(); } " >> /tmp/t.cpp; sed -i 's/^class Student.*/class Student : '$inh' Person { public: int own() { return '$mem'; } };/' /tmp/t.cpp;;
     outside) echo "(void)s.$mem; }" >> /tmp/t.cpp; sed -i 's/{ return $mem; }/{ return 0; }/; s/return '$mem'; }/return 0; }/' /tmp/t.cpp;;
     derived) echo "(void)s; }" >> /tmp/t.cpp; sed -i 's/public: int own() { return '$mem'; }/public:/' /tmp/t.cpp;;
   esac
   if [ $ctx != derived ]; then sed -i 's/public: int d() { return '$mem'; }/public: int d() { return 0; }/' /tmp/t.cpp; fi
   if g++ -std=c++17 -fsyntax-only /tmp/t.cpp 2>/dev/null; then r=yes; else r=NO; fi
   res="$res$(printf '%-13s' $r)"
  done
  printf "%-10s %-10s %s\n" $inh $mem "$res"
 done
done
