#include "Konto.h"
#include <iostream>

//Konto::~Konto() {
//	delete this;
//}

bool Konto::autoryzacja(const string& login, const string& haslo) {
	return this->login == login && this->haslo == haslo;
}

string Konto::getLogin() const { return login; }
string Konto::getHasloKonto() const { return haslo; }
