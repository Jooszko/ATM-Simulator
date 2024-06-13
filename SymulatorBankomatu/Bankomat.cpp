#include "Bankomat.h"
#include "sqlite3.h"
#include <string>
#include "Hash.h"

Bankomat::~Bankomat() {
    for (auto konto : konta) {
        delete konto;
    }
}

void Bankomat::dodajKonto(Konto_Bankowe* konto) {
    konta.push_back(konto);
}

void Bankomat::usunKonto(Konto_Bankowe* konto) {
    konta.erase(std::remove(konta.begin(), konta.end(), konto), konta.end());
}

Konto_Bankowe* Bankomat::zaloguj(const string& login, const string& haslo) {
    for (auto& konto : konta) {
        if (konto->autoryzacja(login, haslo)) {
            return konto;
        }
    }
    return nullptr;
}

bool Bankomat::czyIstnieje(const string& login) {

    for (auto& konto : konta) {
        if (konto->getLogin() == login) {
            return true;
        }
    }
    return false;

}

void Bankomat::utworzKonto() {
    string login, haslo, pin, imie, nazwisko;
    double saldo;
    long long pesel;
    string peselStr;
    cout << "Podaj imie: ";
    cin >> imie;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    do {
        cout << "Podaj pesel: ";
        cin >> pesel;
        peselStr = to_string(pesel);
        if (peselStr.length() != 11)
           cout << "Blad: nieprawidlowa dlugosc numeru  PESEL!" << endl;
    } while (peselStr.length() != 11);
    cout << "Podaj login: ";
    cin >> login;
    cout << "Podaj haslo: ";
    cin >> haslo;
    do {
        cout << "Podaj PIN: ";
        cin >> pin;
        if (pin.length() != 4) {
            cout << "Blad: nieprawidlowa dlugosc numeru  PIN!" << endl;
        }
    } while (pin.length() != 4);
    cout << "Podaj saldo poczatkowe: ";
    cin >> saldo;

    
    if (!czyIstnieje(login)) {

        string pass_salt = Hash::generateSalt(10);
        string pass_hash = Hash::generateHash(haslo, pass_salt);
        

        Konto_Bankowe* noweKonto = new Konto_Bankowe(login, pass_hash, pass_salt, pin, saldo, imie, nazwisko, pesel);

        dataBase.insertData(noweKonto);
        
    }
    else {
        cout << "Blad: Login jest już uzywany." << endl;
    }
}

void Bankomat::zapiszKontaDoPliku() {

    dataBase.updateData(konta);
}

void Bankomat::wczytajKontaZPliku() {

    konta = dataBase.data();

}