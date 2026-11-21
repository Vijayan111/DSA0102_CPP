#include <iostream>
#include <iomanip>
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
using namespace std;

class Bill {
protected:
    string patient;
public:
    explicit Bill(string p) : patient(std::move(p)) {}
    virtual ~Bill() = default;
    virtual double total() const = 0;
    virtual string type() const = 0;
    void print() const { cout << type() << " " << patient << ": " << total() << '\n'; }
};
class OutPatient : public Bill {
    double consultation, tests;
public:
    OutPatient(string p,double c,double t):Bill(std::move(p)),consultation(c),tests(t) {
        if(c<0 || t<0) throw invalid_argument("negative charge");
    }
    double total() const override { return consultation+tests; }
    string type() const override { return "OP"; }
};
class InPatient : public Bill {
    int days; double perDay, surgery;
public:
    InPatient(string p,int d,double r,double s):Bill(std::move(p)),days(d),perDay(r),surgery(s) {
        if(d<0 || r<0 || s<0) throw invalid_argument("negative charge");
    }
    double total() const override { return days*perDay+surgery; }
    string type() const override { return "IP"; }
};
class DayCareBill : public Bill {
    double packagePrice;
public:
    DayCareBill(string p,double v):Bill(std::move(p)),packagePrice(v) { if(v<0) throw invalid_argument("negative charge"); }
    double total() const override { return packagePrice; }
    string type() const override { return "DAY"; }
};
class EmergencyBill : public Bill {
    double base, hourly; int hours;
public:
    EmergencyBill(string p,double b,double h,int n):Bill(std::move(p)),base(b),hourly(h),hours(n) {
        if(b<0 || h<0 || n<0) throw invalid_argument("negative charge");
    }
    double total() const override { return base+hourly*hours; }
    string type() const override { return "ER"; }
};
class Payer {
public: virtual ~Payer()=default; virtual double amountCovered(const Bill&) const=0; virtual string name() const=0;
};
class SelfPay: public Payer {
public: double amountCovered(const Bill& b) const override { return 0.0; } string name() const override{return "SelfPay";}
};
class Insurance: public Payer {
    double limit, copay;
public: Insurance(double l,double c):limit(l),copay(c) { if(l<0||c<0||c>100) throw invalid_argument("invalid policy"); }
    double amountCovered(const Bill& b) const override { return min(limit,b.total()*(1.0-copay/100.0)); }
    string name() const override{return "Insurance";}
};
class GovernmentScheme: public Payer {
    double packageRate;
public: explicit GovernmentScheme(double r):packageRate(r) { if(r<0) throw invalid_argument("invalid package rate"); }
    double amountCovered(const Bill& b) const override { return min(packageRate,b.total()); }
    string name() const override{return "GovernmentScheme";}
};
class CorporatePayer: public Payer {
    double percentage;
public: explicit CorporatePayer(double p):percentage(p) { if(p<0||p>100) throw invalid_argument("invalid percentage"); }
    double amountCovered(const Bill& b) const override { return b.total()*percentage/100.0; }
    string name() const override{return "CorporatePayer";}
};
int main(){
    cout<<fixed<<setprecision(0);
    vector<unique_ptr<Bill>> bills;
    bills.push_back(make_unique<OutPatient>("Ravi",500,1200));
    bills.push_back(make_unique<InPatient>("Meena",3,2500,40000));
    bills.push_back(make_unique<DayCareBill>("Arun",18000));
    bills.push_back(make_unique<EmergencyBill>("Divya",2000,750,4));
    double grand=0;
    for(const auto& b:bills){b->print();grand+=b->total();}
    cout<<"Total "<<grand<<'\n';
    Insurance ins(30000,20); GovernmentScheme gov(15000); CorporatePayer corp(70);
    cout<<"Insurance covers "<<ins.amountCovered(*bills[1])<<'\n';
    cout<<"Government covers "<<gov.amountCovered(*bills[2])<<'\n';
    cout<<"Corporate covers "<<corp.amountCovered(*bills[0])<<'\n';
}
