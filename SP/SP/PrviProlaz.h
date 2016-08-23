#pragma once
#include "stdafx.h"
#include "Functions.h"
#include "Strukture.h"
using namespace std;
Elem* prviProlazAsm(ifstream &myfile) {
	string word, line;

	Elem *head, *sekcije, *kraj;
	head = sekcije = kraj = NULL;
	DeoTabele *deo = new DeoTabele("UND", 0, 0);

	head = sekcije = kraj = new Elem(deo);

	int id = 1;

	while (!myfile.eof()) {
		char data[100];
		getline(myfile, line);
		int i = 0;
		word = getParameter(line, i);
		if (word == ".public") {
			string simbol;
			simbol = getParameter(line, i);
			while (simbol.compare("\0") != 0) {
				Elem *pom = imaSimbola(sekcije, simbol);
				if (!pom) {
					dodajDeo(sekcije, kraj, simbol, sekcije->deo->rb, 'g');
					if (kraj == sekcije)
						kraj = sekcije->next;
					else
						kraj = kraj->next;
				}
				else {
					pom->deo->vidljivost = 'g';
				}
				simbol = getParameter(line, i);
			}
		}
		else if (word == ".extern") {
			string simbol = getParameter(line, i);
			while (simbol.compare("\0") != 0) {
				if (!imaSimbola(sekcije, simbol)) {
					dodajDeo(sekcije, kraj, simbol, 0, 'g');
					if (kraj == sekcije)
						kraj = sekcije->next;
					else
						kraj = kraj->next;
				}
				simbol = getParameter(line, i);
			}
		}
		else if (word.size() >= 4 && word.substr(0, 4) == ".bss") {
			dodajSekciju(sekcije, word, id, id, 'l');
			sekcije = sekcije->next;
			id++;
		}
		else if (word.size() >= 5 && word.substr(0, 5) == ".data") {
			dodajSekciju(sekcije, word, id, id, 'l');
			sekcije = sekcije->next;
			id++;
		}
		else if (word.size() >= 5 && word.substr(0, 5) == ".text") {
			dodajSekciju(sekcije, word, id, id, 'l');
			sekcije = sekcije->next;
			id++;
		}
		else if (word[i - 1] == ':') {
			word[i - 1] = '\0';
			Elem *simb = imaSimbola(sekcije, word);
			if (simb != NULL) {
				simb->deo->sekcija = sekcije->deo->rb;
				simb->deo->vrednost = sekcije->deo->velicina;
			}
			else {
				dodajDeo(sekcije, kraj, word, sekcije->deo->rb, 'l');
				if (kraj == sekcije)
					kraj = sekcije->next;
				else
					kraj = kraj->next;
			}
		}
		else if (word == ".char") {
			char c;
			int j = 0;
			while (i < line.size()) {
				while (line[i] == ' ' || line[i] == ',') i++;
				c = line[i]; i++;
				sekcije->deo->velicina++;
			}
		}
		else if (word == ".skip") {
			int numSkip, j = 0;
			string data = getParameter(line, i);
			numSkip = atoi(data.c_str());
			sekcije->deo->velicina += numSkip;
		}
		else if (word == ".align") {
			int maxBr = 0;
			int broj = stoi(getParameter(line, i));
			int uvecanje = 0;
			while ((sekcije->deo->velicina + uvecanje) % broj != 0) uvecanje++;
			if (i < line.size()) {
				char c = *(getParameter(line, i).c_str());
				if (i < line.size()) {
					maxBr = stoi(getParameter(line, i));
					if (uvecanje <= maxBr)
						sekcije->deo->velicina += uvecanje;
				}
				else
					sekcije->deo->velicina += uvecanje;
			}
			else
				sekcije->deo->velicina += uvecanje;


		}
		else if (word == ".word") {
			unsigned int broj = stoi(getParameter(line, i));
			sekcije->deo->velicina += 2;
		}
		else if (word == ".long") {
			int cnt = 0;
			unsigned int broj = stoi(getParameter(line, i));
			sekcije->deo->velicina += 4;
		}
		else if (word == ".end") {
			cout << ".END\n";
			break;
		}
	}
	postaviRb(head);
	
	return head;
}