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
	public:
	    Konto_Bankowe(const string& login, const string& haslo, const string& pin, double saldo): Konto(login, haslo), pin(pin), saldo(saldo) {}
	
		string getPin() const;
	    //double getSaldo() const { return saldo; }
		double getSaldo() const;
	
		void wplac(double kwota);
	
		bool wyplac(double kwota);
	
		double sprawdzSaldo() const;
	
		void zmienPin(const string& staryPin, const string& nowyPin);
	};
