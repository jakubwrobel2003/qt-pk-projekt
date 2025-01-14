#include "PID.h"
#include "App.h"
#include "BuforDanych.h"
PID::PID(double kp, double ki, double kd)
    : wzmocnienieProporcjonalne(kp), wzmocnienieCalkujace(ki), wzmocnienieRowniczkujace(kd),
    calka(0), poprzedniUchyb(0), resetujCalke(false) {}

void PID::resetPamieci() {
    calka = 0.001;
    poprzedniUchyb = 0;
}

void PID::ustawWzmocnienieProporcjonalne(double wartosc) {
    wzmocnienieProporcjonalne = wartosc;
}

void PID::ustawWzmocnienieCalkujace(double wartosc) {
    wzmocnienieCalkujace = wartosc;
}

void PID::ustawWzmocnienieRowniczkujace(double wartosc) {
    wzmocnienieRowniczkujace = wartosc;
}

double PID::oblicz(double wartoscZadana, double wartoscMierzona) {
    double uchyb = wartoscZadana - wartoscMierzona;

    // Skladowa proporcjonalna
    double proporcjonalna = wzmocnienieProporcjonalne * uchyb;

    // Skladowa calkujaca
    if (!resetujCalke) {
        calka += uchyb;
        calka = calka / 2;
    }
    else {
        resetujCalke = false;
    }
    double calkujaca = wzmocnienieCalkujace * calka;

    // Skladowa rozniczkujaca
    double rozniczkujaca = wzmocnienieRowniczkujace * (uchyb - poprzedniUchyb);

    // Aktualizacja poprzedniego uchybu
    poprzedniUchyb = uchyb;
    //calkujaca = 0;
    //rozniczkujaca = 0;
   //out << proporcjonalna << " " << calkujaca << " " << rozniczkujaca << "\n";
    return proporcjonalna + calkujaca + rozniczkujaca;
}
double PID::sumator(double wartoscZadana, double wartoscMierzona) {
    // Wylicza uchyb jako rroznice miedzy wartoscia zadana a mierzona
    return wartoscZadana - wartoscMierzona;
}

double PID::obliczSprzezenie(double wartoscZadana, double wartoscMierzona) {
    // Wylicza uchyb za pomoca sumatora
    double uchyb = sumator(wartoscZadana, wartoscMierzona);

    // Oblicza sygnaa sterujacy za pomoca PID
    double sygnalSterujacy = this->oblicz(uchyb, wartoscMierzona);

    //// Zaktualizuj model ARX
    //if (!dane.empty()) {
    //    dane.back()->setU(sygnalSterujacy);
    //}

    return sygnalSterujacy;
}