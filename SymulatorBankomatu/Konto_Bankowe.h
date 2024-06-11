#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include "Konto.h"

using namespace std;


class Konto_Bankowe : public Konto {
	private:
	    string pin;
	    double saldo;
		string imie;
		string nazwisko;
		int pesel;
	public:
	    Konto_Bankowe(const string& login, const string& haslo, const string& pin, double saldo, const string& imie, const string& nazwisko, const int& pesel): Konto(login, haslo), pin(pin), saldo(saldo), imie(imie), nazwisko(nazwisko), pesel(pesel) {}
	
		string getPin() const;
	    //double getSaldo() const { return saldo; }
		double getSaldo() const;
		string getImie() const;
		string getNazwisko() const;
		int getPesel() const;
	
		void wplac(double kwota);
	
		bool wyplac(double kwota);
	
		double sprawdzSaldo() const;
	
		void zmienPin(const string& staryPin, const string& nowyPin);
	};
