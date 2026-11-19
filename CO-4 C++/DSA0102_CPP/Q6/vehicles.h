// vehicles.h - the vehicle hierarchy (these classes are NOT edited when a new type is added)
#pragma once
#include <string>

const double LATE_FACTOR       = 1.5;    // late day costs 1.5 x daily rate
const double FUEL_PRICE        = 100;    // Rs per litre
const double KWH_PRICE         = 12;     // Rs per kWh
const double HELMET_FEE        = 50;     // Rs per two-wheeler rental
const double INSURANCE_PER_DAY = 200;    // Rs per day for cars

class Date {                                         // member class: service due date
    int d, m, y;
public:
    Date(int dd, int mm, int yy) : d(dd), m(mm), y(yy) {}
    bool before(const Date& o) const { return y != o.y ? y < o.y : (m != o.m ? m < o.m : d < o.d); }
    std::string str() const { return std::to_string(d) + "/" + std::to_string(m) + "/" + std::to_string(y); }
};

class Vehicle {                                      // abstract base class
    std::string regNo;
    double dailyRate;
    bool rented = false;
protected:
    double baseCharge(int days) const { return days * dailyRate; }
    double lateCharge(int lateDays) const { return lateDays * dailyRate * LATE_FACTOR; }
public:
    Vehicle(const std::string& r, double rate) : regNo(r), dailyRate(rate) {}
    virtual ~Vehicle() = default;
    const std::string& getReg() const { return regNo; }
    double getRate() const { return dailyRate; }
    bool isRented() const { return rented; }
    void setRented(bool r) { rented = r; }
    virtual bool rentable(const Date&) const { return !rented; }
    virtual double charge(int days, int lateDays, double used) const = 0;   // pure virtual
    virtual std::string type() const = 0;                                    // pure virtual
    virtual std::string details() const { return ""; }
};

class Bicycle : public Vehicle {
public:
    Bicycle(const std::string& r, double rate) : Vehicle(r, rate) {}
    double charge(int days, int lateDays, double) const override { return baseCharge(days) + lateCharge(lateDays); }
    std::string type() const override { return "Bicycle"; }
};

class MotorVehicle : public Vehicle {                // fuel/charge level + service date
protected:
    double level;                                    // litres, or kWh for electric vehicles
    Date serviceDue;
public:
    MotorVehicle(const std::string& r, double rate, double lvl, const Date& due)
        : Vehicle(r, rate), level(lvl), serviceDue(due) {}
    bool rentable(const Date& today) const override { return Vehicle::rentable(today) && !serviceDue.before(today); }
    virtual double energyCost(double used) const = 0;                        // pure virtual
    std::string details() const override { return "level " + std::to_string((int)level) + ", service due " + serviceDue.str(); }
};

class TwoWheeler : public MotorVehicle {
public:
    TwoWheeler(const std::string& r, double rate, double lvl, const Date& due) : MotorVehicle(r, rate, lvl, due) {}
    double energyCost(double used) const override { return used * FUEL_PRICE; }
    double charge(int days, int lateDays, double used) const override
    { return baseCharge(days) + energyCost(used) + HELMET_FEE + lateCharge(lateDays); }
    std::string type() const override { return "Two-wheeler"; }
};

class Car : public MotorVehicle {
    int seats;
public:
    Car(const std::string& r, double rate, int s, double lvl, const Date& due) : MotorVehicle(r, rate, lvl, due), seats(s) {}
    double energyCost(double used) const override { return used * FUEL_PRICE; }
    double charge(int days, int lateDays, double used) const override
    { return baseCharge(days) + energyCost(used) + days * INSURANCE_PER_DAY + lateCharge(lateDays); }
    std::string type() const override { return "Car"; }
    std::string details() const override { return MotorVehicle::details() + ", seats " + std::to_string(seats); }
};

class ElectricCar : public Car {                     // charged per kWh instead of per litre
    double batteryKWh;
public:
    ElectricCar(const std::string& r, double rate, int s, double kwh, double battery, const Date& due)
        : Car(r, rate, s, kwh, due), batteryKWh(battery) {}
    double energyCost(double used) const override { return used * KWH_PRICE; }
    std::string type() const override { return "Electric car"; }
    std::string details() const override { return Car::details() + ", battery " + std::to_string((int)batteryKWh) + " kWh"; }
};
