#pragma once
#include <iostream>


using namespace std;

class Konto {
	protected:
	    string login;
	    string haslo;
		string salt;
	public:
	    Konto(const string& login, const string& haslo, const string& salt): login(login), haslo(haslo), salt(salt) {}

		/*~Konto(){}*/
	
	    virtual ~Konto() {}
	
		bool autoryzacja(const string& login, const string& haslo);

		string getLogin() const;
		string getHasloKonto() const;
	};

