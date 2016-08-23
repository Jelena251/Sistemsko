#pragma once
#include "stdafx.h"
using namespace std;
struct DeoTabele {
	string ime;
	int rb;
	int sekcija;
	int vrednost;
	char vidljivost;
	int velicina;
	DeoTabele(string _ime, int _rb, int _sekcija, int _vrednost = 0, char _vidljivost = 'l', int _velicina = 0) {
		ime = _ime;
		rb = _rb;
		sekcija = _sekcija;
		vrednost = _vrednost;
		vidljivost = _vidljivost;
		velicina = _velicina;
	}
};
struct Elem {
	DeoTabele *deo;
	Elem *next;
	Elem(DeoTabele *_deo, Elem *sled = NULL) {
		deo = _deo;
		next = sled;
	}
};

struct TabelaSekcija {
	char *sadrzaj;
	int trVel;
	Elem *sekcija;
	TabelaSekcija *next;
	TabelaSekcija(Elem *sekc, TabelaSekcija* sled) {
		sadrzaj = new char[100];
		trVel = 0;
		next = sled;
		sekcija = sekc;
	}
	~TabelaSekcija() {
		delete[] sadrzaj;
	}
};