#pragma once
#include "stdafx.h"
#include "Strukture.h"
using namespace std;
string getParameter(string line, int &i) {
	char data[20];
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

void dodajDeo(Elem *sekc, Elem *kraj, string ime, int sekcija, char vidljivost) {
	DeoTabele *deo = new DeoTabele(ime, 0, sekcija, 0, vidljivost, 0);
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
void dodajSekciju(Elem *sekc, string ime, int rb, int sekcija, char vidljivost) {//, ElemSekcija *trSekcija) {
	DeoTabele *deo = new DeoTabele(ime, rb, sekcija, 0, vidljivost, 0);
	Elem *novi = new Elem(deo, sekc->next);
	sekc->next = novi;
	//DeoTabeleSekcija *deoSekc = new DeoTabeleSekcija(ime, rb);
	//trSekcija ->next = new ElemSekcija(deoSekc);

}
Elem* imaSimbola(Elem *sekc, string simbol) {
	int i = 0;
	Elem *tek = sekc;
	while (tek != NULL) {
		if (strcmp(simbol.c_str(), tek->deo->ime.c_str()) == 0)
			return tek;
		tek = tek->next;
	}
	return NULL;
}
void ispisiTabeluSimbola(Elem *head, ofstream& out) {
	Elem *tek = head;
	while (tek != NULL) {
		out << tek->deo->rb << "	" << tek->deo->ime << "		" << tek->deo->sekcija << "		" << tek->deo->vrednost << "	" << tek->deo->vidljivost << "		" << tek->deo->velicina << '\n';
		tek = tek->next;
	}
}
void ispisiTabeluSekcija(TabelaSekcija* t, ofstream& out) {
	TabelaSekcija *pom = t;
	while (pom!=NULL) {
		out << "#" << pom->sekcija->deo->ime << '\n';
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
void freeTableOfSections(TabelaSekcija *table) {
	TabelaSekcija *pom = table;
	while (table) {
		table = table->next;
		free(pom->sadrzaj);
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