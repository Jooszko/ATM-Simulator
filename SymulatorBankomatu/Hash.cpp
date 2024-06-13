#include "Hash.h"
#include <random>
#include <string>
#include <sstream>
#include <iomanip>


string Hash::generateSalt(size_t length)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const size_t max_index = sizeof(charset) - 1;

    string salt;
    salt.reserve(length);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, max_index - 1);

    for (size_t i = 0; i < length; ++i) {
        salt += charset[dis(gen)];
    }

    return salt;
}

string Hash::generateHash(const string& password, const string& salt)
{

    string combined = password + salt;
    unsigned long hash = 0;

    for (char c : combined) {
        hash = hash * 31 + c;
    }

    stringstream ss;
    ss << hex << hash;
    return ss.str();
}
