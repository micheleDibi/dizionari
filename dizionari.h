#ifndef DIZIONARI_H
#define DIZIONARI_J

#include <iostream>
#include <string>
using namespace std;

template <class K, class E>
struct coppia {
    K chiave;
    E elemento;

    coppia() {}

    coppia(K key, E element) {
        this->chiave = key;
        this->elemento = element;
    }

    coppia(coppia<K, E> &thePair) {
        this->chiave = thePair.chiave;
        this->elemento = thePair.elemento;
    }

    coppia<K, E> &operator=(const coppia<K, E> thePair) {
        this->chiave = thePair.chiave;
        this->elemento = thePair.elemento;
        return *this;
    }

    bool operator==(const coppia<K, E> thePair) {
        return (this->chiave == thePair.chiave && this->elemento == thePair.elemento);
    }

    friend ostream &operator<<(ostream &os, const coppia<K, E> &thePair) {
        os << "<" << thePair.chiave << "," << thePair.valore << ">";
        return os;
    }
};

template <class K, class E>
class dizionario {
public:

    typedef K chiave;
    typedef E elemento;

    virtual void create() = 0;
    virtual bool vuoto() const = 0;
    virtual int dimensione() const = 0;
    virtual int ricerca(const chiave &) const = 0;
    virtual coppia<K, E>* trova (const chiave&) const = 0;
    virtual void inserisci(coppia<K, E>&) = 0;
    virtual void cancella(const chiave&) = 0;
    virtual void modifica(const chiave&, const elemento&) = 0;
    virtual const elemento& recupera(const chiave&) const = 0;

};

#endif //DIZIONARI_H
