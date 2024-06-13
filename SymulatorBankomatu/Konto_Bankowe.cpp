#include "Konto_Bankowe.h"

string Konto_Bankowe::getPin() const { return pin; }
string Konto_Bankowe::getHaslo() const { return haslo; }
string Konto_Bankowe::getSalt() const { return salt; }
double Konto_Bankowe::getSaldo() const { return saldo; }
string Konto_Bankowe::getImie() const { return imie; }
string Konto_Bankowe::getNazwisko() const { return nazwisko; }
long long Konto_Bankowe::getPesel() const { return pesel; }

void Konto_Bankowe::wplac(double kwota) {
	saldo += kwota;
	cout << "Wplacono " << kwota << "zl. Twoje saldo wynosi teraz " << saldo << "zl." << endl;
}

bool Konto_Bankowe::wyplac(double kwota) {
	if (kwota <= saldo) {
		saldo -= kwota;
		cout << "Wyplacono " << kwota << "zl. Twoje saldo wynosi teraz " << saldo << "zl." << endl;
		return true;
	}
	else {
		cout << "Blad: niewystarczajace srodki na koncie." << endl;
		return false;
	}
}

double Konto_Bankowe::sprawdzSaldo() const {
	cout << "Twoje saldo wynosi " << saldo << "zl." << endl;
	return saldo;
}

void Konto_Bankowe::zmienPin(const string& staryPin, const string& nowyPin) {
	if (staryPin == pin) {
		if (staryPin == nowyPin) {
			cout << "Blad: nowy PIN nie moze byc taki sam jak stary PIN." << endl;
		}
		else {
			pin = nowyPin;
			cout << "PIN zostal pomyslnie zmieniony." << endl;
		}
	}
	else {
		cout << "Blad: podano nieprawidlowy stary PIN." << endl;
	}
}

void Konto_Bankowe::setHaslo(string hasloNew) {

	Konto::haslo = hasloNew;

}

void Konto_Bankowe::zmienHaslo(const string& stareHaslo, const string& noweHaslo) {

	string pass_hash_old_user = Hash::generateHash(stareHaslo, this->salt);

	if (pass_hash_old_user == haslo) {
		string pass_hash_new_user = Hash::generateHash(noweHaslo, this->salt);

		if (haslo == pass_hash_new_user) {
			cout << "Blad: nowe haslo nie moze byc takie same jak stare haslo." << endl;
		}
		else {
			haslo = pass_hash_new_user;
			cout <<endl<< "Haslo zostalo pomyslnie zmienione." << endl;
		}
	}
	else {
		cout << "Blad: podano nieprawidlowe stare haslo." << endl;
	}
}