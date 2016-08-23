#pragma once
#include "stdafx.h"
#include "Functions.h"
#include "Instrukcija.h"
using namespace std;

TabelaSekcija* drugiProlazAsm(ifstream &myfile,Elem *tabelaSimbola) {
	string word, line;

//ovde napravi tabelu sekcija
	TabelaSekcija *head, *tr;
	int id;
	Elem* sekcija = imaSimbola(tabelaSimbola, "UND");
	head = new TabelaSekcija(sekcija, NULL);
	tr = head;
	while (!myfile.eof()) {
		char data[100];
		getline(myfile, line);
		int i = 0;
		word = getParameter(line, i);
		if (word == ".public") {
		}
		else if (word == ".extern") {

		}
		else if (word.size() >= 4 && word.substr(0, 4) == ".bss") {
			tr -> next = new TabelaSekcija(imaSimbola(tabelaSimbola, word), NULL);
			if (tr->next) tr = tr->next;
		}
		else if (word.size() >= 5 && word.substr(0, 5) == ".data") {
			tr->next = new TabelaSekcija(imaSimbola(tabelaSimbola, word), NULL);
			if (tr->next) tr = tr->next;
		}
		else if (word.size() >= 5 && word.substr(0, 5) == ".text") {
			tr->next = new TabelaSekcija(imaSimbola(tabelaSimbola, word), NULL);
			if (tr->next) tr = tr->next;
		}
		else if (word[i - 1] == ':') {
			//sta radimo sa labelom u drugom prolazu
		}
		else if (word == ".char") {
			char c;
			while (i < line.size()) {
				c = getChar(line, i);
				if (c != ' ') {
					tr->sadrzaj[tr->trVel] = c;
					tr->trVel++;
				}
			}
		}
		else if (word == ".skip") {
			int numSkip = stoi(getParameter(line, i));
			if (i < line.size()) {
				char c = getChar(line, i);
				for (int j = 0; j < numSkip; j++) {
					tr->sadrzaj[tr->trVel] = c;
					tr->trVel++;
				}
			}else{
				for (int j = 0; j < numSkip; j++) {
					tr->sadrzaj[tr->trVel] = 0x00;
					tr->trVel++;
				}
			}
		}
		else if (word == ".align") {
			int mutual = stoi(getParameter(line, i));
			int sizeToAdd = 0;
			while ((tr->trVel + sizeToAdd) % mutual != 0) sizeToAdd++;
			if (i < line.size()) {
				char sadr = getChar(line, i);
				if (i < line.size()) {
					int maxSizeToAdd = stoi(getParameter(line, i));
					if (sizeToAdd <= maxSizeToAdd) {
						for (int j = 0; j < sizeToAdd; j++) {
							tr->sadrzaj[tr->trVel] = sadr;
							tr->trVel++;
						}
					}
				}
				else {
					for (int j = 0; j < sizeToAdd; j++) {
						tr->sadrzaj[tr->trVel] = sadr;
						tr->trVel++;
					}
				}
			}else {
				for (int j = 0; j < sizeToAdd; j++) {
					tr->sadrzaj[tr->trVel] = 0x00;
					tr->trVel++;
				}
			}
		}
		else if (word == ".word") {
			unsigned int n = stoi(getParameter(line, i));
			tr->sadrzaj[tr->trVel] = (char)(n & 0x00ff);
			n <<= 8;
			tr->trVel++;
			tr->sadrzaj[tr->trVel] = char(n & 0x00ff);
			tr->trVel++;
			
		}
		else if (word == ".long") {
			unsigned int n = stoi(getParameter(line, i));
			tr->sadrzaj[tr->trVel] = (char)(n & 0x00ff);
			tr->trVel++;
			n <<= 8;
			tr->sadrzaj[tr->trVel] = (char)(n & 0x00ff);
			tr->trVel++;
			n <<= 8;
			tr->sadrzaj[tr->trVel] = (char)(n & 0x00ff);
			tr->trVel++;
			n <<= 8;
			tr->sadrzaj[tr->trVel] = (char)(n & 0x00ff);
			tr->trVel++;
		}
		else if (word == ".end") {
			return head;
		}
		else {

			
			int n = obradiInstrukciju(word, i, line);
			tr->sadrzaj[tr->trVel] = (char)((n & 0xff000000)>>24);
			tr->trVel++;
			n <<= 8;
			tr->sadrzaj[tr->trVel] = (char)((n & 0xff000000) >> 24);
			tr->trVel++;
			n <<= 8;
			tr->sadrzaj[tr->trVel] = (char)((n & 0xff000000) >> 24);
			tr->trVel++;
			n <<= 8;
			tr->sadrzaj[tr->trVel] = (char)((n & 0xff000000) >> 24);
			tr->trVel++;

		}
	}
	return head;
}