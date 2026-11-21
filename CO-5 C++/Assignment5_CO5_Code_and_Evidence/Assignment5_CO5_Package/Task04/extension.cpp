#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;
class Bill { protected:string patient; public:explicit Bill(string p):patient(move(p)){} virtual ~Bill()=default; virtual double total()const=0; virtual string type()const=0; };
class OPBill:public Bill {double consultation,tests;public:OPBill(string p,double c,double t):Bill(move(p)),consultation(c),tests(t){if(c<0||t<0)throw invalid_argument("negative charge");}double total()const override{return consultation+tests;}string type()const override{return "OP";}};
class MaternityBill:public Bill {double delivery,stay;int days;public:MaternityBill(string p,double d,double s,int n):Bill(move(p)),delivery(d),stay(s),days(n){if(d<0||s<0||n<0)throw invalid_argument("negative charge");}double total()const override{return delivery+stay*days;}string type()const override{return "MATERNITY";}};
class Payer {public:virtual ~Payer()=default;virtual double cover(double amount)const=0;};
class EmployeeBenefit:public Payer {double rate;public:explicit EmployeeBenefit(double r):rate(r){if(r<0||r>100)throw invalid_argument("rate");}double cover(double a)const override{return a*rate/100.0;}};
int main(){vector<unique_ptr<Bill>> bills;bills.push_back(make_unique<OPBill>("Ravi",500,1200));bills.push_back(make_unique<MaternityBill>("Anu",35000,4000,2));double total=0;for(auto&b:bills){cout<<b->type()<<" "<<b->total()<<'\n';total+=b->total();}EmployeeBenefit payer(80);cout<<"Employee benefit: "<<payer.cover(bills[1]->total())<<'\n';cout<<"Total: "<<total<<'\n';}
