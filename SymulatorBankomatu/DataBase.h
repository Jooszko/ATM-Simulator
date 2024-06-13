#pragma once
#include <iostream>
#include <vector>
#include "Konto_Bankowe.h"

#include "sqlite3.h"

using namespace std;

class DataBase
{
private:
    char** u¿ytkownik;

public:
    static int createDb();
    static int createTable();
    static int insertData(Konto_Bankowe* noweKonto);
    static int selectData();
    static int callback(void* NotUsed, int argc, char** argv, char** azColName);
    vector<Konto_Bankowe*> data();
    static int updateData(vector<Konto_Bankowe*> noweKonto);

};

