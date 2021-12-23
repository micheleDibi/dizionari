#include <iostream>
#include <string>

#include "hashTable.h"

using namespace std;

int main()
{
    hashTable<string, int> h(10);
	coppia<string, int> the_pair;

	the_pair.chiave = "firstkey";
	the_pair.elemento = 10;

	cout << "\nvuoto: " << h.vuoto();
	cout << "\nnum elementi: " << h.dimensione();

	h.inserisci(the_pair);
	cout << "\nvalore primachiave: " << h.recupera(the_pair.chiave);
	cout << "\n\n";

	coppia<string, int> the_copy = *(h.trova(the_pair.chiave));
	the_copy.chiave = "secondkey";

	cout << "\nsearch copy key: " << h.ricerca(the_copy.chiave);
	h.inserisci(the_copy);

	h.modifica(the_copy.chiave, 20);
	cout << "\nvalore prima chiave copia: " << h.recupera(the_copy.chiave);
	cout << "\n";

    return 0;
}
