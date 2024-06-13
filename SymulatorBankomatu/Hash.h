#pragma once
#include <iostream>

using namespace std;

class Hash
{
public:
	static string generateSalt(size_t length);
	static string generateHash(const string& password, const string& salt);
};

