#include "Konto.h"
#include <iostream>
#include "Hash.h"

//Konto::~Konto() {
//	delete this;
//}

bool Konto::autoryzacja(const string& login, const string& haslo) {

	string pass_hash = Hash::generateHash(haslo, this->salt);

	return this->login == login && this->haslo == pass_hash;
}

string Konto::getLogin() const { return login; }
string Konto::getHasloKonto() const { return haslo; }
