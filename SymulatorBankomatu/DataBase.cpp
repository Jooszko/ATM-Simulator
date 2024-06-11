#include "DataBase.h"
#include <vector>
#include "Konto_Bankowe.h"

//const char* dir = "c:\\Users\\jonas\\Desktop\\ProjektBankomat\\ATM-Simulator\\SymulatorBankomatu\\bankDatabase.bd";
const char* dir = "bankDatabase.bd";
//vector<char**> uzytkownicy;
vector<Konto_Bankowe*> uzytkownicy;

//int DataBase::createDb(const char* s) {
int DataBase::createDb() {
    sqlite3* DB;
    int exit = 0;

    exit = sqlite3_open(dir, &DB);

    sqlite3_close(DB);

    return 0;
};

//int DataBase::createTable(const char* s) {
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

    //string sql = "DROP TABLE USERS";

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

//int DataBase::insertData(const char* s, Konto_Bankowe* noweKonto) {
int DataBase::insertData(Konto_Bankowe* noweKonto) {

    sqlite3* DB;

    char* messaggeError;

    int exit = sqlite3_open(dir, &DB);

    string sql("INSERT INTO USERS (LOGIN, PASSWORD, PASS_SALT, PIN, BALANCE, IMIE, NAZWISKO, PESEL) VALUES ('" + noweKonto->getLogin() + "', '"+ noweKonto->getHaslo() + "', 'salt', " + noweKonto->getPin() + ", " + to_string(noweKonto->getSaldo()) + ", '" + noweKonto->getImie() + "', '" + noweKonto->getNazwisko() + "', " + to_string(noweKonto->getPesel()) + ");");
    //string sql("INSERT INTO USERS (LOGIN, PASSWORD, PASS_SALT, PIN, BALANCE, IMIE, NAZWISKO, PESEL) VALUES ('" + noweKonto->getLogin() + "', '" + noweKonto->getHaslo() + "', 'salt', " + noweKonto->getPin() + ", " + to_string(noweKonto->getSaldo()) + ", 'jo', 'kubaczka', 124);");

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK) {
        cerr << "Blad dodania danych"<<" " << messaggeError << endl;
        sqlite3_free(messaggeError);
    }
    else {
        cout << "Konto zostalo utworzone." << endl;
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
    /*for (int i = 0; i < argc; i++) {
        cout << azColName[i] << ": " << argv[i] << endl;
    }*/

    Konto_Bankowe* uzytkownikBaza = new Konto_Bankowe(argv[1], argv[2], argv[4], stod(argv[5]), argv[6], argv[7], stoi(argv[8]));

    uzytkownicy.push_back(uzytkownikBaza);

    return 0;
}

vector<Konto_Bankowe*> DataBase::data() {
    uzytkownicy.clear();
    selectData();
    return uzytkownicy;
};

int DataBase::updateData(vector<Konto_Bankowe*> konta) {

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

            //string sqlAdd("INSERT INTO USERS (LOGIN, PASSWORD, PASS_SALT, PIN, BALANCE) VALUES ('" + konto->getLogin() + "', '" + konto->getHaslo() + "', 'salt', " + konto->getPin() + ", " + to_string(konto->getSaldo()) + ");");
            string sqlAdd("INSERT INTO USERS (LOGIN, PASSWORD, PASS_SALT, PIN, BALANCE, IMIE, NAZWISKO, PESEL) VALUES ('" + konto->getLogin() + "', '" + konto->getHaslo() + "', 'salt', " + konto->getPin() + ", " + to_string(konto->getSaldo()) + ", '" + konto->getImie() + "', '" + konto->getNazwisko() + "', " + to_string(konto->getPesel()) + ");");
            exit = sqlite3_exec(DB, sqlAdd.c_str(), NULL, 0, &messaggeError);

            if (exit != SQLITE_OK) {
                cerr << "Blad dodania danych podczas aktualizacji" << endl;
                sqlite3_free(messaggeError);
                break;
            }
        }
    }
  
    

    return 0;
};