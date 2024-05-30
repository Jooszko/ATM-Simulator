#include "Bankomat.h"

Bankomat::~Bankomat() {
    for (auto konto : konta) {
        delete konto;
    }
}

void Bankomat::dodajKonto(Konto_Bankowe* konto) {
    konta.push_back(konto);
}

Konto_Bankowe* Bankomat::zaloguj(const string& login, const string& haslo) {
    for (auto& konto : konta) {
        if (konto->autoryzacja(login, haslo)) {
            return konto;
        }
    }
    return nullptr;
}

bool Bankomat::czyIstnieje(const string& login, const string& haslo, const string& pin) {
    for (auto& konto : konta) {
        if (konto->getLogin() == login || konto->getHaslo() == haslo || konto->getPin() == pin) {
            return true;
        }
    }
    return false;
}

void Bankomat::utworzKonto() {
    string login, haslo, pin;
    double saldo;
    cout << "Podaj login: ";
    cin >> login;
    cout << "Podaj haslo: ";
    cin >> haslo;
    cout << "Podaj PIN: ";
    cin >> pin;
    cout << "Podaj saldo poczatkowe: ";
    cin >> saldo;
    if (!czyIstnieje(login, haslo, pin)) {
        Konto_Bankowe* noweKonto = new Konto_Bankowe(login, haslo, pin, saldo);
        konta.push_back(noweKonto);
        cout << "Konto zostalo utworzone." << endl;
        zapiszKontaDoPliku();
    }
    else {
        cout << "B³¹d: Login, has³o lub PIN jest ju¿ u¿ywany." << endl;
    }
}

void Bankomat::zapiszKontaDoPliku() {
    ofstream plik("konta.csv");
    for (auto& konto : konta) {
        plik << konto->getLogin() << "," << konto->getHaslo() << "," << konto->getPin() << "," << konto->getSaldo() << "\n";
    }
    plik.close();
}

void Bankomat::wczytajKontaZPliku() {
    ifstream plik("konta.csv");
    string linia;
    while (getline(plik, linia)) {
        stringstream ss(linia);
        string login, haslo, pin;
        double saldo;
        getline(ss, login, ',');
        getline(ss, haslo, ',');
        getline(ss, pin, ',');
        ss >> saldo;
        Konto_Bankowe* konto = new Konto_Bankowe(login, haslo, pin, saldo);
        konta.push_back(konto);
    }
    plik.close();
}