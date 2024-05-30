#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "Konto.h"
#include "Konto_Bankowe.h"
#include "Bankomat.h"

using namespace std;

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
