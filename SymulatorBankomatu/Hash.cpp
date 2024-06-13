#include "Hash.h"
#include <random>
#include <string>
#include <sstream>
#include <iomanip>


string Hash::generateSalt(size_t length)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const size_t max_index = sizeof(charset) - 1; // rozmiar

    string salt;
    salt.reserve(length); // rezerwacja miejsca dla wydajnosci

    random_device rd; // uzyskanie losowej liczby 
    mt19937 gen(rd()); // generator ziarna
    uniform_int_distribution<> dis(0, max_index - 1); // Define the range

    for (size_t i = 0; i < length; ++i) {
        salt += charset[dis(gen)]; // dodanie znaku do 'soli'
    }

    return salt; // zwrocenie soli
}

string Hash::generateHash(const string& password, const string& salt)
{

    string combined = password + salt;
    unsigned long hash = 0;

    for (char c : combined) {
        hash = hash * 31 + c; //funkcja haszujaca
    }

    //konwersja na system heksadecymalny
    stringstream ss;
    ss << hex << hash;
    return ss.str();
}

//bool Hash::validateCredentials(string& username, string& password)
//{
//
//    //wygenerowanie hashu na podstawie hasla pobranego od uzytkownika i soli z bazy danych
//    //string generatedHash = generateHash(password, userCredentials.password_salt);
//
//    // walidacja wygenerowanego nowego hasha do istniejacego w bazie danych
//    //return generatedHash == userCredentials.password_hash;
//    return 0;
//}