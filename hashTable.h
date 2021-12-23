#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "dizionari.h"
#include <string>

template <class T>
class hAsh{
public:
    size_t operator() (const T theKey) const;
};

template<>
class hAsh<string> {
public:
    size_t operator()(const string the_key) const
	{
		unsigned long hash_value = 0;
		int lenght = (int)the_key.length();
		for (int i = 0; i < lenght; i++)
		{
			hash_value = 5 * hash_value + the_key.at(i);
		}
		return (size_t(hash_value));
	}
};

template<class K, class E>
struct coppia;

template<class K, class E>
class hashTable : public dizionario<K, E> {
public:

    typedef K chiave;
    typedef E elemento;

    hashTable();
    hashTable(int);
    ~hashTable();

    void create() {};
    bool vuoto() const;
    int dimensione() const;
    int ricerca(const chiave &) const;
    coppia<K, E>* trova (const chiave&) const;
    void inserisci(coppia<K, E>&);
    void cancella(const chiave&);
    void modifica(const chiave&, const elemento&);
    const E &recupera(const K &) const;

private:
    coppia<K, E> **tabella;
    hAsh<K> hashM;
    int dim;            //numero di coppie del dizionario
    int divisore;       //divisore della tabella hash
};

template <class K, class E>
hashTable<K, E>::hashTable() {
    divisore = 100;
    dim = 0;

    tabella = new coppia<K, E>*[divisore];
    for (int i = 0; i < divisore; i++) {
        tabella[i] = nullptr;
    }
}

template<class K, class E>
hashTable<K, E>::hashTable(int div) {
    divisore = div;
    dim = 0;

    tabella = new coppia<K, E>*[divisore];
    for (int i = 0; i < divisore; i++) {
        tabella[i] = nullptr;
    }
}

template <class K, class E>
hashTable<K, E>::~hashTable() {
    for(int i = 0; i < divisore; i++) {
        if(tabella[i] != nullptr) {
            delete tabella[i];
            tabella[i] = nullptr;
            dim--;
        }
    }

    delete[] tabella;
}

template<class K, class E>
bool hashTable<K, E>::vuoto() const {
    return (dim == 0);
}

template<class K, class E>
hashTable<K, E>::dimensione() const {
    return (dim);
}

template<class K, class E>
int hashTable<K, E>::ricerca(const K &key) const {
    int i = (int)hashM(key) % divisore;
    int j = i;

    do {
        if(tabella[j] == nullptr || tabella[j]->chiave == key) {
            return j;
        }
        j = (j + 1) % divisore;

    } while(j != i);

    return j;
}

template<class K, class E>
coppia<K, E>* hashTable<K, E>::trova (const K &key) const {
    int i = ricerca(key);

    if(tabella[i] == nullptr || tabella[i]->chiave != key) {
        return nullptr;
    }

    return tabella[i];
}

template <class K, class E>
void hashTable<K, E>::inserisci(coppia<K, E>& pairs) {
    int i = ricerca(pairs.chiave);

    if(tabella[i] == nullptr) {
        tabella[i] = new coppia<K, E>(pairs);
        dim++;
    } else {
        if(tabella[i]->chiave == pairs.chiave) {
            //chiave già presente -> aggiorno il valore
            tabella[i]->elemento = pairs.elemento;
        }
    }
}

template <class K, class E>
void hashTable<K, E>::cancella(const K &key) {
    int i = ricerca(key);

    if(tabella[i] != nullptr && tabella[i]->chiave == key) {
        delete tabella[i];
        tabella[i] = nullptr;
        dim--;
    }
}

template <class K, class E>
void hashTable<K, E>::modifica(const K &key, const E &elem) {
    int i = ricerca(key);

    if(tabella[i] != nullptr && tabella[i]->chiave == key) {
        tabella[i]->elemento = elem;
    }
}

template <class K, class E>
const E &hashTable<K, E>::recupera(const K &key) const {

    int i = ricerca(key);

    if(tabella[i] != nullptr && tabella[i]->chiave == key) {
        return tabella[i]->elemento;
    }
}

#endif // HASHTABLE_H
