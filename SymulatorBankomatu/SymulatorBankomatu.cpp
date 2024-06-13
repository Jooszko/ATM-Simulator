#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>

#include "Konto.h"
#include "Konto_Bankowe.h"
#include "Bankomat.h"
#include "DataBase.h"

#include <stdio.h>
#include <sqlite3.h>

using namespace std;

int main() {

    setlocale(LC_CTYPE, "Polish");

    DataBase dataBase;

    dataBase.createDb();
    dataBase.createTable();
    dataBase.selectData();

    

    while (true) {
        int wybor;
        system("cls");
        cout << "1. Zaloguj\n";
        cout << "2. Utwórz konto\n";
        cout << "3. Zakończ program\n\n";
        cout << "Wybierz opcje: ";
        cin >> wybor;

        Bankomat bankomat;
        bankomat.wczytajKontaZPliku();

        switch (wybor) {
        case 1: {
            string login, haslo;
            system("cls");
            cout << "Podaj login: ";
            cin >> login;
            cout << "Podaj hasło: ";
            cin >> haslo;

            Konto_Bankowe* konto = bankomat.zaloguj(login, haslo);

            if (konto) {
                cout <<endl<< "Zalogowano!"<<endl<<endl;

                cout << "Nacisnij dowolny klawisz, aby kontynuować..." << endl;
                _getch();
                int wybor;
                do {
                    system("cls");
                    cout << "Witaj " << konto->getImie() << " " << konto->getNazwisko()<<endl << endl;
                    cout << "1. Wplać pieniadze\n";
                    cout << "2. Wyplać pieniadze\n";
                    cout << "3. Sprawdź saldo\n";
                    cout << "4. Zmień Haslo\n";
                    cout << "5. Zmień PIN\n";
                    cout << "6. Usuń konto\n";
                    cout << "7. Wyloguj\n";
                    cout << "8. Zakończ program\n\n";
                    cout << "Wybierz opcje: ";
                    cin >> wybor;

                    switch (wybor) {
                    case 1: {
                        double kwota;
                        system("cls");
                        cout << "Podaj kwote do wplaty: ";
                        cin >> kwota;
                        system("cls");
                        konto->wplac(kwota);
                        bankomat.zapiszKontaDoPliku();
                        cout <<endl<< "Nacisnij dowolny klawisz, aby kontynuować..." << endl;
                        _getch();
                        break;
                    }
                    case 2: {
                        double kwota;
                        system("cls");
                        cout << "Podaj kwote do wyplaty: ";
                        cin >> kwota;
                        if (konto->wyplac(kwota)) {
                            bankomat.zapiszKontaDoPliku();
                        }
                        _getch();
                        break;
                    }
                    case 3: {
                        system("cls");
                        konto->sprawdzSaldo();
                        cout << endl << "Nacisnij dowolny klawisz, aby kontynuować..." << endl;
                        _getch();
                        break;
                    }
                    case 4: {
                        string stareHaslo, noweHaslo;
                        system("cls");
                        cout << "Podaj stare hasło: ";
                        cin >> stareHaslo;
                        cout << "Podaj nowe hasło: ";
                        cin >> noweHaslo;

                        konto->zmienHaslo(stareHaslo, noweHaslo);
                        konto->setHaslo(konto->getHaslo());
                        bankomat.zapiszKontaDoPliku();
                        cout << endl << "Nacisnij dowolny klawisz, aby kontynuować..." << endl;
                        _getch();
                        break;
                    }
                    case 5: {
                        string staryPin, nowyPin;
                        system("cls");
                        cout << "Podaj stary PIN: ";
                        cin >> staryPin;
                        cout << "Podaj nowy PIN: ";
                        cin >> nowyPin;
                        konto->zmienPin(staryPin, nowyPin);
                        bankomat.zapiszKontaDoPliku();
                        cout << endl << "Nacisnij dowolny klawisz, aby kontynuować..." << endl;
                        _getch();
                        break;
                    }
                    case 6: {
                        char decyzja;
                        do {
                            cout << "Czy na pewno chcesz usunąć konto? (t/n): ";
                            cin >> decyzja;
                        } while (decyzja!='t' && decyzja!='n');
                        if (decyzja == 't') {
                            bankomat.usunKonto(konto);
                            bankomat.zapiszKontaDoPliku();
                            cout << "Usunięto konto." << endl;
                            cout << endl << "Nacisnij dowolny klawisz, aby kontynuować..." << endl;
                            _getch();
                        }
                   
                        break;
                    }
                    case 7: {
                        system("cls");
                        cout << "Wylogowano." << endl;
                        cout << endl << "Nacisnij dowolny klawisz, aby kontynuować..." << endl;
                        _getch();
                        break;
                    }
                    case 8: {
                        system("cls");
                        cout << "Zakonczono program." << endl;
                        return 0;
                    }
                    default: {
                        system("cls");
                        cout << "Nieznana opcja." << endl << endl;
                        cout << "Nacisnij dowolny klawisz, aby kontynuować..." << endl;
                        _getch();
                        break;
                    }
                    }
                } while (wybor != 6 && wybor != 7);
            }
            else {
                cout <<endl<< "Bład: nieprawidłowe dane logowania." << endl<<endl;

                cout << "Naciśnij dowolny klawisz, aby kontynuować..." << endl;
                _getch();
            }
            break;
        }
        case 2: {
            system("cls");
            bankomat.utworzKonto();
            break;
        }
        case 3: {
            system("cls");
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

