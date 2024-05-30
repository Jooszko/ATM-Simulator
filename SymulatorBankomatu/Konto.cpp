#include "Konto.h"
#include <iostream>


bool Konto::autoryzacja(const string& login, const string& haslo) {
	return this->login == login && this->haslo == haslo;
}

string Konto::getLogin() const { return login; }
string Konto::getHaslo() const { return haslo; }
