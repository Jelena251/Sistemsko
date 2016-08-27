#pragma once
#include "stdafx.h"
#include "Functions.h"
#include "PostaviUslove.h"
#include "Registar.h"
using namespace std;

void Aritmeticka(int &rezultat, string line, int& i, string word) {
	string par = getParameter(line, i);
	char regD = dohvatiBrojRegistra(par, word);
	int pom = 0x00000000 | regD;
	pom <<= 19;
	rezultat = rezultat | pom;
	par = getParameter(line, i);
	regD = dohvatiBrojRegistra(par, word);
	if (regD == 'e') {
		int immNum = stoi(par);
		immNum = (immNum | 0x00040000);
		rezultat = rezultat | immNum;
	}
	else {
		pom = 0x00000000 | regD;
		pom <<= 14;
		rezultat = rezultat | pom;
	}
}
void Logicka(int &rezultat, string line, int& i, string word) {
	string par = getParameter(line, i);
	char regD = dohvatiBrojRegistra(par, word);
	int pom = 0x00000000 | regD;
	pom <<= 19;
	rezultat = rezultat | pom;
	par = getParameter(line, i);
	regD = dohvatiBrojRegistra(par, word);
	pom = 0x00000000 | regD;
	pom <<= 14;
	rezultat = rezultat | pom;
}

void LdSt(int &rezultat, string line, int& i, string word, Elem *tabelaSimbola, TabelaSekcija *tSekcija) {
	//dohvati prvi regista
	string par = getParameter(line, i);

	bool relative = false;
	if (par == "PC" || par == "r16") relative = true;
	char regD = dohvatiBrojRegistra(par, word);
	int pom = 0x00000000 | regD;
	pom <<= 19;
	rezultat = rezultat | pom;
	//doohvati drugi registar
	par = getParameter(line, i);
	regD = dohvatiBrojRegistra(par, word);
	pom = 0x00000000 | regD;
	pom <<= 14;
	rezultat = rezultat | pom;
	//dohvati f
	par = getParameter(line, i);
	int f = stoi(par);
	if (relative) f = 0;
	pom = 0x00000000 | f;
	pom <<= 9;
	rezultat = rezultat | pom;
	//neposredna vrednost ili labela
	par = getParameter(line, i);
	Elem *sim = imaSimbola(tabelaSimbola, par);
	if (sim) {
		int simNum = (sim->deo->vidljivost == 'l') ? sim->deo->sekcija : 0;
		string type = relative ? "PC_REL_10" : "APS_10";
 		tSekcija->dodajRelokaciju(new Relocation(tSekcija->trVel + 2, 6, type, simNum));
		if (sim->deo->vidljivost == 'l') f = sim->deo->vrednost;
		else f = 0;

	}
	else {
		f = stoi(par);
	}
		if (word == "ldr") {
			pom = 0x00000400 | (f & 0x000003ff);
		}
		else {
			pom = 0x00000000 | (f & 0x000003ff);
		}
		rezultat = rezultat | pom;
	
}

void Call(int &rezultat, string line, int& i, string word, Elem *tabelaSimbola, TabelaSekcija *tSekcije) {
	string par = getParameter(line, i);
	char regD = dohvatiBrojRegistra(par, word);
	int pom = 0x00000000 | regD;
	pom <<= 19;
	rezultat = rezultat | pom;
	//immediate val or label
	par = getParameter(line, i);
	int f;
	Elem * sim = imaSimbola(tabelaSimbola, par);
	if (sim) {
		if (sim->deo->vidljivost == 'l' && sim == tSekcije->sekcija) {
			f = sim->deo->vrednost;
		}else{
			int simNum = (sim->deo->vidljivost == 'l') ? sim->deo->sekcija : 0;
			tSekcije->dodajRelokaciju(new Relocation((tSekcije->trVel + 1), 5, "PC_REL_19", simNum));
			if (sim->deo->vidljivost == 'l')
				f = sim->deo->vrednost;
			else
				f = 0;
		}
	}
	else {
		f = stoi(par);
	}
	pom = 0x00000000 | f;
	rezultat = rezultat | pom;
}

void InOut(int &rezultat, string line, int& i, string word) {
	string par = getParameter(line, i);
	char regD = dohvatiBrojRegistra(par, word);
	int pom = 0x00000000 | regD;
	pom <<= 20;
	rezultat = rezultat | pom;
	par = getParameter(line, i);
	regD = dohvatiBrojRegistra(par, word);
	pom = 0x00000000 | regD;
	pom <<= 16;
	if (word == "in") pom = pom | 0x00008000;
	rezultat = rezultat | pom;
}

void MovShift(int &rezultat, string line, int& i, string word) {
	string par = getParameter(line, i);
	char regD = dohvatiBrojRegistra(par, word);
	int pom = 0x00000000 | regD;
	pom <<= 19;
	rezultat = rezultat | pom;
	par = getParameter(line, i);
	regD = dohvatiBrojRegistra(par, word);
	pom = 0x00000000 | regD;
	pom <<= 14;
	rezultat = rezultat | pom;
	if (word == "shr" || word == "shl") {
		int im = stoi(getParameter(line, i));
		im = ((im & 0x0000001f) << 9);
		if (word == "shl") im = im | 0x00000100;
		rezultat = rezultat | im;
	}
}

void Ldch(int &rezultat, string line, int& i, string word, Elem *tabelaSimbola, TabelaSekcija *tSekcija) {
	rezultat = rezultat | 0x0f000000;
	string par = getParameter(line, i);
	char  regD= dohvatiBrojRegistra(par, word);
	int pom = 0x00000000 | regD;
	pom <<= 20;
	pom = pom | 0x00080000;
	rezultat = rezultat | pom;

	string vrednost = getParameter(line, i);
	Elem *sim = imaSimbola(tabelaSimbola, vrednost);
	if (sim) {
		int simNum = (sim->deo ->vidljivost == 'l') ? sim->deo->sekcija : 0;
		tSekcija->dodajRelokaciju(new Relocation(tSekcija->trVel + 2, 0, "APS_16_H", simNum));
		if (sim->deo->vidljivost == 'l')
			simNum = sim->deo->vrednost & 0x0000ffff;
		else simNum = 0x00000000;
		rezultat = rezultat | simNum;
	}else{
		int c = stoi(vrednost);
		c = (c>>8) | 0x00000000;
		rezultat = rezultat | c;
	}
}
void Ldcl(int &rezultat, string line, int& i, string word, Elem *tabelaSimbola, TabelaSekcija *tSekcija) {
	rezultat = rezultat | 0x0f000000;
	string par = getParameter(line, i);
	char regD = dohvatiBrojRegistra(par, word);
	int pom = 0x00000000 | regD;
	pom <<= 20;
	rezultat = rezultat | pom;

	string vrednost = getParameter(line, i);
	Elem *sim = imaSimbola(tabelaSimbola, vrednost);
	if (sim) {
		int simNum = (sim->deo->vidljivost == 'l') ? sim->deo->sekcija : 0;
		tSekcija->dodajRelokaciju(new Relocation(tSekcija->trVel+2, 0, "APS_16_L", simNum));
		if (sim->deo->vidljivost == 'l')
			simNum = sim->deo->vrednost;
		else simNum = 0x00000000;
		rezultat = rezultat | simNum;
	}
	else {
		int c = stoi(vrednost);
		c = (c >> 8) | 0x00000000;
		rezultat = rezultat | c;
	}
}