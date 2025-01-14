#include "BuforDanych.h"
#include <cstring>
#include <string>
using namespace std;
int BuforDanych::licznikInstancji = -1;

BuforDanych::BuforDanych() : ID(++licznikInstancji), zaklucenie(0) {
    i=ID;
}



void BuforDanych::wypisztabele() {
    // Wyœwietlenie ID i Zaklucenie
    std::cout << this->getID() << " | " << this->getZaklucenie();

    //formacie liczba;liczba;...
    std::cout << " ";
    for (size_t i = 0; i < b.size(); ++i) {
        std::cout << b[i];
        if (i < b.size() - 1) {
            std::cout << ";"; 
        }
    }
    std::cout << "|";
    for (size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i];
        if (i < b.size() - 1) {
            std::cout << ";";
        }
    }
    std::cout << " | " << this->getY() << " | " << this->getU();
    std::cout << "\n";
}
// Setery
void BuforDanych::setZaklucenie(double data) {
    zaklucenie = data;
}

void BuforDanych::setID(int id) {
    ID = id;
}
void BuforDanych::setB(const string& data1) {
    if (data1.empty()) { 
        return;
    }

    string data(data1);

    size_t pos = 0;
    while ((pos = data.find(";")) != string::npos) { 
        string token = data.substr(0, pos); 
        try {
            b.push_back(std::stod(token)); 
        }
        catch (const std::invalid_argument&) {
            cerr << "B³¹d " << token << std::endl;
        }
        data.erase(0, pos + 1); 
    }

   
    try {
        if (!data.empty()) {
            b.push_back(std::stod(data));
        }
    }
    catch (const std::invalid_argument&) {
      cerr << "B³¹d " << data << std::endl;
    }
}
void BuforDanych::setA(const string& data1) {
    if (data1.empty()) {
        return;//Sprawdzamy czy jest pusty 
    }

    string data(data1);//kopiujemy dane

    size_t pos = 0;//pozycja separatora
    while ((pos = data.find(";")) != string::npos) {
    //pêtla dopuki nie znadziemy wsztkich ";"
        string token = data.substr(0, pos);
        //wyciagamy fragment do ; np 2.3
        try {
            a.push_back(std::stod(token));//zamiana stringa na doubla
        }
        catch (const std::invalid_argument&) {
            //zwramy blad gdy fragmet nie jest liczba
            cerr << "B³¹d " << token << std::endl;
        }
        data.erase(0, pos + 1);//usuwamy fragment waz z searaorem
    }


    try {
        if (!data.empty()) {
         // ostatni liczba jest bez ; to tudaj dodamy do a i 'wy¿ucamy wyjatek
         // gdy nie jest liczba'
            a.push_back(std::stod(data));
        }
    }
    catch (const std::invalid_argument&) {
        cerr << "B³¹d " << data << std::endl;
    }
}


// Getery
double BuforDanych::getZaklucenie() const {
    return zaklucenie;
}

int BuforDanych::getID() const {
    return ID;
}
int BuforDanych::getI()const {
    return i;
}
double BuforDanych::getA(int i) {
    if (i < 0 || i >= a.size()) {
        std::cerr << "B??d: Indeks " << i << " poza zakresem wektora A. Rozmiar A: " << a.size() << "\n";
        return 0; // Zwró? warto?? domy?ln? zamiast rzucania wyj?tku
    }
    return a[i];
}

double BuforDanych::getb(int i) {
    if (i < 0 || i >= b.size()) {
        std::cerr << "B??d: Indeks " << i << " poza zakresem wektora b. Rozmiar b: " << b.size() << "\n";
        return 0; // Zwró? warto?? domy?ln? zamiast rzucania wyj?tku
    }
    return b[i];
}

double BuforDanych::getY() {
    return y;
}












