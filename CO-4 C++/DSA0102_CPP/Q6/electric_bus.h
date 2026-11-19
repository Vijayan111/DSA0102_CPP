// electric_bus.h - a NEW vehicle type in its own file: vehicles.h and fleet.h are not touched
#pragma once
#include "vehicles.h"

const double DRIVER_FEE = 1500;                      // Rs per day, a bus comes with a driver

class ElectricBus : public ElectricCar {
public:
    ElectricBus(const std::string& r, double rate, int seats, double kwh, double battery, const Date& due)
        : ElectricCar(r, rate, seats, kwh, battery, due) {}
    double charge(int days, int lateDays, double used) const override
    { return ElectricCar::charge(days, lateDays, used) + days * DRIVER_FEE; }
    std::string type() const override { return "Electric bus"; }
};
