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

    //database add
    DataBase dataBase;
    //sqlite3* DB;
    /*dataBase.createDb(dir);
    dataBase.createTable(dir);*/

    /*Konto_Bankowe* noweKonto = new Konto_Bankowe("login", "haslo", "12", 21, "imie", "nazwisko", 12);


    
    dataBase.insertData(noweKonto);*/

    //dataBase.createTable();
    

    dataBase.selectData();

    

    while (true) {
        int wybor;
        system("cls");
        cout << "1. Zaloguj\n";
        cout << "2. Utworz konto\n";
        cout << "3. Zakończ program\n";
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
            cout << "Podaj haslo: ";
            cin >> haslo;

            Konto_Bankowe* konto = bankomat.zaloguj(login, haslo);
            if (konto) {
                int wybor;
                do {
                    //system("cls");
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
                        cout << "Podaj kwote do wplaty: ";
                        cin >> kwota;
                        system("cls");
                        konto->wplac(kwota);
                        bankomat.zapiszKontaDoPliku();
                        cout << "Nacisnij dowolny klawisz, aby kontynuowac..." << endl;
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
                        break;
                    }
                    case 3: {
                        system("cls");
                        konto->sprawdzSaldo();
                        cout << "Nacisnij dowolny klawisz, aby kontynuowac..." << endl;
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
                            cout << "Nacisnij dowolny klawisz, aby kontynuowac..." << endl;
                            _getch();
                        }
                   
                        break;
                    }
                    case 7: {
                        system("cls");
                        cout << "Wylogowano." << endl;
                        cout << "Nacisnij dowolny klawisz, aby kontynuowac..." << endl;
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
                        cout << "Nacisnij dowolny klawisz, aby kontynuowac..." << endl;
                        _getch();
                        break;
                    }
                    }
                } while (wybor != 6 && wybor != 5);
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

