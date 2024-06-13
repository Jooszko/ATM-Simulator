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
        cout << "[BANKOMAT]" << endl << endl;

        cout << "1. Zaloguj\n";
        cout << "2. Utworz konto\n";
        cout << "3. Zakoncz program\n\n";
        cout << "Wybierz opcje: ";
        cin >> wybor;

        Bankomat bankomat;
        bankomat.wczytajKontaZPliku();

        switch (wybor) {
        case 1: {
            string login, haslo;
            system("cls");
            cout << "[BANKOMAT]" << endl << endl;

            cout << "Podaj login: ";
            cin >> login;
            cout << "Podaj hasło: ";
            cin >> haslo;

            Konto_Bankowe* konto = bankomat.zaloguj(login, haslo);

            if (konto) {
                cout <<endl<< "Zalogowano!"<<endl<<endl;

                cout << "Nacisnij dowolny klawisz, aby kontynuowac..." << endl;
                _getch();
                int wybor;
                do {
                    system("cls");
                    cout << "[BANKOMAT]" << endl << endl;

                    cout << "Witaj " << konto->getImie() << " " << konto->getNazwisko()<<endl << endl;
                    cout << "1. Wplac pieniadze\n";
                    cout << "2. Wyplac pieniadze\n";
                    cout << "3. Sprawdz saldo\n";
                    cout << "4. Zmien Haslo\n";
                    cout << "5. Zmien PIN\n";
                    cout << "6. Usun konto\n";
                    cout << "7. Wyloguj\n";
                    cout << "8. Zakoncz program\n\n";
                    cout << "Wybierz opcje: ";
                    cin >> wybor;

                    switch (wybor) {
                    case 1: {
                        double kwota;
                        system("cls");
                        cout << "[BANKOMAT]" << endl << endl;

                        cout << "Podaj kwote do wplaty: ";
                        cin >> kwota;
                        system("cls");
                        konto->wplac(kwota);
                        bankomat.zapiszKontaDoPliku();
                        cout <<endl<< "Nacisnij dowolny klawisz, aby kontynuowac..." << endl;
                        _getch();
                        break;
                    }
                    case 2: {
                        double kwota;
                        system("cls");
                        cout << "[BANKOMAT]" << endl << endl;

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
                        cout << "[BANKOMAT]" << endl << endl;

                        konto->sprawdzSaldo();
                        cout << endl << "Nacisnij dowolny klawisz, aby kontynuowac..." << endl;
                        _getch();
                        break;
                    }
                    case 4: {
                        string stareHaslo, noweHaslo;
                        system("cls");
                        cout << "[BANKOMAT]" << endl << endl;

                        cout << "Podaj stare haslo: ";
                        cin >> stareHaslo;
                        cout << "Podaj nowe haslo: ";
                        cin >> noweHaslo;

                        konto->zmienHaslo(stareHaslo, noweHaslo);
                        konto->setHaslo(konto->getHaslo());
                        bankomat.zapiszKontaDoPliku();
                        cout << endl << "Nacisnij dowolny klawisz, aby kontynuowac..." << endl;
                        _getch();
                        break;
                    }
                    case 5: {
                        string staryPin, nowyPin;
                        system("cls");
                        cout << "[BANKOMAT]" << endl << endl;

                        do {
                            cout << "Podaj stary PIN: ";
                            cin >> staryPin;
                            if (staryPin.length() != 4) {
                                cout << "Blad: nieprawidlowa dlugosc numeru PIN!" << endl;
                            }
                        } while (staryPin.length() != 4);
                        
                        do {
                            cout << "Podaj nowy PIN: ";
                            cin >> nowyPin;
                            if (nowyPin.length() != 4) {
                                cout << "Blad: nieprawidlowa dlugosc numeru PIN!" << endl;
                            }
                        } while (nowyPin.length() != 4);

                        konto->zmienPin(staryPin, nowyPin);
                        bankomat.zapiszKontaDoPliku();
                        cout << endl << "Nacisnij dowolny klawisz, aby kontynuowac..." << endl;
                        _getch();
                        break;
                    }
                    case 6: {
                        char decyzja;
                        do {
                            system("cls");
                            cout << "[BANKOMAT]" << endl << endl;

                            cout << "Czy na pewno chcesz usunac konto? (t/n): ";
                            cin >> decyzja;
                        } while (decyzja!='t' && decyzja!='n');
                        if (decyzja == 't') {
                            bankomat.usunKonto(konto);
                            bankomat.zapiszKontaDoPliku();
                            cout <<endl<< "Usunieto konto." << endl;
                            cout << endl << "Nacisnij dowolny klawisz, aby kontynuowac..." << endl;
                            _getch();
                        }
                   
                        break;
                    }
                    case 7: {
                        system("cls");
                        cout << "[BANKOMAT]" << endl << endl;

                        cout << "Wylogowano." << endl;
                        cout << endl << "Nacisnij dowolny klawisz, aby kontynuowac..." << endl;
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
                        cout << "[BANKOMAT]" << endl << endl;

                        cout << "Nieznana opcja." << endl << endl;
                        cout << "Nacisnij dowolny klawisz, aby kontynuowac..." << endl;
                        _getch();
                        break;
                    }
                    }
                } while (wybor != 6 && wybor != 7);
            }
            else {
                cout <<endl<< "Blad: nieprawidlowe dane logowania." << endl<<endl;

                cout << "Nacisnij dowolny klawisz, aby kontynuowac..." << endl;
                _getch();
            }
            break;
        }
        case 2: {
            system("cls");
            cout << "[BANKOMAT]" << endl << endl;

            bankomat.utworzKonto();
            cout <<endl<< "Nacisnij dowolny klawisz, aby kontynuowac..." << endl;
            _getch();
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

