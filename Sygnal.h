#pragma once
class Sygnal
{
private:
    double A=1;
    double p=1;
    int t=1;
    int i=1;


	
	double unit(double A);
	double sinusoidal(double A,int i,int t=60);
	double rectangular(double A,double p, int i, int t = 60);
	
public:
	void setA(double data) {
		A = data;
	}
	void setp(double data) {
		p = data;
	}
	void sett(int data) {
		t = data;
	}
	void seti(int data) {
		i = data;
	}
	double axx() {
		return A;
	}
	double generateSignal(int liczba=0);
	Sygnal();
};

