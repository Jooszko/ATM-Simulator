#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Konto {
protected:
    string login;
    string haslo;
public:
    Konto(const string& login, const string& haslo)
        : login(login), haslo(haslo) {}

    virtual ~Konto() {}

    bool autoryzacja(const string& login, const string& haslo) {
        return this->login == login && this->haslo == haslo;
    }

    string getLogin() const { return login; }
    string getHaslo() const { return haslo; }
};

class Konto_Bankowe : public Konto {
private:
    string pin;
    double saldo;
public:
    Konto_Bankowe(const string& login, const string& haslo, const string& pin, double saldo)
        : Konto(login, haslo), pin(pin), saldo(saldo) {}

    string getPin() const { return pin; }
    double getSaldo() const { return saldo; }

    void wplac(double kwota) {
        saldo += kwota;
        cout << "Wpłacono " << kwota << ". Twoje saldo wynosi teraz " << saldo << "." << endl;
    }

    bool wyplac(double kwota) {
        if (kwota <= saldo) {
            saldo -= kwota;
            cout << "Wypłacono " << kwota << ". Twoje saldo wynosi teraz " << saldo << "." << endl;
            return true;
        }
        else {
            cout << "Błąd: niewystarczające środki na koncie." << endl;
            return false;
        }
    }

    double sprawdzSaldo() const {
        cout << "Twoje saldo wynosi " << saldo << "." << endl;
        return saldo;
    }

    void zmienPin(const string& staryPin, const string& nowyPin) {
        if (staryPin == pin) {
            if (staryPin == nowyPin) {
                cout << "Błąd: nowy PIN nie może być taki sam jak stary PIN." << endl;
            }
            else {
                pin = nowyPin;
                cout << "PIN został pomyślnie zmieniony." << endl;
            }
        }
        else {
            cout << "Błąd: podano nieprawidłowy stary PIN." << endl;
        }
    }
};

class Bankomat {
private:
    vector<Konto_Bankowe*> konta;
public:
    ~Bankomat() {
        for (auto konto : konta) {
            delete konto;
        }
    }

    void dodajKonto(Konto_Bankowe* konto) {
        konta.push_back(konto);
    }

    Konto_Bankowe* zaloguj(const string& login, const string& haslo) {
        for (auto& konto : konta) {
            if (konto->autoryzacja(login, haslo)) {
                return konto;
            }
        }
        return nullptr;
    }

    bool czyIstnieje(const string& login, const string& haslo, const string& pin) {
        for (auto& konto : konta) {
            if (konto->getLogin() == login || konto->getHaslo() == haslo || konto->getPin() == pin) {
                return true;
            }
        }
        return false;
    }

    void utworzKonto() {
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
            cout << "Błąd: Login, hasło lub PIN jest już używany." << endl;
        }
    }

    void zapiszKontaDoPliku() {
        ofstream plik("konta.csv");
        for (auto& konto : konta) {
            plik << konto->getLogin() << "," << konto->getHaslo() << "," << konto->getPin() << "," << konto->getSaldo() << "\n";
        }
        plik.close();
    }

    void wczytajKontaZPliku() {
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
};

int main() {
    Bankomat bankomat;
    bankomat.wczytajKontaZPliku();

    while (true) {
        int wybor;
        cout << "1. Zaloguj\n";
        cout << "2. Utworz konto\n";
        cout << "3. Zakoncz program\n";
        cout << "Wybierz opcje: ";
        cin >> wybor;

        switch (wybor) {
        case 1: {
            string login, haslo;
            cout << "Podaj login: ";
            cin >> login;
            cout << "Podaj haslo: ";
            cin >> haslo;

            Konto_Bankowe* konto = bankomat.zaloguj(login, haslo);
            if (konto) {
                int wybor;
                do {
                    cout << "1. Wplac pieniadze\n";
                    cout << "2. Wyplac pieniadze\n";
                    cout << "3. Sprawdz saldo\n";
                    cout << "4. Zmien PIN\n";
                    cout << "5. Wyloguj\n";
                    cout << "6. Zakoncz program\n";
                    cout << "Wybierz opcje: ";
                    cin >> wybor;

                    switch (wybor) {
                    case 1: {
                        double kwota;
                        cout << "Podaj kwote do wplaty: ";
                        cin >> kwota;
                        konto->wplac(kwota);
                        bankomat.zapiszKontaDoPliku();
                        break;
                    }
                    case 2: {
                        double kwota;
                        cout << "Podaj kwote do wyplaty: ";
                        cin >> kwota;
                        if (konto->wyplac(kwota)) {
                            bankomat.zapiszKontaDoPliku();
                        }
                        break;
                    }
                    case 3: {
                        konto->sprawdzSaldo();
                        break;
                    }
                    case 4: {
                        string staryPin, nowyPin;
                        cout << "Podaj stary PIN: ";
                        cin >> staryPin;
                        cout << "Podaj nowy PIN: ";
                        cin >> nowyPin;
                        konto->zmienPin(staryPin, nowyPin);
                        bankomat.zapiszKontaDoPliku();
                        break;
                    }
                    case 5: {
                        cout << "Wylogowano." << endl;
                        break;
                    }
                    case 6: {
                        cout << "Zakonczono program." << endl;
                        return 0;
                    }
                    default: {
                        cout << "Nieznana opcja." << endl;
                        break;
                    }
                    }
                } while (wybor != 5);
            }
            else {
                cout << "Blad: nieprawidlowe dane logowania." << endl;
            }
            break;
        }
        case 2: {
            bankomat.utworzKonto();
            break;
        }
        case 3: {
            cout << "Zakonczono program." << endl;
            return 0;
        }
        default: {
            cout << "Nieznana opcja." << endl;
            break;
        }
        }
    }

    return 0;
}
