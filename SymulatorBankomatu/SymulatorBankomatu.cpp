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

    //database add
    DataBase dataBase;
    //sqlite3* DB;
    /*dataBase.createDb(dir);
    dataBase.createTable(dir);*/

    //Konto_Bankowe kontonew("elo", "pass", "123", 50);


    
    //dataBase.insertData(dir);
    
    dataBase.selectData();

    

    while (true) {
        int wybor;
        system("cls");
        cout << "1. Zaloguj\n";
        cout << "2. Utworz konto\n";
        cout << "3. Zakoncz program\n";
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
                    system("cls");
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
                    case 5: {
                        system("cls");
                        cout << "Wylogowano." << endl;
                        cout << "Nacisnij dowolny klawisz, aby kontynuowac..." << endl;
                        _getch();
                        break;
                    }
                    case 6: {
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

