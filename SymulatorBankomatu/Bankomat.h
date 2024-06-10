#pragma once
#include <iostream>
#include <vector>
#include <conio.h>
#include "Konto_Bankowe.h"


using namespace std;

class Bankomat {
private:
    vector<Konto_Bankowe*> konta;
public:
    ~Bankomat();

    void dodajKonto(Konto_Bankowe* konto);

    Konto_Bankowe* zaloguj(const string& login, const string& haslo);

    bool czyIstnieje(const string& login, const string& haslo, const string& pin);

    void utworzKonto();

    void zapiszKontaDoPliku();

    void wczytajKontaZPliku();
};
