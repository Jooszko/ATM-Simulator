#include "Konto_Bankowe.h"

string Konto_Bankowe::getPin() const { return pin; }
double Konto_Bankowe::getSaldo() const { return saldo; }
string Konto_Bankowe::getImie() const { return imie; }
string Konto_Bankowe::getNazwisko() const { return nazwisko; }
int Konto_Bankowe::getPesel() const { return pesel; }

void Konto_Bankowe::wplac(double kwota) {
	saldo += kwota;
	cout << "Wp³acono " << kwota << ". Twoje saldo wynosi teraz " << saldo << "." << endl;
}

bool Konto_Bankowe::wyplac(double kwota) {
	if (kwota <= saldo) {
		saldo -= kwota;
		cout << "Wyp³acono " << kwota << ". Twoje saldo wynosi teraz " << saldo << "." << endl;
		return true;
	}
	else {
		cout << "B³¹d: niewystarczaj¹ce œrodki na koncie." << endl;
		return false;
	}
}

double Konto_Bankowe::sprawdzSaldo() const {
	cout << "Twoje saldo wynosi " << saldo << "." << endl;
	return saldo;
}

void Konto_Bankowe::zmienPin(const string& staryPin, const string& nowyPin) {
	if (staryPin == pin) {
		if (staryPin == nowyPin) {
			cout << "B³¹d: nowy PIN nie mo¿e byæ taki sam jak stary PIN." << endl;
		}
		else {
			pin = nowyPin;
			cout << "PIN zosta³ pomyœlnie zmieniony." << endl;
		}
	}
	else {
		cout << "B³¹d: podano nieprawid³owy stary PIN." << endl;
	}
}