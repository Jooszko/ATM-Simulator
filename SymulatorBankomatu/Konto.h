#pragma once
#include <iostream>


using namespace std;

class Konto {
	protected:
	    string login;
	    string haslo;
	public:
	    Konto(const string& login, const string& haslo): login(login), haslo(haslo) {}

		/*~Konto(){}*/
	
	    virtual ~Konto() {}
	
		bool autoryzacja(const string& login, const string& haslo);

		string getLogin() const;
		string getHasloKonto() const;
	};

