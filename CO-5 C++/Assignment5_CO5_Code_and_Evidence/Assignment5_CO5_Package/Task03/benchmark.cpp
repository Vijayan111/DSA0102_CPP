#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <cstdint>
#include <memory>
using namespace std;
struct BillBase { virtual ~BillBase()=default; virtual double total() const=0; };
struct OP:BillBase { double a,b; OP(double x,double y):a(x),b(y){} double total()const override{return a+b;} };
struct IP:BillBase { double a,b; IP(double x,double y):a(x),b(y){} double total()const override{return a+b;} };
struct Flat { int type; double a,b; double total()const { switch(type){case 0:return a+b;default:return a+b;} } };
volatile double sinkValue=0;
template<class F> double measure(F f){auto s=chrono::steady_clock::now(); double v=f(); auto e=chrono::steady_clock::now(); sinkValue=v; return chrono::duration<double,milli>(e-s).count();}
int main(){
    cout<<fixed<<setprecision(3);
    const int n=1000000;
    vector<unique_ptr<BillBase>> poly; poly.reserve(n);
    vector<Flat> flat; flat.reserve(n);
    for(int i=0;i<n;i++){double x=(i%500)+100,y=(i%200)+50; if(i%2){poly.push_back(make_unique<OP>(x,y));flat.push_back({0,x,y});}else{poly.push_back(make_unique<IP>(x,y));flat.push_back({1,x,y});}}
    double p=measure([&]{double s=0;for(auto &b:poly)s+=b->total();return s;});
    double q=measure([&]{double s=0;for(auto &b:flat)s+=b.total();return s;});
    cout<<"Bills: "<<n<<"\nVirtual total: "<<sinkValue<<"\nVirtual time ms: "<<p<<"\nSwitch total: "<<sinkValue<<"\nSwitch time ms: "<<q<<"\n";
    for(int invalidPct:{0,1,50}){
        volatile int accepted=0;
        auto t=chrono::steady_clock::now();
        for(int i=0;i<n;i++){bool bad=(i%100)<invalidPct;if(!bad)++accepted;}
        auto e=chrono::steady_clock::now();
        cout<<"Return-code invalid "<<invalidPct<<"% time ms: "<<chrono::duration<double,milli>(e-t).count()<<" accepted "<<accepted<<'\n';
        accepted=0;t=chrono::steady_clock::now();
        for(int i=0;i<n;i++){try{if((i%100)<invalidPct)throw 1;++accepted;}catch(int){}}
        e=chrono::steady_clock::now();
        cout<<"Exception invalid "<<invalidPct<<"% time ms: "<<chrono::duration<double,milli>(e-t).count()<<" accepted "<<accepted<<'\n';
    }
}
