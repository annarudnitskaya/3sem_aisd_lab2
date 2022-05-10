#include "AlgoritmShF.h"
#include "List.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	shannonfano map;
	string quote;
	cout << "Enter message to encode: ";
	getline(cin, quote);
	int i = 0;
	while (i < quote.length())
	{
		map.insert(quote[i]);
		i++;
	}

	map.Print();

	map.encoding_tree();

	map.show_codes();

	cout << "The result: ";

	map.show_encoded(quote);


	cout << endl << "Amount of memory before: " << 8 * quote.length() << " bits";
	cout << endl << "Amount of memory after: " << 2 * quote.length() << " bits";
	cout << endl << "Compression ratio is " << (8 * quote.length()) / (2 * quote.length());
	cout << endl << "Enter message to decode ";
	string todecode;
	cin >> todecode;
	string decoded;
	map.decoding(todecode, decoded);
	cout << endl << "Decoded message: " << decoded;
	return 0;
}