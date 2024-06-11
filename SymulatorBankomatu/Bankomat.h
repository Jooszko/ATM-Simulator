#pragma once
#include <iostream>
#include <vector>
#include <conio.h>
#include "Konto_Bankowe.h"
#include "DataBase.h"


using namespace std;

class Bankomat {
protected:
    vector<Konto_Bankowe*> konta;
    DataBase dataBase;
public:
    ~Bankomat();

    void dodajKonto(Konto_Bankowe* konto);

    Konto_Bankowe* zaloguj(const string& login, const string& haslo);

    bool czyIstnieje(const string& login);

    void utworzKonto();

    void zapiszKontaDoPliku();

    void wczytajKontaZPliku();
};
