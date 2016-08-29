#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include "Strukture.h"
#include <iomanip>
using namespace std;

string getParameter(string line, int &i) {
	char data[100];
	int j = 0;
	while ((line[i] == ' ' || line[i] == ',' || line[i] == '\'') &&  i<line.size())
		i++;
	while (line[i] != ' ' && line[i] != ',' && i < line.size()) {
		data[j] = line[i];
		j++; i++;
	}
	data[j] = '\0';
	return data;
}
char getChar(string line, int &i) {
	char data = ' ';
	while ((line[i] == ' ' || line[i] == ',' || line[i] == '\'') && i<line.size())
		i++;
	if(i<line.size())
		data = line[i];
		i++;
	return data;
}
void dodajDeo(Elem *sekc, Elem *kraj, string ime, int sekcija, char vidljivost, int vrednost) {
	DeoTabele *deo = new DeoTabele(ime, 0, sekcija, vrednost, vidljivost, 0);
	Elem *novi = new Elem(deo);
	if (kraj == sekc) {
		kraj = novi;
		sekc->next = kraj;
	}
	else {
		kraj->next = novi;
		kraj = novi;
	}
}
void dodajSekciju(Elem *sekc, string ime, int rb, int sekcija, char vidljivost) {
	DeoTabele *deo = new DeoTabele(ime, rb, sekcija, 0, vidljivost, 0);
	Elem *novi = new Elem(deo, sekc->next);
	sekc->next = novi;
}
Elem* imaSimbola(Elem *simTable, string simbol) {
	int i = 0;
	Elem *tek = simTable;
	while (tek != NULL) {
		if (strcmp(simbol.c_str(), tek->deo->ime.c_str()) == 0)
			return tek;
		tek = tek->next;
	}
	return NULL;
}

void ispisiTabeluSimbola(Elem *head, ofstream& out) {
	out << "#### Tabela Simbola #### \n\n";
	Elem *tek = head;
	out << setw(10) << "Redni Broj:" << setw(10) << "Ime" << setw(10) << "Sekcija" << setw(12) << "Vrednost" << setw(12) << "Vidljivost" << setw(10) << "Velicina\n";
	while (tek != NULL) {
		out << setw(10)<< tek->deo->rb << setw(10) << tek->deo->ime << setw(10) << tek->deo->sekcija << setw(12) << tek->deo->vrednost << setw(12) << tek->deo->vidljivost << setw(10) << tek->deo->velicina << '\n';
		cout << setw(10) << tek->deo->rb << setw(10) << tek->deo->ime << setw(10) << tek->deo->sekcija << setw(12) << tek->deo->vrednost << setw(12) << tek->deo->vidljivost << setw(10) << tek->deo->velicina << '\n';

		tek = tek->next;
	}
}
void ispisiTabeluSekcija(TabelaSekcija* t, ofstream& out) {
	TabelaSekcija *pom = t;
	out << "\n\n#### Tabela Sekcija #### \n\n";
	while (pom!=NULL) {
		out << "#" << pom->sekcija->deo->ime << "\n\n";
		int i = 0;
		while (i < pom->trVel) {
			int c0 = (int)(pom->sadrzaj[i] & 0x0f);
			int c1 = (int)((pom->sadrzaj[i] >> 4) & 0x0f);
			out << hex << c1;
			out << hex << c0 << " ";
			i++;
		}
		out << '\n';
		pom = pom->next;
	}
}
void ispisiTabeluRelokacija(TabelaSekcija *tS, ofstream& out) {
	TabelaSekcija *sekcija = tS;
	out << "\n\n#### Tabela Relokacija #### \n\n";
	out << setw(10) << "Sekcija" << setw(10) << "Offset" << setw(10) << "Shift" << setw(10) << "Tip" << setw(10) << "Symbol" << '\n';
	while (sekcija!= NULL) {
		Reloc_List *pom = sekcija->relokacije;
		
		while (pom) {
			out << setw(10) << sekcija->sekcija->deo->ime << setw(10) << pom->reloc->offset << setw(10) << pom->reloc->shift << setw(10) << pom->reloc->type << setw(10) << pom->reloc->symbol << '\n';
			pom = pom->next;
		}
		sekcija = sekcija->next;
	}
}
void postaviRb(Elem *head) {
	int id = 0;
	while (head != NULL) {
		head->deo->rb = id++;
		head = head->next;
	}
}
void freeTable(Elem *head) {
	Elem *pom = head;
	while (head) {
		head = head->next;
		free(pom);
		pom = head;
	}
}
void freeReloc(Reloc_List *r) {
	Reloc_List *pom = r;
	while (r) {
		r = r->next;
		free(pom->reloc);
		pom->reloc = NULL;
		free(pom);
		pom = r;
	}
}
void freeTableOfSections(TabelaSekcija *table) {
	TabelaSekcija *pom = table;
	while (table) {
		table = table->next;
		free(pom->sadrzaj);
		freeReloc(pom->relokacije);
		free(pom);
		pom = table;
	}
}

Elem* dohvatiSekciju(Elem *head, int rb) {
	int i = 0;
	Elem *tek = head;
	while (i++ < rb) tek = tek->next;
	return tek;
}
#endif