#pragma once
#include <vector>
#include "BuforDanych.h"
class PID {
private:
    double wzmocnienieProporcjonalne; // Wzmocnienie proporcjonalne (Kp)
    double wzmocnienieCalkujace;      // Wzmocnienie calkujace (Ki)
    double wzmocnienieRowniczkujace;  // Wzmocnienie ró¿niczkujace (Kd)

    double calka;            // Suma ca³kowania
  
    bool resetujCalke;       // Flaga resetu calkowania

public:
    double poprzedniUchyb = 0.5;
    PID(double kp, double ki, double kd);
    void resetPamieci(); 

    void ustawWzmocnienieProporcjonalne(double wartosc);
    void ustawWzmocnienieCalkujace(double wartosc);
    void ustawWzmocnienieRowniczkujace(double wartosc);

    double oblicz(double wartoscZadana, double wartoscMierzona); // Oblicz wyjscie regulatora
    double obliczSprzezenie(double wartoscZadana, double wartoscMierzona);

    // Funkcja sumatora
    double sumator(double wartoscZadana, double wartoscMierzona);
    double getWzmocnienieProporcjonalne() const {
        return wzmocnienieProporcjonalne;
    }

    double getWzmocnienieCalkujace() const {
        return wzmocnienieCalkujace;
    }

    double getWzmocnienieRowniczkujace() const {
        return wzmocnienieRowniczkujace;
    }
};

