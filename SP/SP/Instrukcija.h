#pragma once
#include "stdafx.h"
#include "Functions.h"
#include "PostaviUslove.h"
#include "Registar.h"
using namespace std;
int obradiInstrukciju(string word, int& i, string line) {
	int rezultat = 0;
	postaviUslove(rezultat, word, i, line);
	if (word == "int") {
		rezultat = rezultat | 0x00000000;
		int c = stoi(getParameter(line, i));
		int pom = 0x00000000 | c;
		pom <<= 20;
		rezultat = rezultat | pom;
	}
	else if (word == "add") {
		rezultat = rezultat | 0x11000000;
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

	else if (word == "sub") {
		rezultat = rezultat | 0x12000000;
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
	else if (word == "mul") {
		rezultat = rezultat | 0x13000000;
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
	else if (word == "div") {

		rezultat = rezultat | 0x14000000;
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
	else if (word == "cmp") {
		rezultat = rezultat | 0x15000000;
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
			pom <<= 13;
			rezultat = rezultat | pom;
		}
	}
	else if (word == "and") {
		rezultat = rezultat | 0x16000000;
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
	else if (word == "or") {
		rezultat = rezultat | 0x17000000;
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
	else if (word == "not") {
		rezultat = rezultat | 0x18000000;
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
	else if (word == "test") {
		rezultat = rezultat | 0x19000000;
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
	else if (word == "ldr") {
		rezultat = rezultat | 0x0a000000;
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
		par = getParameter(line, i);
		int f = stoi(par);
		pom = 0x00000000 | f;
		pom <<= 9;
		rezultat = rezultat | pom;
		par = getParameter(line, i);
		f = stoi(par);
		pom = 0x00000400 | f;
		rezultat = rezultat | pom;
	}
	else if (word == "str") {
		rezultat = rezultat | 0x0a000000;
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
		par = getParameter(line, i);
		int f = stoi(par);
		pom = 0x00000000 | f;
		pom <<= 9;
		rezultat = rezultat | pom;
		par = getParameter(line, i);
		f = stoi(par);
		pom = 0x00000000 | f;
		rezultat = rezultat | pom;
	}
	else if (word == "call") {
		rezultat = rezultat | 0x0c000000;
		string par = getParameter(line, i);
		char regD = dohvatiBrojRegistra(par, word);
		int pom = 0x00000000 | regD;
		pom <<= 19;
		rezultat = rezultat | pom;
		//immediate reg
		par = getParameter(line, i);
		int f = stoi(par);
		pom = 0x00000000 | f;
		rezultat = rezultat | pom;
	}
	else if (word == "in") {
		rezultat = rezultat | 0x0d008000;
		string par = getParameter(line, i);
		char regD = dohvatiBrojRegistra(par, word);
		int pom = 0x00000000 | regD;
		pom <<= 20;
		rezultat = rezultat | pom;
		par = getParameter(line, i);
		regD = dohvatiBrojRegistra(par, word);
		pom = 0x00000000 | regD;
		pom <<= 16;
		rezultat = rezultat | pom;
	}
	else if (word == "out") {
		rezultat = rezultat | 0x0d008000;
		string par = getParameter(line, i);
		char regD = dohvatiBrojRegistra(par, word);
		int pom = 0x00000000 | regD;
		pom <<= 20;
		rezultat = rezultat | pom;
		par = getParameter(line, i);
		regD = dohvatiBrojRegistra(par, word);
		pom = 0x00000000 | regD;
		pom <<= 16;
		rezultat = rezultat | pom;
	}
	else if (word == "mov") {
		rezultat = rezultat | 0x1e000000;
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
	else if (word == "shr") {
		rezultat = rezultat | 0x1e000000;
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
		int im = stoi(getParameter(line, i));
		im = ((im & 0x0000001f) << 9);
		rezultat = rezultat | im;

	}
	else if (word == "shl") {
		rezultat = rezultat | 0x1e000000;
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
		int im = stoi(getParameter(line, i));
		im = ((im & 0x0000001f) << 9) | 0x00000100;
		rezultat = rezultat | im;
	}
	else if (word == "ldch") {
		rezultat = rezultat | 0x0f000000;
		string par = getParameter(line, i);
		char regD = dohvatiBrojRegistra(par, word);
		int pom = 0x00000000 | regD;
		pom <<= 20;
		rezultat = rezultat | pom;
		int c = stoi(getParameter(line, i));
		c = (c & 0x0000ffff) | 0x00080000;
		rezultat = rezultat | c;

	}
	else if (word == "ldcl") {
		rezultat = rezultat | 0x0f00000;
		string par = getParameter(line, i);
		char regD = dohvatiBrojRegistra(par, word);
		int pom = 0x00000000 | regD;
		pom <<= 20;
		rezultat = rezultat | pom;
		int c = stoi(getParameter(line, i));
		c = c & 0x0000ffff;
		rezultat = rezultat | c;
	}
	else if (word == "ldc") {   ///ovo vidi kako ide :D 
		rezultat = rezultat | 0x0f00000;
		string par = getParameter(line, i);
		char regD = dohvatiBrojRegistra(par, word);
		int pom = 0x00000000 | regD;
		pom <<= 20;
		rezultat = rezultat | pom;
		int c = stoi(getParameter(line, i));
		c = c & 0x0000ffff;
		rezultat = rezultat | c;
	}
	return rezultat;

}
