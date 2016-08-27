#pragma once
#include "stdafx.h"
#include "Functions.h"
#include "PostaviUslove.h"
#include "Registar.h"
#include "ImplInstr.h"
using namespace std;
int obradiInstrukciju(string word, int& i, string line, Elem *tabelaSimbola, TabelaSekcija *tSekcije) {
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
		Aritmeticka(rezultat, line, i, word);
	}

	else if (word == "sub") {
		rezultat = rezultat | 0x12000000;
		Aritmeticka(rezultat, line, i, word);
	}
	else if (word == "mul") {
		rezultat = rezultat | 0x13000000;
		Aritmeticka(rezultat, line, i, word);
	}
	else if (word == "div") {

		rezultat = rezultat | 0x14000000;
		Aritmeticka(rezultat, line, i, word);
	}
	else if (word == "cmp") {
		rezultat = rezultat | 0x15000000;
		Aritmeticka(rezultat, line, i, word);
	}
	else if (word == "and") {
		rezultat = rezultat | 0x16000000;
		Logicka(rezultat, line, i, word);
	}
	else if (word == "or") {
		rezultat = rezultat | 0x17000000;
		Logicka(rezultat, line, i, word);
	}
	else if (word == "not") {
		rezultat = rezultat | 0x18000000;
		Logicka(rezultat, line, i, word);
	}
	else if (word == "test") {
		rezultat = rezultat | 0x19000000;
		Logicka(rezultat, line, i, word);
	}
	else if (word == "ldr") {
		rezultat = rezultat | 0x0a000000;
		LdSt(rezultat, line, i, word, tabelaSimbola, tSekcije);
	}
	else if (word == "str") {
		rezultat = rezultat | 0x0a000000;
		LdSt(rezultat, line, i, word, tabelaSimbola, tSekcije);
	}
	else if (word == "call") {
		rezultat = rezultat | 0x0c000000;
		Call(rezultat, line, i, word, tabelaSimbola, tSekcije);
	}
	else if (word == "in") {
		rezultat = rezultat | 0x0d008000;
		InOut(rezultat, line, i, word);
	}
	else if (word == "out") {
		rezultat = rezultat | 0x0d008000;
		InOut(rezultat, line, i, word);
	}
	else if (word == "mov") {
		rezultat = rezultat | 0x1e000000;
		MovShift(rezultat, line, i, word);
		
	}
	else if (word == "shr") {
		rezultat = rezultat | 0x1e000000;
		MovShift(rezultat, line, i, word);
	}
	else if (word == "shl") {
		rezultat = rezultat | 0x1e000000;
		MovShift(rezultat, line, i, word);
	}
	else if (word == "ldch") {

		Ldch(rezultat, line, i, word, tabelaSimbola, tSekcije);

	}
	else if (word == "ldcl") {

		Ldcl(rezultat, line, i, word, tabelaSimbola, tSekcije);
	}
	else if (word == "ldc") {   
		int tri = i;
		Ldcl(rezultat, line, i, word, tabelaSimbola, tSekcije);
		int pomr = rezultat;
		tSekcije->sadrzaj[tSekcije->trVel] = (char)((rezultat & 0xff000000) >> 24);
		tSekcije->trVel++;
		rezultat<<= 8;
		tSekcije->sadrzaj[tSekcije->trVel] = (char)((rezultat & 0xff000000) >> 24);
		tSekcije->trVel++;
		rezultat <<= 8;
		tSekcije->sadrzaj[tSekcije->trVel] = (char)((rezultat & 0xff000000) >> 24);
		tSekcije->trVel++;
		rezultat<<= 8;
		tSekcije->sadrzaj[tSekcije->trVel] = (char)((rezultat & 0xff000000) >> 24);
		tSekcije->trVel++;
		i = tri;
		rezultat = pomr & 0xf0000000;
		Ldch(rezultat, line, i, word, tabelaSimbola, tSekcije);
	}

	return rezultat;

}
