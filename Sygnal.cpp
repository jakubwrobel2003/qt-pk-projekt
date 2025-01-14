#include "Sygnal.h"
#include <math.h>
#include <QDebug>
Sygnal::Sygnal() {
	//konstruktor
    A=1.0;
}
double Sygnal::unit(double A) {
	
	return A;
}
double  Sygnal::sinusoidal(double A,int i, int t ) {
    double wynik = A * sin(((i % t) /static_cast<double>(t) ) * 2 * 3.14);
    qDebug()<<"DUIPA"<<"SDAD"<<t ;
	return wynik;
}
double Sygnal::rectangular(double A, double p, int i, int t) {
    qDebug()<<"DUIPA44"<<i%t<<"SDAD"<<t*p<<"SDAD"<<t<<"SDAD"<<p<<"\n";
    if (i%t < static_cast<double>(p*t) ) {
		return A;
	}
    return -A;
}
double  Sygnal::generateSignal(int liczba) {
    double g;
    if (liczba == 0) {
        g=unit(A);

	}
    else if (liczba==1) {
        g=sinusoidal(A, i, t);
	}
	else {
        g= rectangular(A, p, i, t);
	}
	// generowanie sygnalu
    return g;
}
