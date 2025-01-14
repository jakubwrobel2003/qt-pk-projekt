#include "Sprzezenie.h"

Sprzezenie::Sprzezenie(PID* regulator, ARX* model)
    : regulatorPID(regulator), modelARX(model) {}

double Sprzezenie::sumator(double wartoscZadana, double wartoscMierzona) {
    // Wylicza uchyb jako rroznice miedzy wartoscia zadana a mierzona
    return wartoscZadana - wartoscMierzona;
}

double Sprzezenie::obliczSprzezenie(double wartoscZadana, double wartoscMierzona, std::vector<BuforDanych*> dane) {
    // Wylicza uchyb za pomoca sumatora
    double uchyb = sumator(wartoscZadana, wartoscMierzona);

    // Oblicza sygnaa sterujacy za pomoca PID
    double sygnalSterujacy = regulatorPID->oblicz(uchyb, wartoscMierzona);

    // Zaktualizuj model ARX
    if (!dane.empty()) {
        dane.back()->setU(sygnalSterujacy);
    }

    // Oblicza wyjscie modelu ARX
    double wyjscieSystemu = modelARX->calcAll(dane);

    return wyjscieSystemu;
}
