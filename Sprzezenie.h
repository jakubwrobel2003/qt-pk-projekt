#pragma once
#include "PID.h"
#include "ARX.h"
#include <vector>

class Sprzezenie {
private:
    PID* regulatorPID;
    ARX* modelARX;

public:
    Sprzezenie(PID* regulator, ARX* model);

    // Funkcja obliczaj¹ca sprzê¿enie zwrotne
    double obliczSprzezenie(double wartoscZadana, double wartoscMierzona, std::vector<BuforDanych*> dane);

    // Funkcja sumatora
    double sumator(double wartoscZadana, double wartoscMierzona);
};

