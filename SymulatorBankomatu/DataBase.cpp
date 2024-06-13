#include "DataBase.h"
#include <vector>
#include "Konto_Bankowe.h"
#include <iostream>
#include <cstdio>

#include "Hash.h"

//const char* dir = "c:\\Users\\jonas\\Desktop\\ProjektBankomat\\ATM-Simulator\\SymulatorBankomatu\\bankDatabase.bd";
const char* dir = "bankDatabase.bd";
const std::string databaseFilename = "bankDatabase.bd";

vector<Konto_Bankowe*> uzytkownicy;

int DataBase::createDb() {
    FILE* file;
    errno_t err = fopen_s(&file, databaseFilename.c_str(), "r");
    if (err == 0 && file != nullptr) {
        fclose(file);
        sqlite3* DB;
        int exit = 0;

        exit = sqlite3_open(dir, &DB);

        sqlite3_close(DB);
    }
    return 0;
};

int DataBase::createTable() {

    sqlite3* DB;

    string sql = "CREATE TABLE IF NOT EXISTS USERS("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "LOGIN TEXT NOT NULL, "
        "PASSWORD TEXT NOT NULL, "
        "PASS_SALT TEXT NOT NULL, "
        "PIN INT NOT NULL, "
        "BALANCE INT, "
        "IMIE TEXT NOT NULL, "
        "NAZWISKO TEXT NOT NULL, "
        "PESEL INT NOT NULL); ";

    try {
        int exit = 0;
        exit = sqlite3_open(dir, &DB);

        char* messaggeError;
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

        if (exit != SQLITE_OK) {
            cerr << "B³¹d tworzenia tabeli" << endl;

            sqlite3_free(messaggeError);
        }
        else {
            cout << "Tabela stworzona prawidlowo" << endl;
        }
        sqlite3_close(DB);

    }
    catch (const exception& e) {
        cerr << e.what();
    }

    return 0;
};

int DataBase::insertData(Konto_Bankowe* noweKonto) {

    sqlite3* DB;

    char* messaggeError;

    int exit = sqlite3_open(dir, &DB);

    string sql("INSERT INTO USERS (LOGIN, PASSWORD, PASS_SALT, PIN, BALANCE, IMIE, NAZWISKO, PESEL) VALUES ('" + noweKonto->getLogin() + "', '"+ noweKonto->getHasloKonto() + "', '"+ noweKonto->getSalt() + "', " + noweKonto->getPin() + ", " + to_string(noweKonto->getSaldo()) + ", '" + noweKonto->getImie() + "', '" + noweKonto->getNazwisko() + "', " + to_string(noweKonto->getPesel()) + ");");

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK) {
        cerr << "Blad dodania danych"<<" " << messaggeError << endl;
        sqlite3_free(messaggeError);
    }
    else {
        cout << endl<< "Konto zostalo utworzone." << endl;
    }

    return 0;
};

int DataBase::selectData() {

    sqlite3* DB;
    int exit = sqlite3_open(dir, &DB);

    string sql = "SELECT * FROM USERS";

    sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);

    return 0;

};

int DataBase::callback(void* NotUsed, int argc, char** argv, char** azColName) {

    Konto_Bankowe* uzytkownikBaza = new Konto_Bankowe(argv[1], argv[2], argv[3], argv[4], stod(argv[5]), argv[6], argv[7], stoi(argv[8]));

    uzytkownicy.push_back(uzytkownikBaza);

    return 0;
}

vector<Konto_Bankowe*> DataBase::data() {
    uzytkownicy.clear();
    selectData();
    return uzytkownicy;
};

int DataBase::updateData(vector<Konto_Bankowe*> konta) {
    
    if (konta.size() != 0) {
        sqlite3* DB;

        char* messaggeError;

        int exit = sqlite3_open(dir, &DB);

        string sqlDelete("DELETE FROM USERS");

        exit = sqlite3_exec(DB, sqlDelete.c_str(), NULL, 0, &messaggeError);

        if (exit != SQLITE_OK) {
            cerr << "Blad usowania danych podczas aktualizacji" << endl;
            sqlite3_free(messaggeError);
        }
        else {
        
            for (auto& konto : konta) {

                string sqlAdd("INSERT INTO USERS (LOGIN, PASSWORD, PASS_SALT, PIN, BALANCE, IMIE, NAZWISKO, PESEL) VALUES ('" + konto->getLogin() + "', '" + konto->getHasloKonto() + "', '"+ konto->getSalt() + "', " + konto->getPin() + ", " + to_string(konto->getSaldo()) + ", '" + konto->getImie() + "', '" + konto->getNazwisko() + "', " + to_string(konto->getPesel()) + ");");
                exit = sqlite3_exec(DB, sqlAdd.c_str(), NULL, 0, &messaggeError);

                if (exit != SQLITE_OK) {
                    cerr << "Blad dodania danych podczas aktualizacji" << endl;
                    sqlite3_free(messaggeError);
                    break;
                }
            }
        }
    }

    return 0;
};