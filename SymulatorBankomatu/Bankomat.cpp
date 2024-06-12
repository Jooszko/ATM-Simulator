#include "Bankomat.h"
#include "sqlite3.h"
//#include "DataBase.h"

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
    system("cls");
    //DataBase dataBase;

    string login, haslo, pin, imie, nazwisko;
    double saldo;
    int pesel;
    cout << "Podaj imie: ";
    cin >> imie;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    cout << "Podaj pesel: ";
    cin >> pesel;
    cout << "Podaj login: ";
    cin >> login;
    cout << "Podaj haslo: ";
    cin >> haslo;
    cout << "Podaj PIN: ";
    cin >> pin;
    cout << "Podaj saldo poczatkowe: ";
    cin >> saldo;

    if (!czyIstnieje(login)) {
        Konto_Bankowe* noweKonto = new Konto_Bankowe(login, haslo, pin, saldo, imie, nazwisko, pesel);
        
        //konta.push_back(noweKonto);

        dataBase.insertData(noweKonto);
        //zapiszKontaDoPliku();
    }
    else {
        cout << "B��d: Login jest ju� u�ywany." << endl;
    }
}

void Bankomat::zapiszKontaDoPliku() {
    /*ofstream plik("konta.csv");
    for (auto& konto : konta) {
        plik << konto->getLogin() << "," << konto->getHaslo() << "," << konto->getPin() << "," << konto->getSaldo() << "\n";
    }
    plik.close();*/

    //DataBase dataBase;

    dataBase.updateData(konta);
}

void Bankomat::wczytajKontaZPliku() {

    //DataBase dataBase;
    konta = dataBase.data();

    /*ifstream plik("konta.csv");
    string linia;*/

    /*while (getline(plik, linia)) {
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
    plik.close();*/
}