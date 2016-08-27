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
struct Relocation {
	int offset;
	int shift;
	string type;
	int symbol;
	Relocation(int off, int sh, string type, int sym) {
		offset = off;
		shift = sh;
		this->type = type;
		symbol = sym;
	}
};
struct Reloc_List {
	Relocation *reloc;
	Reloc_List *next;
	Reloc_List(Relocation *r) {
		reloc = r;
		next = NULL;
	}

};

struct TabelaSekcija {
	char *sadrzaj;
	int trVel;
	Elem *sekcija;
	Reloc_List *relokacije;
	Reloc_List *tr;
	TabelaSekcija *next;
	TabelaSekcija(Elem *sekc, TabelaSekcija* sled) {
		sadrzaj = new char[100];
		trVel = 0;
		next = sled;
		sekcija = sekc;
		relokacije = NULL;
		tr = NULL;
	}
	~TabelaSekcija() {
		delete[] sadrzaj;
	}
	void dodajRelokaciju(Relocation *rel) {
		Reloc_List *r = new Reloc_List(rel);
		if (!relokacije) {
			relokacije = r;
		} else{

			tr->next = r;
		}
		tr = r;

	}
};