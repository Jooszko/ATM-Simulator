#pragma once
#include <iostream>
#include <vector>
#include "Konto_Bankowe.h"

#include "sqlite3.h"

using namespace std;

class DataBase
{
private:
    //œcie¿ka do bazy danych
    /*const char* dir = "c:\\Users\\jonas\\Desktop\\ProjektBankomat\\ATM-Simulator\\SymulatorBankomatu\\bankDatabase.bd";*/

    //vector<char**> uzytkownicy;
    char** u¿ytkownik;
    /*static string generateSalt(size_t length);
    static string generateHash(const string& password, const string& salt);*/

public:
    /*static int createDb(const char* s);
    static int createTable(const char* s);
    static int insertData(const char* s, Konto_Bankowe* noweKonto);*/
    //const string dir = "c:\\Users\\jonas\\Desktop\\ProjektBankomat\\ATM-Simulator\\SymulatorBankomatu\\bankDatabase.bd";

    //vector<char**> uzytkownicy;
    static int createDb();
    static int createTable();
    static int insertData(Konto_Bankowe* noweKonto);
    static int selectData();
    static int callback(void* NotUsed, int argc, char** argv, char** azColName);
    vector<Konto_Bankowe*> data();
    static int updateData(vector<Konto_Bankowe*> noweKonto);
    /*bool validateCredentials(string& username, string& password);*/



};

