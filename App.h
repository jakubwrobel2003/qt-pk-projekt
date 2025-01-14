#ifndef APP_H
#define APP_H
#include "ARX.h"
#include <fstream>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include "BuforDanych.h"
#include "Sygnal.h"
#include "PID.h"

using namespace std;
class ARX;

class App {
private:
    bool run = false; // start stop
    //Relacja agregacji
    ARX* arx;// Relacja zale¿noœci

public:
    Sygnal* syg;//Relacja zale¿noœci
    PID* Pid;
    std::vector<BuforDanych*> data;
  //  void clikrun(); //start stop
    void symulacjaStep();
    void symulacja(bool start); //g³ówna fukcja programu
    void wypiszDane(); //wykonuje wypisz na wstkich obiektach bufordanyh po kolei od 1 do n na ekran piersza wersja
    void setARX(ARX* A) { this->arx = A; }
    void setSyg(Sygnal* S) { this->syg = S; }
    void setPID(PID* p) { this->Pid = p; }
    std::string a;
    std::string b;
    double u;
    double p;
    double t;
    double i;
    double amplituda;
    int sygnal;

    void startSymulacja();  // rozpocznij symulacj?
    void stopSymulacja();   // zatrzymaj symulacj?
    void zapisBazydanychdopliku();
    App();
    ~App();
    void odczytajDaneZPliku() {
        const std::string nazwaPliku = "example.txt"; // Plik na sztywno
        std::ifstream file(nazwaPliku); // Otwieramy plik
        if (!file.is_open()) {
            std::cerr << "Nie mo¿na otworzyæ pliku: " << nazwaPliku << std::endl;
            return;
        }

        std::string linia;
        string a;
        string b;

        // Przetwarzanie kolejnych wierszy danych
        while (std::getline(file, linia)) {
            std::istringstream iss(linia);//obiekt strumienia wejscia

            int id;
            double zaklucenie;
            std::string str1, str2;
            double val1, val2,val3, val4,val5;

           // int, double, string, string, double, double
            if (iss >> id >> zaklucenie >> str1 >> str2 >> val1 >> val2>>val3>>val4>>val5) {
                // Tworzenie obiektu BuforDanych
                BuforDanych* bufor = new BuforDanych();
                bufor->setID(id);
                bufor->setZaklucenie(zaklucenie);
                bufor->setB(str1);

                bufor->setA(str2);
                bufor->setU(val2);
                bufor->setY(val1);
                Pid->ustawWzmocnienieCalkujace(val3);
                Pid->ustawWzmocnienieProporcjonalne(val4);
                Pid->ustawWzmocnienieRowniczkujace(val5);
                a=str2;
                b=str1;

                data.push_back(bufor);
               //S std::cout << "Dodano dane do BuforDanych: ID = " << id << std::endl;
            }
            else {
               // std::cerr << "B³¹d odczytu wiersza danych: " << linia << std::endl;
            }
        }

        file.close();
    }
};
#endif
